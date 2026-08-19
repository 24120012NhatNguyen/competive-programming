#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
// cach cai segment tree moi kham pha ra;
struct SegTree
{
    int n;
    vector<int> st, add, mul;
    SegTree(int _n)
    {
        n = _n;
        st.assign(4 * n + 5, 0);
        add.assign(4 * n + 5, 0);
        mul.assign(4 * n + 5, 1);
    }
    void build(int id, int l, int r, int a[])
    {
        if (l == r)
        {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * id, l, mid, a);
        build(2 * id + 1, mid + 1, r, a);
        st[id] = (st[2 * id] + st[2 * id + 1]) % MOD;
    }
    void down(int id, int l, int r)
    {
        if (mul[id] == 1 and add[id] == 0)
            return;
        int A = mul[id];
        int B = add[id];
        mul[id] = 1;
        add[id] = 0;

        int mid = (l + r) / 2;
        // ans = (val * mul_od + add_od ) * mul + add = val * mul
        st[2 * id] = ((st[2 * id] * A % MOD + B * (mid - l + 1)) % MOD) % MOD;
        mul[2 * id] = mul[2 * id] * A % MOD;
        add[2 * id] = (add[2 * id] * A + B) % MOD;

        st[2 * id + 1] = (st[2 * id + 1] * A + B * (r - mid) % MOD) % MOD;
        add[2 * id + 1] = (add[2 * id + 1] * A + B) % MOD;
        mul[2 * id + 1] = mul[2 * id + 1] * A % MOD;
    }
    void update(int id, int l, int r, int u, int v, int x, int y)
    {
        if (u > r || l > v)
            return;
        if (u <= l and r <= v)
        {
            st[id] = (st[id] * x + y * (r - l + 1)) % MOD;
            mul[id] = mul[id] * x % MOD;
            add[id] = (add[id] * x + y) % MOD;
            return;
        }
        down(id, l, r);
        int mid = (l + r) / 2;
        update(2 * id, l, mid, u, v, x, y);
        update(2 * id + 1, mid + 1, r, u, v, x, y);
        st[id] = (st[2 * id] + st[2 * id + 1]) % MOD;
    }
    void update(int l, int r, int t, int val)
    {
        if (t == 1)
        {
            update(1, 1, n, l, r, 1, val);
        }
        else if (t == 2)
        {
            update(1, 1, n, l, r, val, 0);
        }
        else
        {
            update(1, 1, n, l, r, 0, val);
        }
    }
    int get(int id, int l, int r, int u, int v)
    {
        if (u > r || l > v)
            return 0;
        if (u <= l and r <= v)
        {
            return st[id];
        }
        down(id, l, r);
        int mid = (l + r) / 2;
        int le = get(2 * id, l, mid, u, v);
        int ri = get(2 * id + 1, mid + 1, r, u, v);
        return (le + ri) % MOD;
    }
    int get(int l, int r)
    {
        return get(1, 1, n, l, r);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    int a[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    SegTree st(n);
    st.build(1, 1, n, a);
    while (m--)
    {
        int t;
        cin >> t;
        if (t <= 3)
        {
            int l, r, val;
            cin >> l >> r >> val;
            st.update(l, r, t, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.get(l, r) << "\n";
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
    //  cin >> test;
    while (test--)
        solve();
    return 0;
}
