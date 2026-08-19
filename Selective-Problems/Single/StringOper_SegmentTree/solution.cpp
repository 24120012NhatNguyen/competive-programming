#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int, int>;
const int MX = 100005;
string s;
int q;
int pow2[100005];
int MOD = 1007050321;
void init_pow()
{
    pow2[0] = 1;
    for (int i = 0; i <= 100003; i++)
    {
        pow2[i + 1] = pow2[i] * 2 % MOD;
    }
}
struct Node
{
    int val = 0;
    int len = 0;
    Node() : val(0), len(0) {};
} st[4 * MX + 100];
Node merge(Node &left, Node &right)
{
    Node fa;
    if (left.len == 0)
    {
        fa = right;
        return fa;
    }
    if (right.len == 0)
    {
        fa = left;
        return fa;
    }
    fa.len = left.len + right.len;
    fa.val = (left.val * pow2[right.len] % MOD + right.val) % MOD;
    return fa;
}
void update(int id, int l, int r, int pos, char value)
{
    if (pos > r || pos < l)
    {
        return;
    }
    if (l == r)
    {
        // thao tac xoa phan tu o vi tri pos
        if (value == '-')
        {
            st[id].len = 0;
            st[id].val = 0;
            return;
        }
        st[id].len = 1;
        st[id].val = (value == '0') ? 0 : 1;
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, pos, value);
    update(2 * id + 1, mid + 1, r, pos, value);
    st[id] = merge(st[2 * id], st[2 * id + 1]);
}
Node get(int id, int l, int r, int u, int v)
{
    if (u > r || l > v)
        return Node();
    if (u <= l and r <= v)
    {
        return st[id];
    }
    int mid = (l + r) / 2;
    Node left = get(2 * id, l, mid, u, v);
    Node right = get(2 * id + 1, mid + 1, r, u, v);
    return merge(left, right);
}
// tim idx that su cua pos trong mang
int find_idx(int id, int l, int r, int pos)
{
    int mid = (l + r) / 2;
    if (l == r)
    {
        return l;
    }
    if (st[2 * id].len >= pos)
    {
        return find_idx(2 * id, l, mid, pos);
    }
    else
    {
        return find_idx(2 * id + 1, mid + 1, r, pos - st[2 * id].len);
    }
}
void solve()
{
    init_pow();
    string s;
    cin >> s;
    int n = s.length();
    s = " " + s;
    int m;
    cin >> m;
    for (int i = 1; i <= n; i++)
    {
        update(1, 1, n, i, s[i]);
    }
    while (m--)
    {
        char qu;
        cin >> qu;
        if (qu == '-')
        {
            int p;
            cin >> p;
            int pos = find_idx(1, 1, n, p);
            update(1, 1, n, pos, '-');
        }
        else
        {
            int l, r;
            cin >> l >> r;
            int posl = find_idx(1, 1, n, l);
            int posr = find_idx(1, 1, n, r);
            cout << get(1, 1, n, posl, posr).val << "\n";
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int test = 1;
    // cin >> test;
    while (test--)
        solve();
    return 0;
}
