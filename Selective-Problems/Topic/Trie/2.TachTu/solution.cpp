// nguon :https://oj.vnoi.info/problem/nksev
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1337377;
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
};

void solve()
{
    string T;
    cin >> T;
    int m = T.length();
    T = " " + T;
    int n;
    cin >> n;
    Trie trie;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        trie.insert(s);
    }
    vector<int> dp(m + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= m; i++)
    {
        int u = 0;
        for (int j = i; j >= max(i - 100, 1); j--)
        {
            int x = T[j] - 'a';
            if (trie.trie[u].child[x] == -1)
                break;
            u = trie.trie[u].child[x];
            if (trie.trie[u].exist > 0)
            {
                dp[i] += dp[j - 1];
                if (dp[i] >= MOD)
                    dp[i] -= MOD;
            }
        }
    }
    cout << dp[m] % MOD << "\n";
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
