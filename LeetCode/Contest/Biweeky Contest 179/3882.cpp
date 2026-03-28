#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minCost(vector<vector<int>> &a)
    {
        int n = a.size();
        int m = a[0].size();
        int MAA = (1 << 10) + 1;
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(m, vector<bool>(MAA, 0)));
        dp[0][0][a[0][0]] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int k = 0; k < MAA; k++)
                {
                    if (dp[i][j][k])
                    {
                        if (i + 1 < n)
                        {
                            dp[i + 1][j][(k ^ a[i + 1][j])] = 1;
                        }
                        if (j + 1 < m)
                        {
                            dp[i][j + 1][k ^ a[i][j + 1]] = 1;
                        }
                    }
                }
            }
        }
        for (int ans = 0; ans < MAA; ans++)
        {
            if (dp[n - 1][m - 1][ans])
                return ans;
        }
        return -1;
    }
};
/*
a[i] <= 1023 = 2^10 - 1 -> phep xor cuối cùng cũng không quá 10 bit
dp[i][j][k] duong di tu i , j tao ra xor = k;
*/