#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
const int MX = 1e6 + 10;
struct SegTree
{
    struct Node
    {
        bool has_black = 0; // = 0 neu nhu doan l,r chi toan mau trang
        int head = 0;
        int tail = 0;
        int val = 0;
        int lz = -1; // , =-1 neu nhu chua co thao tac gi ca, = 0 neu hien tai la trang, 1 la den
    };
    Node merge(Node &l, Node &r)
    {
        Node c;
        c.head = l.head;
        c.tail = r.tail;
        if (l.has_black == 0)
            c.head += r.head;
        if (r.has_black == 0)
            c.tail += l.tail;
        c.val = max({l.val, r.val, l.tail + r.head});
        c.has_black = l.has_black | r.has_black;
        return c;
    }
    int n;
    vector<Node> st;
    SegTree(int _n)
    {
        n = _n;
        st.resize(4 * n + 100);
    }
    void down(int id, int l, int r)
    {
        if (st[id].lz == -1)
            return;
        int temp = st[id].lz;
        st[id].lz = -1;

        int mid = (l + r) / 2;
        st[2 * id].lz = temp;
        st[2 * id + 1].lz = temp;
        if (temp == 0)
        {
            st[2 * id].has_black = 0;
            st[2 * id].head = mid - l + 1;
            st[2 * id].tail = mid - l + 1;
            st[2 * id].val = mid - l + 1;

            st[2 * id + 1].has_black = 0;
            st[2 * id + 1].head = r - mid;
            st[2 * id + 1].tail = r - mid;
            st[2 * id + 1].val = r - mid;
        }
        else
        {
            st[2 * id].has_black = 1;
            st[2 * id].head = 0;
            st[2 * id].tail = 0;
            st[2 * id].val = 0;

            st[2 * id + 1].has_black = 1;
            st[2 * id + 1].head = 0;
            st[2 * id + 1].tail = 0;
            st[2 * id + 1].val = 0;
        }
    }
    void update(int id, int l, int r, int u, int v, int val)
    {
        if (l > v or r < u)
            return;
        if (u <= l and r <= v)
        {
            if (val == 0)
            {
                st[id].has_black = 0;
                st[id].head = r - l + 1;
                st[id].tail = r - l + 1;
                st[id].val = r - l + 1;
            }
            else
            {
                st[id].has_black = 1;
                st[id].head = 0;
                st[id].tail = 0;
                st[id].val = 0;
            }
            st[id].lz = val;
            return;
        }
        int mid = (l + r) / 2;
        down(id, l, r);
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);
        st[id] = merge(st[2 * id], st[2 * id + 1]);
    }
};
void solve()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    SegTree st(n);
    st.update(1, 1, n, 1, n, 0);
    for (int i = 0; i < m; i++)
    {
        int q;
        cin >> q;
        if (q < 3)
        {
            int l, r;
            cin >> l >> r;
            if (q == 1)
            {
                st.update(1, 1, n, l, r, 0);
            }
            else
            {
                st.update(1, 1, n, l, r, 1);
            }
        }
        else
        {
            cout << st.st[1].val << "\n";
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
