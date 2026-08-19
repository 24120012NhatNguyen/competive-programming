// nguon :https://oj.vnoi.info/problem/sec
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1337377;
struct Trie
{
    struct Node
    {
        int child[2];
        int cnt;
        int exist;
        Node()
        {
            fill(child, child + 2, -1);
            cnt = 0;
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
            int v = c - '0';
            if (trie[u].child[v] == -1)
            {
                trie[u].child[v] = trie.size();
                trie.emplace_back();
            }
            u = trie[u].child[v];
            trie[u].cnt++;
        }
        trie[u].exist++;
    }
    int countA(const string &s)
    {
        int u = 0;
        for (const char &c : s)
        {
            int v = c - '0';
            if (trie[u].child[v] == -1)
                return 0;
            u = trie[u].child[v];
        }
        return trie[u].cnt;
    }
    int countB(const string &s)
    {
        int u = 0;
        int cnt = 0;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            int v = c - '0';
            if (trie[u].child[v] == -1)
                return cnt;
            u = trie[u].child[v];
            if (i < s.length() - 1 and trie[u].exist > 0)
            {
                cnt += trie[u].exist;
            }
        }
        return cnt;
    }
};

void solve()
{
    int m, n;
    cin >> m >> n;
    Trie trie;
    for (int i = 0; i <= m - 1; i++)
    {
        int x;
        cin >> x;
        string s;
        s.reserve(x);
        for (int i = 1; i <= x; i++)
        {
            char m;
            cin >> m;
            s.push_back(m);
        }
        trie.insert(s);
    }
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        string s;
        s.reserve(x);
        for (int i = 1; i <= x; i++)
        {
            char m;
            cin >> m;
            s.push_back(m);
        }

        cout << trie.countA(s) + trie.countB(s) << "\n";
    }
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
