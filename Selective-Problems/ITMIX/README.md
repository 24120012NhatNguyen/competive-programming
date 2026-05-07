# VNOI: Segment Tree Mix (segtree_itmix)

[Problem Link](https://oj.vnoi.info/problem/segtree_itmix)

## Overview
This repository contains a solution for managing an array of size $N$ with $M$ operations, supporting three types of range updates and one range query:
1. **Add:** Increase all elements in $[l, r]$ by $v$.
2. **Multiply:** Multiply all elements in $[l, r]$ by $v$.
3. **Assign:** Set all elements in $[l, r]$ to $v$.
4. **Query:** Calculate the sum of elements in $[l, r] \pmod{10^9+7}$.

## Core Technique
**Segment Tree with Lazy Propagation** using **Linear Transformations**. 

Instead of maintaining separate, complex rules for how addition, multiplication, and assignment interact, this solution generalizes all operations into a single linear function applied to the segment.

## Mathematical Model (First Principles)

Any of the three update operations can be represented as a linear transformation $f(V) = V \cdot X + Y$, where $V$ is the current value.

*   **Type 1 (Add $v$):** $X = 1, Y = v \implies V \cdot 1 + v$
*   **Type 2 (Multiply $v$):** $X = v, Y = 0 \implies V \cdot v + 0$
*   **Type 3 (Assign $v$):** $X = 0, Y = v \implies V \cdot 0 + v$

### Lazy Tag Composition
When a node already has pending updates represented by tags $(A_{old}, B_{old})$ and receives a new operation $(X_{new}, Y_{new})$, the operations compose mathematically. 

For a single element $v$, the current pending value is $(v \cdot A_{old} + B_{old})$. Applying the new transformation yields:
$$ (v \cdot A_{old} + B_{old}) \cdot X_{new} + Y_{new} $$
$$ = v \cdot (A_{old} \cdot X_{new}) + (B_{old} \cdot X_{new} + Y_{new}) $$

This proves we can seamlessly merge the new operation into the existing lazy tags without losing information:
*   **New Multiplier (`mul`):** $A_{new} = A_{old} \cdot X_{new}$
*   **New Adder (`add`):** $B_{new} = B_{old} \cdot X_{new} + Y_{new}$

### Node Value Update
When updating the sum of a segment of length $L$ with transformation $(X, Y)$:
*   The sum of all $V \cdot X$ terms is $\text{Sum} \cdot X$.
*   The sum of all $Y$ terms is $Y \cdot L$.
*   **New Segment Sum:** $\text{Sum}_{new} = (\text{Sum}_{old} \cdot X + Y \cdot L) \pmod M$.

## Implementation Details
*   `st` array: Stores the sum of the segments.
*   `mul` array: Stores the $A$ coefficient (initialized to 1).
*   `add` array: Stores the $B$ coefficient (initialized to 0).
*   The `down(id, l, r)` function directly implements the algebraic distribution logic to push $(A, B)$ to children nodes $2 \cdot id$ and $2 \cdot id + 1$.

## Complexity
*   **Time Complexity:** 
    *   Build: $O(N)$
    *   Point/Range Updates: $O(\log N)$ per query.
    *   Range Queries: $O(\log N)$ per query.
    *   Total Time: $O(N + M \log N)$
*   **Space Complexity:** $O(N)$ for Segment Tree arrays.