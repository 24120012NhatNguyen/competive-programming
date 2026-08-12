#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    struct SegTree
    {
        int n;
        int p;
        struct Node
        {
            bool havediv;
            int val;
            int sz;
            Node() : havediv(false), val(-1), sz(0) {};
            Node(int x) : havediv(true), val(x), sz(1) {};
        };
        vector<Node> st;
        vector<bool> div;
        SegTree(vector<int> &nums, int _n, int _p) : n(_n), p(_p)
        {
            st.resize(4 * _n + 5, Node());
            div.resize(_n);
            for (int i = 0; i < n; i++)
            {
                div[i] = 0;
                if (nums[i] % p == 0)
                {
                    div[i] = 1;
                }
            }
        }
        Node merge(Node &L, Node &R)
        {
            if (L.havediv == false)
                return R;
            if (R.havediv == false)
                return L;
            Node tmp;
            tmp.sz = L.sz + R.sz;
            tmp.havediv = true;
            tmp.val = __gcd(L.val, R.val);
            return tmp;
        }
        void build(vector<int> &nums, int id, int l, int r)
        {
            if (l == r)
            {
                st[id] = (div[l]) ? Node(nums[l]) : Node();
                return;
            }
            int mid = (l + r) / 2;
            build(nums, 2 * id, l, mid);
            build(nums, 2 * id + 1, mid + 1, r);
            st[id] = merge(st[2 * id], st[2 * id + 1]);
        }

        void update(int id, int l, int r, int idx, int val)
        {
            if (idx > r or idx < l)
                return;
            if (l == r)
            {
                if (val % p == 0)
                    div[idx] = 1;
                else
                    div[idx] = 0;
                st[id] = (div[idx]) ? Node(val) : Node();
                return;
            }
            int mid = (l + r) / 2;
            update(2 * id, l, mid, idx, val);
            update(2 * id + 1, mid + 1, r, idx, val);
            st[id] = merge(st[2 * id], st[2 * id + 1]);
        }
        Node get(int id, int l, int r, int u, int v)
        {
            if (u > r or v < l)
                return Node();
            if (u <= l and r <= v)
                return st[id];
            int mid = (l + r) / 2;
            Node L = get(2 * id, l, mid, u, v);
            Node R = get(2 * id + 1, mid + 1, r, u, v);
            return merge(L, R);
        }
        bool check()
        {
            if (st[1].val != p)
                return false;
            if (st[1].sz < n)
            {
                if (st[1].val == p)
                    return true;
                return false;
            }
            if (n >= 30)
                return true;
            else
            {
                for (int i = 0; i < n; i++)
                {
                    Node A = get(1, 0, n - 1, 0, i - 1);
                    Node B = get(1, 0, n - 1, i + 1, n - 1);
                    Node C = merge(A, B);
                    if (C.val == p)
                        return true;
                }
            }
            return false;
            // tat ca cac phan tu deu chia het cho n, gcd co giam ngat nen , nen khong ton tai cach xoa 1 trong n phan tu khong lam giam gcd -> false
        }
    };
    int countGoodSubseq(vector<int> &nums, int p, vector<vector<int>> &queries)
    {
        int n = nums.size();
        int q = queries.size();
        SegTree st(nums, n, p);
        st.build(nums, 1, 0, n - 1);
        int cnt = 0;
        for (int i = 0; i < q; i++)
        {
            int a = queries[i][0];
            int b = queries[i][1];
            st.update(1, 0, n - 1, a, b);
            if (st.check())
                cnt++;
        }
        return cnt;
    }
};
/*
tất cả các số trong đó đều chia hết cho p
-> đem chia cho p thì gcd đống đó là 1
2 4 6 8
*/
