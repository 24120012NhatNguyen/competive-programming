#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minimumTotalDistance(vector<int> &robot,
                                   vector<vector<int>> &factory)
    {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        int n = robot.size();
        int m = factory.size();
        long long INF = 1e18;
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, INF));
        // khoảng cách nhỏ nhất để sửa i con robot đầu tiên sử dụng j nhà máy
        for (int j = 0; j <= m; j++)
            dp[0][j] = 0;

        for (int j = 1; j <= m; j++)
        {
            int pos = factory[j - 1][0];
            int limit = factory[j - 1][1];

            for (int i = 0; i <= n; i++)
            {
                dp[i][j] = dp[i][j - 1];

                long long dist = 0;
                for (int k = 1; k <= limit; k++)
                {
                    if (i - k < 0)
                        continue;
                    dist += abs(robot[i - k] - pos);
                    dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + dist);
                }
            }
        }

        return dp[n][m];
    }
};