# Top M Maximum XOR Pairs

## Problem Statement

Given an array $A$ of $N$ integers, the objective is to find the sum of the $M$ largest XOR pairs $(A[i] \oplus A[j])$.

## Algorithmic Approach

The optimal solution utilizes a combination of **Binary Search on Answer** and a **Bitwise Trie**. Instead of finding the exact $M$-th largest XOR value directly, we binary search for a threshold value $X$. For a candidate threshold $X$, the Trie allows us to efficiently count how many pairs yield an XOR sum $\ge X$ and simultaneously compute their total sum.

### 1. Data Structures

* **Bitwise Trie**: Stores the binary representation of each number in the array, typically up to 30 bits.
* **State Variables per Node**:
* `cnt`: The number of elements passing through the current node.
* `cnt_bit[30]`: An array precomputing the bit distribution. `cnt_bit[k]` stores the number of elements within this node's subtree that have the $k$-th bit set to 1.



### 2. Core Operations

#### Constant-Time Subtree XOR Sum (`get_xor_sum`)

To compute the sum of $A[i] \oplus Y$ for all elements $Y$ residing in a specific Trie subtree without iterating through them, we use the `cnt_bit` array. This operation runs in $O(30)$ time.
For each bit position $k \in [0, 29]$:

* If the $k$-th bit of $A[i]$ is 0, elements in the subtree contributing a 1 to the final XOR result are exactly those with the $k$-th bit set (`cnt_bit[k]`).
* If the $k$-th bit of $A[i]$ is 1, elements contributing a 1 to the final XOR result are those with the $k$-th bit unset (`cnt - cnt_bit[k]`).

#### Threshold Verification (`check(mid)`)

For a candidate threshold `mid`, we traverse the Trie for each $A[i]$ to find all elements $A[j]$ satisfying $A[i] \oplus A[j] \ge mid$:

* If the current bit of `mid` is 0, the Trie branch producing a 1 in the XOR result guarantees a final value strictly greater than `mid`. We instantly add its subtree `cnt` to the pair count and its subtree XOR sum to the total sum. The traversal then proceeds down the branch producing a 0.
* If the current bit of `mid` is 1, we must proceed down the branch producing a 1 to maintain the possibility of meeting the threshold.
* If the traversal successfully reaches a leaf node (or finishes all bits), the resulting XOR is exactly equal to `mid`. These elements are processed and added to the count and sum.

#### Binary Search and Excess Handling

We binary search the threshold $X$ in the range $[0, 2^{30}-1]$. Since pairs are processed directionally (both $(i, j)$ and $(j, i)$ are visited), we target $2M$ pairs.
When the threshold check returns a count $\ge 2M$, it is possible that multiple pairs yield the exact XOR value $X$, causing the count to overshoot $2M$. This is corrected by subtracting the excess contribution: `excess_sum = (total_pairs - 2M) * X`. The final valid sum is then halved to account for bidirectional counting.

## Complexity Analysis

* **Time Complexity**: $O(N \log(\max A) \log(\max A))$. The binary search requires 30 iterations. Each iteration processes $N$ elements, and both Trie traversal and `get_xor_sum` take $O(30)$ operations.
* **Space Complexity**: $O(N \log(\max A))$. The Trie allocates at most $30 \times N$ nodes. With state arrays embedded in each node, memory allocation remains well within standard competitive programming limits (e.g., 256MB).