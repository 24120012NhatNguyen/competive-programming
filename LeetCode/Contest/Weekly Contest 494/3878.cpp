#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long countGoodSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        int LOG = __lg(n) + 1;
        vector<vector<int>> sp(LOG + 1, vector<int>(n));
        sp[0] = nums;
        for (int k = 1; k <= LOG; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = sp[k - 1][i] | sp[k - 1][i + (1 << (k - 1))];
        auto qor = [&](int l, int r)
        {
            int k = __lg(r - l + 1);
            return sp[k][l] | sp[k][r - (1 << k) + 1];
        };
        vector<int> L(n), R(n);
        stack<int> st;
        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && nums[st.top()] < nums[i])
                st.pop();
            L[i] = st.empty() ? 0 : st.top() + 1;
            st.push(i);
        }
        while (!st.empty())
            st.pop();
        for (int i = n - 1; i >= 0; i--)
        {
            while (!st.empty() && nums[st.top()] <= nums[i])
                st.pop();
            R[i] = st.empty() ? n - 1 : st.top() - 1;
            st.push(i);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            int v = nums[i];
            int lo = i, hi = R[i], mr = i;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;
                if (qor(i, mid) == v)
                {
                    mr = mid;
                    lo = mid + 1;
                }
                else
                    hi = mid - 1;
            }
            lo = L[i];
            hi = i;
            int ml = i;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;
                if (qor(mid, i) == v)
                {
                    ml = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }

            ans += (long long)(i - ml + 1) * (mr - i + 1);
        }

        return ans;
    }
};
// a[l] | ... | a[r]  = a[k] -> a[k] = max(a[l]...,a[r]
// dùng stack cố định giá trị [l,r] mà a[k] làm max
// sau đó thì với mỗi [l,mid] -> kiếm l