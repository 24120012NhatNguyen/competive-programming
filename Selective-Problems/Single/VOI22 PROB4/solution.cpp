#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
const int MX = 1e6 + 10;
int n;
struct line
{
    int r, l, w;
};
struct SegTree
{
    int n;
    vector<ll> lz;
    vector<ll> st;
    SegTree(int _n) : n(_n)
    {
        lz.assign(4 * n + 10, 0ll);
        st.assign(4 * n + 10, 0ll);
    }
    void down(int id, int l, int r)
    {
        if (lz[id] == 0 || l > r)
            return;
        ll A = lz[id];
        lz[id] = 0;

        st[2 * id] = st[2 * id] + A;
        lz[2 * id] = lz[2 * id] + A;

        st[2 * id + 1] = st[2 * id + 1] + A;
        lz[2 * id + 1] = lz[2 * id + 1] + A;
    }
    void update(int id, int l, int r, int u, int v, int val)
    {
        if (u > r or l > v)
            return;
        if (u <= l and r <= v)
        {
            st[id] += 1ll * val;
            lz[id] += 1ll * val;
            return;
        }
        down(id, l, r);
        int mid = (l + r) / 2;
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);
        st[id] = max(st[2 * id], st[2 * id + 1]);
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<line> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].l >> v[i].r >> v[i].w;
    }
    sort(v.begin(), v.end(), [&](line &a, line &b)
         {
        if (a.r != b.r) return a.r < b.r;
        return a.l < b.l; });
    int j = 0;
    SegTree st(MX);
    ll ans = 0LL;
    for (int i = 0; i < MX; i++)
    {
        while (j < n and i == v[j].r)
        {
            st.update(1, 0, MX - 1, 0, v[j].l, v[j].w);
            j++;
        }
        ans = max(ans, st.st[1]);
    }
    cout << ans << "\n";
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    if (fopen("SSEQ.INP", "r"))
    {
        freopen("SSEQ.INP", "r", stdin);
        freopen("SSEQ.OUT", "w", stdout);
    }
    int test = 1;
    //  cin >> test;
    while (test--)
        solve();
    return 0;
}
