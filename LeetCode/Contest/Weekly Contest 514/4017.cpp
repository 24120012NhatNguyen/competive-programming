#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    struct SegTree
    {
        int n;
        vector<bool> isPeak;
        struct Node
        {
            bool havepeak;
            int fst_peak;
            int lst_peak;
            long long val;

            Node()
            {
                havepeak = false;
                fst_peak = -1;
                lst_peak = -1;
                val = 0LL;
            }

            Node(int idx)
            {
                havepeak = true;
                fst_peak = idx;
                lst_peak = idx;
                val = 0LL;
            }
        };
        vector<Node> st;
        long long seq(int x) { return 1LL * (x - 1) * (x - 2) / 2; }
        SegTree(vector<int> &nums, int _n) : n(_n)
        {
            isPeak.resize(_n);
            isPeak[0] = 0;
            isPeak[_n - 1] = 0;
            for (int i = 1; i < _n - 1; i++)
            {
                isPeak[i] = 0;
                if (nums[i] > nums[i - 1] and nums[i] > nums[i + 1])
                {
                    isPeak[i] = 1;
                }
            }
            st.resize(4 * _n + 5, Node());
        }
        Node merge(Node &L, Node &R)
        {
            if (L.havepeak == false)
                return R;
            if (R.havepeak == false)
                return L;
            Node tmp;
            tmp.havepeak = true;
            tmp.fst_peak = L.fst_peak;
            tmp.lst_peak = R.lst_peak;
            tmp.val = L.val + R.val + seq(R.fst_peak - L.lst_peak + 1);
            return tmp;
        }
        void build(int id, int l, int r)
        {
            if (l == r)
            {
                st[id] = (isPeak[l]) ? Node(l) : Node();
                return;
            }
            int mid = (l + r) / 2;
            build(2 * id, l, mid);
            build(2 * id + 1, mid + 1, r);
            st[id] = merge(st[2 * id], st[2 * id + 1]);
        }
        void BUILD() { build(1, 0, n - 1); }
        void update_ISPEAK(vector<int> &nums, int idx, int val)
        {
            nums[idx] = val;
            for (int i = max(idx - 1, 1); i <= min(idx + 1, n - 2); i++)
            {
                isPeak[i] = 0;
                if (nums[i] > nums[i - 1] and
                    nums[i] > nums[i + 1])
                {
                    isPeak[i] = 1;
                }
            }
        }
        void update(int id, int l, int r, int idx, bool peak)
        {
            if (idx < l or idx > r)
                return;
            if (l == r)
            {
                st[id] = (peak) ? Node(idx) : Node();
                return;
            }
            int mid = (l + r) / 2;
            update(2 * id, l, mid, idx, peak);
            update(2 * id + 1, mid + 1, r, idx, peak);
            st[id] = merge(st[2 * id], st[2 * id + 1]);
        }
        void update_query(vector<int> &nums, int idx, int val)
        {
            update_ISPEAK(nums, idx, val);
            update(1, 0, n - 1, idx, isPeak[idx]);
            if (idx - 1 >= 0)
                update(1, 0, n - 1, idx - 1, isPeak[idx - 1]);
            if (idx + 1 <= n - 1)
                update(1, 0, n - 1, idx + 1, isPeak[idx + 1]);
        }
        Node getNode(int id, int l, int r, int u, int v)
        {
            if (u > r or v < l)
                return Node();
            if (u <= l and r <= v)
                return st[id];
            int mid = (l + r) / 2;
            Node L = getNode(2 * id, l, mid, u, v);
            Node R = getNode(2 * id + 1, mid + 1, r, u, v);
            return merge(L, R);
        }
        long long getVal(int l, int r)
        {
            Node tmp = getNode(1, 0, n - 1, l, r);
            //   cout << tmp.havepeak <<  " " << tmp.fst_peak << " " << tmp.lst_peak << "\n";
            if (tmp.havepeak == false)
                return 0;
            return seq(r - l + 1) - (seq(tmp.fst_peak - l + 1) + tmp.val +
                                     seq(r - tmp.lst_peak + 1));
        }
        void ispeak()
        {
            for (int v : isPeak)
                cout << v << "\n";
        }
    };
    vector<long long> countOfPeaks(vector<int> &nums,
                                   vector<vector<int>> &queries)
    {
        int n = nums.size();
        int q = queries.size();
        SegTree st(nums, n);
        st.BUILD();
        vector<long long> ans;
        for (int i = 0; i < q; i++)
        {
            int u = queries[i][1];
            int v = queries[i][2];
            if (queries[i][0] == 1)
            {
                ans.push_back(st.getVal(u, v));
            }
            else
            {
                st.update_query(nums, u, v);
            }
        }
        return ans;
    }
};