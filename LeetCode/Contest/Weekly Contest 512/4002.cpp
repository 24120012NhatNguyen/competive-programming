#include <bits/stdc++.h>
using namespace std;
class Solution
{
    const int MOD = 1e9 + 7;

public:
    int inv(int x, int mod)
    {
        long long res = 1;
        long long base = x;
        while (mod > 0)
        {
            if (mod & 1)
            {
                res *= base;
                res %= MOD;
            }
            base *= base;
            base %= MOD;
            mod >>= 1;
        }
        return res;
    }
    int gt(int n)
    {
        int val = 1;
        for (int i = 2; i <= n; i++)
        {
            val = (1LL * val * i) % MOD;
        }
        return val;
    }
    int cmb(int n, int k)
    {
        return 1LL * gt(n) * inv(gt(k), MOD - 2) % MOD * inv(gt(n - k), MOD - 2) % MOD;
    }
    int countValidSequences(int n, int k)
    {
        if ((n + k) % 2)
        {
            return cmb(n - 1, k - 1);
        }
        else
        {
            return (cmb(n - 1, k - 1) - cmb((n + k) / 2 - 1, k - 1) + MOD) % MOD;
        }
    }
};
