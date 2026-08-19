#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
const int MX = 1e6 + 10;

struct SegTree
{
    vector<vector<int>> st;
    vector<int> lz;
    int n;

    SegTree(int _n)
    {
        n = _n;
        st.resize(21, vector<int>(4 * n + 100, 0));
        lz.assign(4 * n + 100, 0);
    }
    void down(int id, int l, int r)
    {
        if (lz[id] == 0)
            return;

        int val = lz[id];
        lz[id] = 0;

        int mid = (l + r) / 2;

        for (int i = 0; i <= 20; i++)
        {
            if ((val >> i) & 1)
            {
                st[i][2 * id] = mid - l + 1 - st[i][2 * id];
                st[i][2 * id + 1] = r - mid - st[i][2 * id + 1];
            }
        }
        lz[2 * id] = (lz[2 * id] ^ val);
        lz[2 * id + 1] = (lz[2 * id + 1] ^ val);
    }
    void build(int id, int l, int r, vector<int> &a)
    {
        if (l > r)
            return;
        if (l == r)
        {
            for (int i = 0; i <= 20; i++)
            {
                if ((a[l] >> i) & 1)
                {
                    st[i][id] = 1;
                }
            }
            return;
        }
        int mid = (l + r) / 2;
        build(2 * id, l, mid, a);
        build(2 * id + 1, mid + 1, r, a);
        for (int i = 0; i <= 20; i++)
        {
            st[i][id] = st[i][2 * id] + st[i][2 * id + 1];
        }
        return;
    }
    void update(int id, int l, int r, int u, int v, int val)
    {
        if (l > v or r < u)
            return;
        if (u <= l and r <= v)
        {
            for (int i = 0; i <= 20; i++)
            {
                if ((val >> i) & 1)
                {
                    st[i][id] = (r - l + 1) - st[i][id];
                }
            }
            lz[id] = (lz[id] ^ val);
            return;
        }
        int mid = (l + r) / 2;
        down(id, l, r);
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);
        for (int i = 0; i <= 20; i++)
        {
            st[i][id] = st[i][2 * id] + st[i][2 * id + 1];
        }
        return;
    }
    int get(int id, int l, int r, int u, int v)
    {
        if (l > v or r < u)
            return 0;
        if (u <= l and r <= v)
        {
            int tmp = 0;
            for (int i = 0; i <= 20; i++)
            {
                tmp += st[i][id] * (1 << i);
            }
            return tmp;
        }
        down(id, l, r);
        int mid = (l + r) / 2;
        int x = get(2 * id, l, mid, u, v);
        int y = get(2 * id + 1, mid + 1, r, u, v);
        return x + y;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    SegTree st(n);
    st.build(1, 1, n, a);
    int m;
    cin >> m;
    while (m--)
    {
        int q;
        cin >> q;
        int l, r;
        cin >> l >> r;
        if (q == 1)
        {
            cout << st.get(1, 1, n, l, r) << "\n";
        }
        else
        {
            int x;
            cin >> x;
            st.update(1, 1, n, l, r, x);
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
