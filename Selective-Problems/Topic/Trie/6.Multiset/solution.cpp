// https://codeforces.com/problemset/problem/706/D
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1337377;

const int ALPHABET_SIZE = 2;
const int MAX_NODE = 6000005;
struct Node
{
    Node *child[ALPHABET_SIZE];
    int cnt;
    Node()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            child[i] = nullptr;
        }
        cnt = 0;
    }
};
Node node[MAX_NODE];
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
        node[trieNodeCount].cnt = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            node[trieNodeCount].child[i] = nullptr;
        }
        return &node[trieNodeCount++];
    }

    void add(int num)
    {
        Node *p = root;
        for (int exp = 29; exp >= 0; exp--)
        {
            int pos = (num >> exp) & 1;
            if (p->child[pos] == nullptr)
            {
                p->child[pos] = createNode();
            }
            p = p->child[pos];
            p->cnt++;
        }
    }
    void del(int num)
    {
        Node *p = root;
        for (int exp = 29; exp >= 0; exp--)
        {
            int pos = (num >> exp) & 1;
            p = p->child[pos];
            p->cnt--;
        }
    }
    int xd(int num)
    {
        int ans = 0;
        Node *p = root;
        for (int exp = 29; exp >= 0; exp--)
        {
            int pos = (num >> exp) & 1;
            if (p->child[1 - pos] != nullptr and (p->child[1 - pos])->cnt > 0)
            {
                p = p->child[1 - pos];
                ans += (1 << exp);
                continue;
            }
            if (p->child[pos] != nullptr and p->child[pos]->cnt > 0)
            {
                p = p->child[pos];
                continue;
            }
        }
        return ans;
    }
};

void solve()
{
    int q;
    cin >> q;
    Trie trie;
    trie.add(0);
    for (int i = 1; i <= q; i++)
    {
        char x;
        int y;
        cin >> x >> y;
        if (x == '+')
        {
            trie.add(y);
        }
        else if (x == '-')
        {
            trie.del(y);
        }
        else
        {
            cout << trie.xd(y) << "\n";
        }
    }
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
