#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minRemovals(vector<int> &nums, int target)
    {
        int val = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            val = (val ^ nums[i]);
        }
        int s = (val ^ target);
        if (s == 0)
            return 0;
        int ma = (1 << 14);
        int inf = 1e9;
        vector<int> dp(ma, inf); // số lượng phần tử ít nhất mà xor ra ma
        queue<int> q;
        q.push(0);
        dp[0] = 0;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int x : nums)
            {
                int nxt = (cur ^ x);
                if (dp[nxt] > dp[cur] + 1)
                {
                    dp[nxt] = dp[cur] + 1;
                    if (nxt == s)
                        return dp[nxt];
                    q.push(nxt);
                }
            }
        }
        return -1;
        /*
        dp[a[i]]
        */
        // a[1] xor .. a[n] = val  ->  a[i1] xor.. a[ik] xor target = val->
        // cần tìm tập con ít phần tử nhất sao cho xor bằng val xor target
    }
};
