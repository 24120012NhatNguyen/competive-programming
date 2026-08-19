// https://oj.vnoi.info/problem/trie_tprinter
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1337377;

const int ALPHABET_SIZE = 26;
const int MAX_NODE = 1000001;
struct Node
{
    Node *child[ALPHABET_SIZE];
    int exist;
    bool islongest;
    Node()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            child[i] = nullptr;
        }
        exist = 0;
        islongest = false;
    }
};

int ans = 0;
string ops;
Node nodes[MAX_NODE];

struct Trie
{
    int trieNodeCount;
    Node *root;

    Trie()
    {
        trieNodeCount = 0;
        root = createNode();
    }

    Node *createNode()
    {
        nodes[trieNodeCount].exist = 0;
        nodes[trieNodeCount].islongest = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            nodes[trieNodeCount].child[i] = nullptr;
        }
        return &nodes[trieNodeCount++];
    }

    void addString(const string &s)
    {
        Node *p = root;
        for (char c : s)
        {
            int v = c - 'a';
            if (p->child[v] == nullptr)
            {
                p->child[v] = createNode();
            }
            p = p->child[v];
        }
        p->exist++;
    }
    void mark(string &s)
    {
        Node *p = root;
        for (char c : s)
        {
            int v = c - 'a';
            p = p->child[v];
            p->islongest = true;
        }
    }
    void dfs(Node *u)
    {
        for (int i = 0; i < u->exist; i++)
        {
            ops.push_back('P');
        }
        int longest = -1;
        for (int v = 0; v < 26; v++)
        {
            Node *son = u->child[v];
            if (son != nullptr)
            {
                if (son->islongest)
                {
                    longest = v;
                }
                else
                {
                    ops.push_back(char(v + 'a'));
                    dfs(son);
                    ops.push_back('-');
                }
            }
        }
        if (longest != -1)
        {
            ops.push_back(char(longest + 'a'));
            dfs(u->child[longest]);
        }
    }
};
void solve()
{
    int n;
    cin >> n;
    string pos = "";
    Trie trie;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s.size() > pos.size())
            pos = s;
        trie.addString(s);
    }
    trie.mark(pos);
    trie.dfs(trie.root);
    cout << ops.size() << "\n"
         << ops;
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}
