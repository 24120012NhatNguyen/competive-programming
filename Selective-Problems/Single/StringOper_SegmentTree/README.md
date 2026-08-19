# VNOI: Segment Tree String (segtree_itstr)

[Problem Link](https://oj.vnoi.info/problem/segtree_itstr)

## Problem Description
Manage an initial binary string of length $N$ and process $M$ queries of two types:
1. **Delete (Update):** Remove the character at the current position $P$ (subsequent characters automatically shift left, altering the indices).
2. **Query:** Calculate the decimal value of the substring from the current position $L$ to $R$, modulo $1007050321$.

## Core Technique
**Segment Tree** combined with **Segment Tree Walk** (Binary Search on Segment Tree).

## Key Insights
* **Dynamic to Static Indexing:** Due to the deletion and shifting nature of the array, we cannot query directly using static indices. The `len` attribute is maintained at each node to track the number of undeleted elements in that specific segment.
* **Segment Tree Walk:** We use a `find_kth` operation to traverse from the root down to the leaves in $O(\log N)$ time. This accurately maps the "dynamic index" (at the time of the query) back to its "original index" (on the static array). Only after this mapping can we correctly execute the `update` or `get` functions.
* **String Concatenation Logic:** When `merge`-ing 2 sub-segments, the combined string value (in base 2) is calculated using bit-shifting principles:  
  $val_{parent} = (val_{left} \cdot 2^{len_{right}} + val_{right}) \pmod M$

## Complexity
* **Time Complexity:** 
  * Initialization (Initial Build/Update): $O(N \log N)$
  * Per query (Walk + Update/Get): $O(\log N)$
  * Total Time: $O((N + M) \log N)$
* **Space/Memory:** $O(N)$ for the Segment Tree structure.