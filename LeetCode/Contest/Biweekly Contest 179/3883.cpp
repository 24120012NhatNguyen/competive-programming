#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int MOD = 1e9 + 7;
    int countArrays(vector<int> &a)
    {
        int n = a.size();
        vector<vector<int>> dp(n, vector<int>(5001, 0));
        vector<int> get(5001, 0);
        for (int i = 0; i <= 5000; i++)
        {
            int tmp = i;
            while (tmp > 0)
            {
                get[i] += tmp % 10;
                tmp /= 10;
            }
        }
        vector<int> pref(5002, 0);
        for (int i = 0; i <= 5000; i++)
        {
            if (get[i] == a[0])
            {
                dp[0][i] = 1;
            }
            pref[i + 1] = pref[i] + dp[0][i];
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= 5000; j++)
            {
                if (get[j] != a[i])
                    continue;
                // test brute - force
                //  for (int x = 0; x <= j; x++)
                //      dp[i][j] += dp[i-1][x];
                dp[i][j] = (dp[i][j] + pref[j + 1]) % MOD;
            }
            pref[0] = 0;
            for (int j = 0; j <= 5000; j++)
            {
                pref[j + 1] = (pref[j] + dp[i][j]) % MOD;
                ;
            }
        }
        long long ans = 0;
        for (int i = 0; i <= 5000; i++)
        {
            ans = (ans + dp[n - 1][i]) % MOD;
        }
        return ans;
    }
};
/*
đếm s cáhc xây dựng mảng a không giảm sao cho a[i] <= 5000 và
tổng các chữ số của a[i] = digit sum [i]
a[i] <= 5000, sum_dig(a[i]) <= 4 + 9*3 = 31
dp[i][m] là số cách xây dựng mảng độ dài i, phần tử kết thúc là m
m = digit[i]
có bao nhiêu số nhỏ hơn 5000, lớn hơn VAL và có tổng các chữ số là m = y;
dp[i][m] = sigma(dp[i-1][ x < m] -> có thể tối ưu chiều nhưng chắc k cần htiết
*/