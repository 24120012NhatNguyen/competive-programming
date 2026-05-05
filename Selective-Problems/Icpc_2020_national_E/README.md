# VNOI ICPC 2020 National E: Equation

[Problem Link](https://oj.vnoi.info/problem/icpc20_national_e)

## Overview
This repository contains a $O(\log N)$ solution for dynamically evaluating mathematical expressions containing digits (`0-9`), addition (`+`), and subtraction (`-`). The problem requires handling point updates (changing a character) and range queries (evaluating the substring mathematically) modulo $998244353$.

## Technical Architecture

The core of the solution is built on a **Segment Tree** designed to maintain algebraic properties of substrings. Since a substring might not form a fully resolved mathematical expression (e.g., `12+34-5`), the tree must carefully manage boundary terms.

### Node State Design
Each node in the Segment Tree operates in one of two distinct states, tracked by the boolean flag `has_op`:

**1. Pure Numeric State (`has_op = false`)**
The segment contains only digits.
* `val`: The numeric value of the sequence $\pmod M$.
* `len_val`: The number of digits (used for base-10 shifting during concatenation).

**2. Operator-Contained State (`has_op = true`)**
The segment contains at least one operator (`+` or `-`). The segment is partitioned into three logical components: `Prefix`, `Middle`, and `Suffix`.
* `fi`, `len_fi`: The unresolved number *before* the first operator.
* `sign_fi`: The operator immediately following the prefix.
* `val_mid`: The fully resolved algebraic sum of all terms trapped *between* the first and last operators.
* `se`, `len_se`: The unresolved number *after* the last operator.
* `sign_se`: The operator immediately preceding the suffix.

### Merge Logic ($O(1)$)
Merging two adjacent nodes, `left` and `right`, depends on their states:

1. **Both Pure Numbers:** Concatenate mathematically: 
   $val_{new} = (val_{left} \cdot 10^{len\_val_{right}} + val_{right}) \pmod M$
2. **Left Pure, Right Has Operator:** The `left` value shifts and merges into the `fi` (prefix) of the `right` node.
3. **Left Has Operator, Right Pure:** The `right` value merges into the `se` (suffix) of the `left` node.
4. **Both Have Operators:** 
   * The new prefix is strictly the prefix of `left`.
   * The new suffix is strictly the suffix of `right`.
   * The new `val_mid` is the sum of `left.val_mid`, `right.val_mid`, and the newly formed term in the middle: $sign\_se_{left} \times (se_{left} \cdot 10^{len\_fi_{right}} + fi_{right}) \pmod M$.

### Evaluation
For any range query $[L, R]$, the final answer is computed by forcefully resolving the unclosed prefix and suffix of the returned Node:
$Result = (fi + val\_mid + sign\_se \times se) \pmod M$

## Complexity
* **Time:** 
  * Tree Construction: $O(N)$
  * Point Update: $O(\log N)$
  * Range Evaluation: $O(\log N)$
* **Space:** $O(N)$ for Segment Tree allocation.