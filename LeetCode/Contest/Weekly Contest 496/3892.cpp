#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minOperations(vector<int> &a, int k)
    {
        int n = a.size();
        if (k > n / 2)
            return -1;
        vector<vector<int>> dp(n, vector<int>(k + 1, (int)1e9));
        // a[0] kh lam peak;
        dp[0][0] = 0;
        for (int i = 1; i < n; i++)
        {
            int costi = max(0, max(a[i - 1], ((i < n - 1) ? a[i + 1] : a[0])) - a[i] + 1);
            for (int j = 0; j <= min(i, k); j++)
            {
                dp[i][j] = min(dp[i - 1][j], ((i >= 2 and j >= 1) ? dp[i - 2][j - 1] : 0) + costi);
            }
        }
        int ans = dp[n - 1][k];
        for (auto vec : dp)
        {
            ans = min(ans, vec[k]);
        }
        if (k == 0)
            return ans;
        // a[0] lam peak
        dp.clear();
        dp.resize(n, vector<int>(k + 1, (int)1e9));
        dp[0][1] = max(0, max(a[1], a[n - 1]) - a[0] + 1);
        for (int i = 1; i < n - 1; i++)
        {
            int costi = max(0, max(a[i - 1], a[i + 1]) - a[i] + 1);
            for (int j = 1; j <= min(i, k); j++)
            {
                dp[i][j] = min(dp[i - 1][j], ((i >= 2 and j >= 1) ? dp[i - 2][j - 1] : 0) + costi);
            }
        }
        for (auto vec : dp)
        {
            ans = min(ans, vec[k]);
        }
        return (ans == (int)1e9 ? -1 : ans);
    }
};