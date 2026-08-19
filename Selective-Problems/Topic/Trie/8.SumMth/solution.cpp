// https://codeforces.com/contest/241/problem/B
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

const int ALPHABET_SIZE = 2;
const int MAX_NODE = 1500005;
const int N = 50004;
int n, m;
int a[N];
struct Node
{
    Node *child[ALPHABET_SIZE];
    int cnt;
    int cnt_bit[30];
    Node()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            child[i] = nullptr;
        }
        cnt = 0;
        for (int i = 0; i < 30; i++)
        {
            cnt_bit[i] = 0;
        }
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

            for (int i = 29; i >= 0; i--)
            {
                if ((num >> i) & 1)
                {
                    p->cnt_bit[i] += 1;
                }
            }
        }
    }
    long long get_xor_sum(Node *p, int x)
    {
        if (!p)
            return 0LL;
        long long ans = 0LL;
        for (int i = 0; i <= 29; i++)
        {
            int bitX = (x >> i) & 1;
            if (bitX == 0)
            {
                ans += 1LL * p->cnt_bit[i] * (1 << i);
                ans = ans % MOD;
            }
            else
            {
                ans += 1LL * (p->cnt - p->cnt_bit[i]) * (1 << i);
                ans = ans % MOD;
            }
        }
        return ans;
    }

    long long check(int mid, long long &ans)
    {
        long long num = 0LL;
        long long sum = 0LL;
        for (int i = 1; i <= n; i++)
        {
            Node *p = root;
            for (int exp = 29; exp >= 0; exp--)
            {
                if (p == nullptr)
                    break;
                int bitA = (a[i] >> exp) & 1;
                int bitX = (mid >> exp) & 1;

                int opp = 1 - bitA;
                if (bitX == 0)
                {
                    if (p->child[opp])
                    {
                        num += (p->child[opp])->cnt;
                        sum = (sum + get_xor_sum(p->child[opp], a[i])) % MOD; // SỬA: Gom modulo cho gọn
                    }
                    p = p->child[1 - opp];
                }
                else
                {
                    p = p->child[opp];
                }
            }
            if (p != nullptr)
            {
                num += p->cnt;
                sum = (sum + get_xor_sum(p, a[i])) % MOD;
            }
        }
        ans = sum;
        return num;
    }
};

void solve()
{
    cin >> n >> m;
    Trie trie;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        trie.add(a[i]);
    }

    long long l = 0, r = (1LL << 30) - 1;
    long long ans = 0LL;
    long long sum = 0LL;

    while (l <= r)
    {
        long long mid = l + (r - l) / 2;
        long long num = trie.check(mid, ans);

        if (num >= 2LL * m)
        {
            long long excess_pairs = (num - 2LL * m) % MOD;
            long long excess_sum = (excess_pairs * (mid % MOD)) % MOD;

            sum = (ans - excess_sum + MOD) % MOD;

            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << (sum * 500000004LL) % MOD << "\n";
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
