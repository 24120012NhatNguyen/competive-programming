#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int, int>;
int MX = 100005;
string s;
int q;
int pow10[100005];
int MOD = 998244353;
int signn(int x)
{
    if (x == 0)
        return 1;
    else if (x == 1)
        return -1;
    else
        return 0;
}
struct Node
{
    bool has_op = 0;

    long long val = 0;
    int len_val = 0;

    int fi = 0;
    int sign_fi = -1; // 0 = '+' , 1 = '-';
    int len_fi = 0;

    int val_mid = 0;

    int se = 0;
    int sign_se = -1;
    int len_se = 0;

} st[4 * 100005 + 100];
Node merge(const Node &left, const Node &right)
{
    Node fa;
    if (!left.has_op and !right.has_op)
    {
        fa.val = ((left.val * pow10[right.len_val]) % MOD + right.val) % MOD;
        fa.len_val = left.len_val + right.len_val;
        fa.has_op = 0;
        return fa;
    }
    else if (!left.has_op and right.has_op)
    {
        fa = right;
        fa.fi = (left.val % MOD * pow10[right.len_fi] % MOD + right.fi + MOD) % MOD;
        fa.len_fi = left.len_val + right.len_fi;
    }
    else if (left.has_op and !right.has_op)
    {
        fa = left;
        fa.se = (left.se % MOD * pow10[right.len_val] % MOD + right.val + MOD) % MOD;
        fa.len_se = left.len_se + right.len_val;
    }
    else
    {
        fa.has_op = 1;
        fa.fi = left.fi;
        fa.sign_fi = left.sign_fi;
        fa.len_fi = left.len_fi;

        fa.val_mid = left.val_mid + signn(left.sign_se) * ((left.se % MOD * pow10[right.len_fi] % MOD + right.fi % MOD + MOD) % MOD) + ((right.val_mid) % MOD + MOD);

        fa.se = right.se;
        fa.sign_se = right.sign_se;
        fa.len_se = right.len_se;
    }
    fa.has_op = 1;
    return fa;
}
void update(int id, int l, int r, int pos, char val)
{
    if (pos < l || pos > r)
        return;
    if (l == r)
    {
        if (val == '+' || val == '-')
        {
            Node tmp;
            tmp.has_op = 1;
            tmp.sign_fi = (val == '+') ? 0 : 1;
            tmp.sign_se = tmp.sign_fi;
            st[id] = tmp;
        }
        else
        {
            Node tmp;
            tmp.val = val - '0';
            tmp.has_op = 0;
            tmp.len_val = 1;
            st[id] = tmp;
        }
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, pos, val);
    update(2 * id + 1, mid + 1, r, pos, val);
    st[id] = merge(st[2 * id], st[2 * id + 1]);
}
Node get_val(int id, int l, int r, int u, int v)
{
    if (l > v or r < u)
        return Node();
    if (u <= l and r <= v)
        return st[id];
    int mid = (l + r) / 2;
    Node le = get_val(2 * id, l, mid, u, v);
    Node ri = get_val(2 * id + 1, mid + 1, r, u, v);
    return merge(le, ri);
}
int compute(Node A)
{
    if (A.has_op)
        return (((A.fi + A.val_mid + signn(A.sign_se) * A.se) % MOD) + MOD) % MOD;
    else
        return (A.val % MOD + MOD) % MOD;
}
void solve()
{
    pow10[0] = 1;
    for (int i = 1; i < MX; i++)
        pow10[i] = pow10[i - 1] * 10 % MOD;
    cin >> s;
    cin >> q;
    int n = s.length();
    s = " " + s;
    for (int i = 1; i <= n; i++)
    {
        update(1, 1, n, i, s[i]);
    }
    while (q--)
    {
        char query;
        cin >> query;
        if (query == '?')
        {
            int l, r;
            cin >> l >> r;
            cout << compute(get_val(1, 1, n, l, r)) << "\n";
        }
        else
        {
            int i;
            char c;
            cin >> i >> c;
            update(1, 1, n, i, c);
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
