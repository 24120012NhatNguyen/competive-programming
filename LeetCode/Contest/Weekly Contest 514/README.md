# Segment Tree Data Structure - Counting Peak Subarrays

This repository contains an optimized Segment Tree solution for processing dynamic array queries: counting the number of subarrays containing at least one peak, while supporting point updates.

## Core Logic

The solution discards the traditional additive counting approach (which is prone to overcounting) and applies two core techniques to optimize the query processing:

### 1. Complement Counting

Instead of directly counting valid subarrays, the algorithm calculates the total number of subarrays of length $\ge 3$ and subtracts the subarrays that contain **zero peaks**.

* The total number of subarrays of length $\ge 3$ generated from a segment of length $L$ is calculated using the formula:

$$f(L) = \max\left(0, \frac{(L - 1)(L - 2)}{2}\right)$$


* The invalid subarrays are those located entirely within the intervals between two consecutive peaks.

### 2. State Decoupling

The Segment Tree **does not** directly manage the value array `nums`. Instead, it manages a Boolean state array `isPeak` (0 or 1).

* **External logic:** Responsible for evaluating the peak condition `nums[i] > nums[i-1]` and `nums[i] > nums[i+1]`.
* **Internal tree logic:** Each Node only maintains 4 properties:
* `havepeak`: Boolean state indicating if a peak exists in the current range.
* `fst_peak`: Index of the first peak in the range.
* `lst_peak`: Index of the last peak in the range.
* `val`: The sum $f(L)$ of all intervals between consecutive peaks strictly within this Node.



This decoupling allows the `merge` function to operate in $O(1)$ time with strictly deterministic logic, completely independent of the boundary values of the original array.

## Complexity

* **Time Complexity:**
* Build: $O(N)$
* Update Query: $O(\log N)$ (updates a maximum of 3 adjacent positions: `idx - 1`, `idx`, and `idx + 1`)
* Count Query: $O(\log N)$


* **Space Complexity:** $O(N)$ for the Segment Tree structure of size $4N$.

## Source Code Structure

* `struct Node`: Stores the localized state of an array segment. Constructors are overloaded for rapid initialization of empty Nodes or single-peak Nodes.
* `void update_query(...)`: An arbitrator function that handles boundary evaluations. Upon an element update, it recalculates the state of the 3 affected elements and propagates the updated Boolean signals to the Segment Tree.
* `long long getVal(int l, int r)`: Retrieves the internal intervals from the tree (`tmp.val`) and processes the complement logic for the two outermost boundaries of the query range to return the final valid count.