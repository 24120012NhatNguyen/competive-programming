# VOI 22: SSEQ - Sum of Segments

[Problem Link](https://oj.vnoi.info/problem/voi22_sseq)

## Algorithm Overview
The problem requires us to find a continuous range $[L, R]$ such that the total weight of all given segments completely contained within this range is maximized. 
Optimal Solution: **Sweep-line Algorithm + Segment Tree with Lazy Propagation**.

##  Analytical Thinking 

Instead of trying to find both $L$ and $R$ simultaneously, we fix the ending point $R$ at position $i$ and look for the optimal starting point $j$.

1.  **State Definition:**
    *   Let $f[j, i]$ be the total weight of all segments entirely enclosed within the interval $[j, i]$.
    *   At any given position $i$, our objective is to efficiently query $\max(f[j, i])$ for all valid $j \le i$.

2.  **Data Structure:**
    *   Since $i$ strictly increases (sweeping from left to right), we need a data structure to dynamically store and update $f[j, i]$ for all possible starting positions $j$.
    *   A **Segment Tree** perfectly fits this requirement. Let `st[j]` represent the total accumulated weight if we choose $j$ as the starting point (and the current $i$ as the ending point).

3.  **State Transition / Optimization ($i \to i+1$):**
    *   As the sweep-line moves from $i$ to $i + 1$, the values don't change arbitrarily. We **only care about the starting and ending points** of the given segments.
    *   The function $f[j, i]$ *only changes* when $i+1$ happens to be the ending point ($R$) of one or more segments.
    *   Suppose we encounter a segment $K(l, r, w)$ where its right endpoint $r = i + 1$:
        *   This segment will be fully trapped inside our chosen interval $[j, i+1]$ **if and only if** our chosen starting point $j$ is placed before or exactly at $l$ ($j \le l$).
        *   Therefore, we simply need to add the weight $w$ to all scenarios where the starting point $j \le l$.
        *   **Segment Tree Operation:** This translates to a simple Range Update: `update(1, 0, l, w)`.

4.  **Extracting the Answer:**
    *   After processing all segments that end at the current sweep-line position $i$, the maximum value across the entire Segment Tree (`st[1].max_val`) represents the maximum weight achievable if we force our interval to end at $i$.
    *   The final answer to the problem is the global maximum of these root values observed during the entire sweeping process.

## Implementation Notes

*   **Coordinates:** The coordinate space for $l, r$ goes up to $10^6$. This is small enough that we can build the Segment Tree directly over the coordinate domain without needing Coordinate Compression.
*   **Sweep-line Setup:** Use an array of vectors (e.g., `vector<pair<int, int>> ends_at[MAX_VAL]`) to group segments by their ending points. 
    *   Store them as: `ends_at[r].push_back({l, w})`.
*   **Lazy Propagation:** 
    *   `update(id, L, R, u, v, w)`: Adds $w$ to the segment $[u, v]$.
    *   `get_max()`: Returns the maximum value stored at the root of the tree.

## Complexity Analysis
*   **Time Complexity:** Sweeping through the coordinates takes $O(\max R)$. For each of the $N$ segments, we perform exactly one range update which takes $O(\log(\max R))$. Total Time: $O(N \log(\max R))$, easily fitting within the time limits.
*   **Space/Memory Complexity:** $O(\max R)$ for allocating the Segment Tree arrays.