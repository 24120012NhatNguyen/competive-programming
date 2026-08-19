# Word Break - VNOI NKSEV

**Problem Details:** (https://oj.vnoi.info/problem/nksev)

## Problem Description

Given a string $T$ with a maximum length of $300,000$ characters and a dictionary consisting of $N$ words ($N \le 4000$), where each word has a maximum length of $100$ characters.

The objective is to determine the total number of ways to partition the string $T$ into substrings such that every substring is a valid word present in the dictionary.

Since the result can be exceptionally large, the output must be the answer modulo **1337377**.

---

## Algorithmic Analysis

This is a classic problem that can be optimally solved using **Dynamic Programming (DP)** combined with an advanced string processing data structure.

Let `dp[i]` denote the number of valid ways to partition the prefix of string $T$ of length `i`.

* **Base case:** `dp[0] = 1` (There is exactly 1 way to partition an empty string).
* **State transition:**

$$dp[i] = \sum dp[j-1]$$



*(for all $j \le i$ such that the substring $T[j \dots i]$ exists in the dictionary)*

Given the constraints ($\vert{}T\vert{} \le 300,000$ and maximum word length $L \le 100$), optimizing the dictionary lookup for $T[j \dots i]$ is strictly crucial to avoid a Time Limit Exceeded (TLE) verdict.

---

## Why Hashing Leads to TLE

A common initial approach is to utilize a **Rolling Hash** or a data structure like `std::set<string>` to store and query the dictionary.

If we use a sorted array with Binary Search or a Red-Black Tree (`std::set`):

1. At each position `i` (from $1$ to $\vert{}T\vert{}$), the inner pointer `j` steps backwards up to $L = 100$ times.
2. For each formed substring $T[j \dots i]$, querying the dictionary takes $O(\log N)$ time.
3. **Overall Time Complexity:** **$O(\vert{}T\vert{} \times L \times \log N)$**.

In practice, this requires roughly $300,000 \times 100 \times \log_2(4000) \approx 3.6 \times 10^7$ operations. While theoretically this might pass within a 1-second time limit, the **hidden constants** associated with string hashing, modulo arithmetic, or pointer chasing in `std::set` are massively impactful. Frequent "Cache Misses" during tree traversals or binary searches severely degrade execution speed, consistently resulting in TLE on stricter test cases.

---

## The Optimization: Trie (Prefix Tree)

To completely eliminate the $\log N$ overhead, we implement a **Trie**. Instead of treating each word as an isolated string and hashing it, a Trie allows the algorithm to gracefully exploit shared prefixes.

Since our DP state transition computes `dp[i]` by extending `j` backwards, we must **insert the reversed words** from the dictionary into the Trie (inserting character by character from right to left).

During the computation of `dp[i]`:

1. We start at the root of the Trie and traverse down using the sequence of characters: $T[i], T[i-1], \dots, T[i-100]$.
2. Each edge traversal takes **$O(1)$** time via a static `child[26]` array.
3. If we reach a node where `exist > 0` (indicating the end of a valid dictionary word), we immediately accumulate the DP value: `dp[i] = (dp[i] + dp[j-1]) % MOD`.
4. If we encounter a dead end (an edge initialized to `-1`), we instantly `break` the inner loop because no further valid substrings can possibly be formed.

### Complexity

* **Time Complexity:** **$O(\vert{}T\vert{} \times L)$**. The Trie structure thoroughly removes the $\log N$ search factor, and the constant time for array indexing is minuscule.
* **Space Complexity:** $O(N \times L \times 26 + \vert{}T\vert{})$. This memory footprint is highly manageable and easily fits within standard competitive programming limits.

---

## Implementation Notes

The accompanying C++ solution leverages a `struct Node` integrated with `std::vector` to implement **Index-based Pointers**. This is a highly optimized technique in competitive programming that ensures contiguous memory allocation (maximizing CPU Cache hits), circumvents the overhead of dynamic allocation (`new`), and guarantees immunity against segmentation faults and memory leaks.