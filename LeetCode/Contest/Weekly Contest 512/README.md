# 4003. Minimum Cost Path with Alternating Directions III

## Problem Overview

The problem requires finding the minimum total cost to traverse a grid of size `m x n` from the starting cell `(0, 0)` to the destination cell `(m - 1, n - 1)`.

The traversal is governed by a strict parity rule based on the action sequence number (1-indexed), which alternates after every action (moving or waiting):

* **Odd-numbered actions (Parity 1):** The valid directions are **Right** or **Down**.
* **Even-numbered actions (Parity 0):** The valid directions are **Left** or **Up**.

The cost structure is defined as follows:

* **Valid Move:** Pay the entrance cost of the destination cell `(nr + 1) * (nc + 1)`.
* **Invalid Move (Violating Parity):** Pay the entrance cost of the destination cell plus the penalty of the current cell `penalty[r][c]`.
* **Wait:** Stay in the current cell, pay `penalty[r][c]`, and increment the action counter.

## Mathematical Model & Algorithm Selection

### Why Dynamic Programming is Inapplicable

While finding the minimum cost path on a 2D matrix is a classic Dynamic Programming (DP) problem, DP strictly requires the underlying state-space graph to be a **Directed Acyclic Graph (DAG)**.

In this problem, the allowed actions include moving in all four cardinal directions (Up, Down, Left, Right) and waiting in place. This introduces **cycles** into the graph (e.g., moving Left then Right, or Waiting repeatedly). Because of these cyclic dependencies, a strict topological ordering of states is impossible to achieve. A standard DP approach would fall into an infinite loop or yield incorrect results due to unresolved state dependencies.

### State-Space Dijkstra

To handle the cyclic nature of the graph and the non-negative edge weights (costs), **Dijkstra's Algorithm** is the optimal choice. The algorithm must be adapted to operate on an expanded state space rather than just the 2D coordinates.

#### State Representation

Each node in the graph is represented by a tuple: `(cost, row, col, parity)`.

* `cost`: The accumulated cost to reach the current state.
* `row`, `col`: The current coordinates on the grid.
* `parity`: The binary state of the current action (1 for odd, 0 for even).

#### State Transitions

From a state `(row, col, parity)`, there are exactly 5 possible transitions to a `next_parity = 1 - parity`:

1. **Move Right `(row, col + 1)`:** Valid if `parity == 1`.
2. **Move Down `(row + 1, col)`:** Valid if `parity == 1`.
3. **Move Left `(row, col - 1)`:** Valid if `parity == 0`.
4. **Move Up `(row - 1, col)`:** Valid if `parity == 0`.
5. **Wait `(row, col)`:** Always costs `penalty[row][col]`.

For directional moves, if the move aligns with the validation rule, the cost increment is `(nr + 1) * (nc + 1)`. Otherwise, an additional `penalty[row][col]` is incurred.

## Implementation Details

* **Priority Queue:** A min-heap (`std::priority_queue` in C++) is utilized to strictly evaluate the lowest-cost paths first.
* **Distance Array for Pruning:** A 3D array `dist[m][n][2]` initialized to infinity is used to track the minimum cost to reach any `(row, col)` with a specific `parity`. If a generated state has a cost greater than or equal to the recorded cost in `dist`, it is pruned to prevent queue bloat.
* **Early Exit:** The algorithm terminates and returns the cost immediately upon popping the destination coordinate `(m - 1, n - 1)` from the priority queue, guaranteeing the minimum cost due to Dijkstra's greedy property.

## Complexity Analysis

* **Time Complexity:** $O(V \log V)$, where $V = m \times n \times 2$ (the total number of states).
* There are $2 \cdot m \cdot n$ unique states.
* Each state has up to 5 edges (transitions).
* Heap operations take $O(\log(m \cdot n))$.
* Total Time Complexity: $O(m \cdot n \log(m \cdot n))$.


* **Space Complexity:** $O(m \cdot n)$ to maintain the 3D `dist` array and the Priority Queue, bounding the memory usage linearly with respect to the grid size.