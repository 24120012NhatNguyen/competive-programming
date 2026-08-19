// nguon :https://oj.vnoi.info/problem/chain2
#include <bits/stdc++.h>
using namespace std;

struct Trie
{
    struct Node
    {
        int child[26];
        int exist;
        Node()
        {
            fill(child, child + 26, -1);
            exist = 0;
        }
    };
    vector<Node> trie;
    Trie()
    {
        trie.emplace_back();
    }
    void insert(const string &s)
    {
        int u = 0;
        for (const char &c : s)
        {
            int v = c - 'a';
            if (trie[u].child[v] == -1)
            {
                trie[u].child[v] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].child[v];
        }
        trie[u].exist++;
    }
    void dfs(int u, int cur, int &ans)
    {
        bool isleaf = true;
        for (int v = 0; v < 26; v++)
        {
            int idx = trie[u].child[v];
            if (idx == -1)
                continue;
            isleaf = false;
            if (trie[idx].exist > 0)
                dfs(idx, cur + 1, ans);
            else
                dfs(idx, cur, ans);
        }
        if (isleaf == true)
        {
            ans = max(ans, cur);
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    Trie trie;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        trie.insert(s);
    }
    int ans = 0;
    trie.dfs(0, 0, ans);
    cout << ans << "\n";
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
