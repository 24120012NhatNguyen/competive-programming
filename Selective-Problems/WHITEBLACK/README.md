# VNOI: LEM4 - Mây Trắng

[Problem Link](https://oj.vnoi.info/problem/lem4)

## Overview

This repository contains a solution for managing an array of $N$ elements (initially all white) and processing $M$ queries of three types:

1. **Assign White (0):** Set all elements in range $[L, R]$ to white.
2. **Assign Black (1):** Set all elements in range $[L, R]$ to black.
3. **Query:** Find the maximum length of a continuous contiguous subarray of white elements.

## Core Technique

**Segment Tree with Lazy Propagation** tailored for the **Longest Contiguous Subarray (LCS)** problem.

## Node State Design

To dynamically maintain the longest continuous sequence of white elements, a single variable is insufficient. Each node in the Segment Tree must track boundary states to allow cross-boundary merging.

* `val`: The length of the maximum continuous white segment strictly within this node.
* `head`: The length of the maximum continuous white segment starting from the left boundary (prefix).
* `tail`: The length of the maximum continuous white segment ending at the right boundary (suffix).
* `has_black`: A boolean flag indicating if the segment contains at least one black element. (If `false`, the entire segment is pure white).
* `lz`: Lazy tag for pending range updates (`-1` = unassigned, `0` = set to white, `1` = set to black).

## Merge Logic ($O(1)$)

When merging two child nodes, `left` and `right`, into a parent node `c`:

1. **Prefix (`head`):** Starts as `left.head`. If the `left` child is entirely white (`left.has_black == 0`), the white prefix stretches across the boundary into the right child: $c.head = left.head + right.head$.
2. **Suffix (`tail`):** Starts as `right.tail`. If the `right` child is entirely white (`right.has_black == 0`), the white suffix stretches backward into the left child: $c.tail = right.tail + left.tail$.
3. **Max Value (`val`):** The longest sequence is the maximum of three candidates:
* The longest sequence fully inside `left` ($left.val$).
* The longest sequence fully inside `right` ($right.val$).
* The sequence formed by bridging the gap across the boundary: ($left.tail + right.head$).


4. **Purity Flag (`has_black`):** $c.has\_black = left.has\_black \mid right.has\_black$.

## Lazy Propagation (Down)

When pushing updates down to children:

* **Assign White (`lz = 0`):** `has_black = 0`, and `head`, `tail`, `val` all become the full length of the segment.
* **Assign Black (`lz = 1`):** `has_black = 1`, and `head`, `tail`, `val` all become $0$.

## Complexity

* **Time Complexity:**
* Initialization: $O(N)$
* Range Update: $O(\log N)$
* Global Query: $O(1)$ (Directly fetching `st[1].val`)
* Total Time: $O(M \log N)$


* **Space Complexity:** $O(N)$ for Segment Tree structures.