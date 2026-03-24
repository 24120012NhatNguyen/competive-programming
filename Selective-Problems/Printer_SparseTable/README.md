# Persistent Text Editor (IOI 2012 - Crayfish Scrivener)
## 1. Problem Origin & Testing Platforms
This project is an implementation of the classic competitive programming problem **"Crayfish Scrivener"**, originally featured in the **International Olympiad in Informatics (IOI) 2012, Day 1**.

LINK TO PROBLEM STATEMENT: https://ioinformatics.org/files/ioi2012problem3.pdf
THE JUDGE LINKS IS PRIVATE, BUT THE PROBLEM STATEMENT IS PUBLICLY AVAILABLE IN THE PDF ABOVE.

## 2. Problem Statement
Design a data structure that simulates a text editor supporting the following operations efficiently over $N$ queries ($N \le 10^6$):
* `TypeLetter(c)`: Appends character `c` to the end of the text.
* `UndoCommands(k)`: Reverts the text to the exact state it was in `k` operations ago. Note that undoing an undo operation acts as a redo.
* `GetLetter(x)`: Returns the character at the 0-indexed position `x` in the current text. This operation is a query and does not affect the command history.

## 3. Naive Approach Limitations
A naive solution maintaining a dynamic array of strings (`std::vector<std::string>`) to record states would require copying the entire string per operation. This yields:
* **Time Complexity:** $O(N^2)$ due to string duplication.
* **Space Complexity:** $O(N^2)$ leading to immediate Memory Limit Exceeded (MLE).

```cpp

    vector<string> ans;
    string cur = "";
    ans.push_back(cur);
 
    for(int i = 1; i <= n; i++) {
        char c; cin >> c;
        if(c == 'T') {
            char a; cin >> a;
            cur += a;
            ans.pb(cur);
        }
        else if(c == 'U') {
            int k; cin >> k;
            // i -> i - k
            cur = ans[ans.size() - 1 - k];
            ans.pb(cur);
        }
        else {
            int x; cin >> x;
            cout << cur[x] << "\n";
        }
    }
```

## 4. Architecture & Optimal Solution
To achieve strict optimal bounds, the solution implements a **Persistent Data Structure** utilizing a **Version Tree (Persistent Trie)** coupled with **Binary Lifting (Sparse Table)**.

### 4.1. Version Tree for Immutable States
Instead of storing contiguous memory blocks for strings, the text is represented as a path on a directed tree from the Root (empty string) to a specific node.
* The Root (Node 0) has depth 0.
* `TypeLetter(c)` operation creates a new node $u$ as a child of the current node $p$. The character `c` is stored at $u$, and `depth[u] = depth[p] + 1`.
* Memory mutation is avoided. The tree strictly grows, preserving all historical paths.

### 4.2. $O(1)$ State Rollback (Time Travel)
State management is handled via a mapping array `pos`, where `pos[i]` stores the ID of the terminal node corresponding to the state after the $i$-th operation.
* For `UndoCommands(k)` at step $i$, the system performs an $O(1)$ pointer assignment: `pos[i] = pos[i - 1 - k]`.
* By referencing existing nodes rather than deleting nodes, the structure trivially supports cascading undos and redos without data loss.

### 4.3. Binary Lifting for $O(\log N)$ Ancestor Queries
The `GetLetter(x)` operation asks for the character at index `x` of a string of length `D`.
* In the tree topology, this translates to finding the $(D - 1 - x)$-th ancestor of the current node.
* A Sparse Table (`up[LG][N]`) is maintained where `up[j][u]` stores the $2^j$-th ancestor of node $u$.
* The ancestor is located in $O(\log N)$ time by jumping via the binary representation of the required distance.

## 5. Complexity Analysis
* **Time Complexity:**
    * `TypeLetter(c)`: $O(\log N)$ (Building the Sparse Table for the new node).
    * `UndoCommands(k)`: $O(1)$ (Array assignment).
    * `GetLetter(x)`: $O(\log N)$ (Tree traversal).
    * **Total Time:** $O(N \log N)$ amortized, well within the standard 1.0s - 2.0s limits.
* **Space Complexity:** $O(N \log N)$ (Dominated by the Sparse Table `up[21][N]`).


