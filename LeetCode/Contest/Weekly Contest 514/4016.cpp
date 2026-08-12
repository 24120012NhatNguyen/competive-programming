#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool check(vector<vector<int>> &dp, int &k, int &n, int &m)
    {
        int r1 = 1e9, r2 = 0, c1 = 1e9, c2 = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (dp[i][j] >= k)
                {
                    r1 = min(r1, i);
                    r2 = max(r2, i);
                    c1 = min(c1, j);
                    c2 = max(c2, j);
                }
            }
        }
        return (c2 - c1 >= k || r2 - r1 >= k);
    }
    int maxArea(vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (mat[i - 1][j - 1] == 1)
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
            }
        }
        int ans = 0;
        int l = 0, r = 251;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (check(dp, mid, n, m))
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans * ans;
    }
};

/*
check k co valid ko ? dp
check 2 vet cat doc va ngang ; l , r ; bot , up ?
*/
