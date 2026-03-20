#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int sumOfNumbers(int l, int r, int k)
    {
        const long long MOD = 1e9 + 7;
        auto power = [&](long long base, long long exp) -> long long
        {
            long long res = 1;
            base %= MOD;
            while (exp > 0)
            {
                if (exp & 1)
                    res = res * base % MOD;
                base = base * base % MOD;
                exp >>= 1;
            }
            return res;
        };
        auto inv = [&](long long x) -> long long
        {
            return power(x, MOD - 2);
        };
        long long cnt = r - l + 1;
        long long S = cnt % MOD * ((l + r) % MOD) % MOD * inv(2) % MOD;
        long long ways = power(cnt, k - 1);
        long long geo = (power(10, k) - 1 + MOD) % MOD * inv(9) % MOD;
        return S % MOD * ways % MOD * geo % MOD;
    }
};
/*
đề yêu cầu tính sigma ( sigma( 10^ i * d[i])) theo fubini
-> sigma(10^i) * sigma(d[i]) , với sigma(d[i]) chính bằng tổng của tất cả giá trị d[i] tại mỗi tổ hợp
-> do cố định d[i] -> có  ( r - l + 1) ^ k - 1 tổ hợp nhận nó tại vị trí i, giá trị d[i] trải daià từ l -> r -> cthuc
*/