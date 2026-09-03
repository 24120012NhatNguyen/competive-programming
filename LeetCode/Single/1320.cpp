#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int dist(int j, int cur)
    {
        return abs(j / 6 - cur / 6) + abs(j % 6 - cur % 6);
    }
    int minimumDistance(string word)
    {
        int n = word.length();
        const int INF = 1e9;
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(27, vector<int>(27, INF)));
        for (int i = 0; i <= 26; i++)
            for (int j = 0; j <= 26; j++)
                dp[0][i][j] = 0;
        for (int i = 1; i <= n; i++)
        {
            int cur = word[i - 1] - 'A';
            for (int j = 0; j <= 26; j++)
            {
                for (int k = 0; k <= 26; k++)
                {
                    dp[i][cur][k] = min(dp[i][cur][k], dp[i - 1][j][k] + dist(j, cur));
                    dp[i][j][cur] = min(dp[i][j][cur], dp[i - 1][j][k] + dist(k, cur));
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= 26; i++)
        {
            for (int j = 0; j <= 26; j++)
            {
                ans = min(ans, dp[n][i][j]);
            }
        }
        return ans;
    }
};