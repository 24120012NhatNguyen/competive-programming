

# SEC - Message Interception (VNOI)

## Problem Description

We are given a system that intercepts messages. There is a known dictionary of $M$ secret messages and $N$ intercepted queries.

A secret message is considered a "match" for an intercepted query if one string is a **prefix** of the other. For each intercepted query, the program must output the total number of matching secret messages.

* **Constraints:** $M, N \le 50,000$. The total length of all strings is up to $5 \times 10^5$.
* **Source:** [VNOI - SEC](https://oj.vnoi.info/problem/sec)

---

## Algorithmic Analysis

Given the large constraints on the total string length, a Naïve String Matching approach $O(M \times N \times L)$ will immediately result in a Time Limit Exceeded (TLE). The optimal data structure to handle prefix-related queries efficiently is a **Trie (Prefix Tree)**.

### Node Structure

Each node in the Trie maintains two crucial state variables:

1. `cnt`: The number of strings passing through this node (representing the count of strings that have the path from the root to this node as a prefix).
2. `exist`: The number of strings that terminate exactly at this node.

---

## The Double-Counting Dilemma & "Strict Prefix" Solution

When a query string $S$ is evaluated, the matching secret messages fall into two categories:

1. Secret messages that have $S$ as a prefix (longer than or equal to $S$).
2. Secret messages that are prefixes of $S$ (shorter than or equal to $S$).

A common pitfall is computing these two sets independently and summing them up. This causes the strings that are **exactly equal to $S$** (the intersection of the two sets) to be counted twice.

To cleanly resolve this boundary issue without complex inclusion-exclusion logic, the solution is divided into two distinct, strictly defined functions:

### 1. `countExtensions(S)`

This function handles strings that are greater than or equal to $S$.

* It traverses the Trie using the characters of $S$.
* If the path breaks, it returns $0$.
* If it successfully reaches the end of $S$, it returns the `cnt` value of the final node. This inherently includes strings exactly equal to $S$.

### 2. `countStrictPrefixes(S)`

This function handles strings that are strictly shorter than $S$ (Strict Prefixes).

* It traverses the Trie along the characters of $S$.
* At each step, it accumulates the `exist` value of the current node into a running total.
* **The Fix:** The iteration strictly stops *before* the final character of $S$ (or explicitly ignores the `exist` value at the final node). This guarantees that strings exactly equal to $S$ are safely ignored in this function, completely eliminating the double-counting overlap.

**Final Answer:** For each query $S$, the exact number of matches is simply `countExtensions(S) + countStrictPrefixes(S)`.

---

## Complexity

* **Time Complexity:**
* Trie Construction: $O(\sum \vert{}M_i\vert{})$
* Querying: $O(\sum \vert{}N_i\vert{})$
* **Overall:** $O(L_{total})$. The time complexity is strictly linear concerning the length of the strings, operating independently of the number of messages.


* **Space Complexity:** $O(\sum \vert{}M_i\vert{} \times \vert{}\Sigma\vert{})$, where $\vert{}\Sigma\vert{} = 2$ (binary alphabet consisting of '0' and '1'). The static array allocation via `std::vector` ensures optimal CPU Cache locality and prevents memory fragmentation.