// https://oj.vnoi.info/problem/palinx
#include <bits/stdc++.h>
using namespace std;

const int MaxNode = 2000005;
const int ALPHABET_SIZE = 26;

struct PalindromeChecker
{
    int n;
    const long long MOD = 1e9 + 7;
    const long long BASE = 311;
    vector<long long> h_f, h_b, p;

    PalindromeChecker(const string &s)
    {
        n = s.length();
        h_f.assign(n + 1, 0);
        h_b.assign(n + 1, 0);
        p.assign(n + 1, 1);

        for (int i = 0; i < n; i++)
        {
            p[i + 1] = (p[i] * BASE) % MOD;
            h_f[i + 1] = (h_f[i] * BASE + s[i]) % MOD;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            h_b[i] = (h_b[i + 1] * BASE + s[i]) % MOD;
        }
    }

    bool isPalindrome(int l, int r)
    {
        if (l >= r)
            return true;
        int len = r - l;

        long long f = (h_f[r] - h_f[l] * p[len]) % MOD;
        if (f < 0)
            f += MOD;

        long long b = (h_b[l] - h_b[r] * p[len]) % MOD;
        if (b < 0)
            b += MOD;

        return f == b;
    }
};

struct Node
{
    int child[ALPHABET_SIZE];
    int exist;
    int palin_suffix_cnt;
};
Node nodes[MaxNode];

struct Trie
{
    int trieNodeCount;
    int root;

    int createNode()
    {
        nodes[trieNodeCount].exist = 0;
        nodes[trieNodeCount].palin_suffix_cnt = 0;
        for (int i = 0; i < 26; i++)
            nodes[trieNodeCount].child[i] = -1;
        return trieNodeCount++;
    }

    Trie()
    {
        trieNodeCount = 0;
        root = createNode();
    }

    void addString(const string &s, PalindromeChecker &checker)
    {
        int p = root;
        for (int i = s.length() - 1; i >= 0; i--)
        {

            if (checker.isPalindrome(0, i + 1))
            {
                nodes[p].palin_suffix_cnt++;
            }

            int v = s[i] - 'a';
            if (nodes[p].child[v] == -1)
            {
                nodes[p].child[v] = createNode();
            }
            p = nodes[p].child[v];
        }

        nodes[p].palin_suffix_cnt++;
        nodes[p].exist++;
    }

    long long query(const string &s, PalindromeChecker &checker)
    {
        long long ans = 0;
        int p = root;

        for (int i = 0; i < s.length(); i++)
        {

            if (nodes[p].exist > 0 && checker.isPalindrome(i, s.length()))
            {
                ans += nodes[p].exist;
            }

            int v = s[i] - 'a';
            if (nodes[p].child[v] == -1)
                return ans;
            p = nodes[p].child[v];
        }

        ans += nodes[p].palin_suffix_cnt;
        return ans;
    }
};

void solve()
{
    int n;
    if (!(cin >> n))
        return;
    Trie trie;

    vector<string> strings(n);

    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m >> strings[i];
        PalindromeChecker checker(strings[i]);
        trie.addString(strings[i], checker);
    }

    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        PalindromeChecker checker(strings[i]);
        ans += trie.query(strings[i], checker);
    }

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