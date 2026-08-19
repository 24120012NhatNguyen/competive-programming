# Palindrome Pairs

## Problem Statement

Given an array of $N$ strings, the objective is to find the total number of pairs $(i, j)$ such that the concatenation of the $i$-th string and the $j$-th string ($S_i + S_j$) forms a palindrome.

## Algorithmic Approach

The optimal solution eliminates the need for checking both $S+T$ and $T+S$ dynamically by utilizing an **Offline Processing** strategy alongside a **Reversed Trie** and **String Hashing**. This reduces the problem to only verifying the $S+T$ condition, as the sequence of iterations handles the reciprocal pairs inherently.

### 1. Data Structures

* **Palindrome Checker (Rolling Hash):** Precomputes forward and backward hashes for each string in $O(L)$ time, where $L$ is the string length. This enables $O(1)$ verification for whether any substring $[l, r)$ is a palindrome.
* **Index-based Reversed Trie:** Strings are inserted into the Trie in reverse order ($rev(T)$). Instead of pointers, an array-based implementation is utilized to guarantee strict memory efficiency. Each node contains two state variables:
* `exist`: Tracks the number of strings that terminate exactly at this node.
* `palin_suffix_cnt`: Tracks the number of strings passing through this node whose remaining uninserted prefix forms a palindrome.



### 2. Execution Flow

#### Phase 1: Offline Precomputation (Insertion)

Iterate through all strings and insert them into the Trie.
For a given string $T$, characters are inserted in reverse order. At each step of the insertion, before traversing to the child node, evaluate the uninserted segment of $T$. If this remaining segment is a palindrome (verified in $O(1)$ via hashing), increment the `palin_suffix_cnt` at the current node. If the traversal is completed, increment the `exist` counter at the final node.

#### Phase 2: Querying

Iterate through all strings again. For each string $S$, traverse the Trie character by character:

* **Case 1 ($\vert{}S\vert{} > \vert{}T\vert{}$):** If the traversal encounters a node where `exist > 0`, it implies a string $T$ in the dataset fully matches a prefix of $S$. Use the Hash checker to verify if the remaining suffix of $S$ is a palindrome. If true, add the `exist` value to the total answer.
* **Case 2 ($\vert{}S\vert{} \le \vert{}T\vert{}$):** If the traversal of string $S$ completes successfully and lands on a node $U$, it implies $S$ fully matches the suffix of one or more strings in the Trie. Add `U.palin_suffix_cnt` to the total answer. This operation runs in $O(1)$ and bypasses the need for Deep First Search (DFS), strictly avoiding time limit exceed (TLE) errors.

## Complexity Analysis

* **Time Complexity:**
* **Hash Precomputation:** $O(\sum \vert{}S_i\vert{})$
* **Trie Insertion:** $O(\sum \vert{}S_i\vert{})$
* **Trie Querying:** $O(\sum \vert{}S_i\vert{})$
* **Overall Time Complexity:** $O(\sum \vert{}S_i\vert{})$. The algorithm operates in linear time relative to the total length of all strings in the dataset.


* **Space Complexity:** $O(\sum \vert{}S_i\vert{} \times \vert{}\Sigma\vert{})$, where $\vert{}\Sigma\vert{} = 26$ (the alphabet size). The index-based Trie allocation heavily limits memory overhead, remaining well within standard 256MB constraints for typical competitive programming environments.