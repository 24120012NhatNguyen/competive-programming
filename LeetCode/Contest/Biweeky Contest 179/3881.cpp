#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countVisiblePeople(int n, int pos, int k)
    {
        int MOD = 1e9 + 7;
        // (n-1)! / ( k! * (n - 1 - k)!)
        long long num = 1, den = 1;
        for (int i = 1; i <= n - 1; i++)
        {
            num = num * i % MOD;
        }
        for (int i = 1; i <= k; i++)
        {
            den = den * i % MOD;
        }
        for (int i = 1; i <= n - 1 - k; i++)
        {
            den = den * i % MOD;
        }
        long long base = den, inv = 1, mu = MOD - 2;
        while (mu > 0)
        {
            if (mu % 2 == 1)
                inv = inv * base % MOD;
            base = base * base % MOD;
            mu /= 2;
        }
        long long ans = (num * inv * 2) % MOD;
        return ans;
    }
};
/*
nếu i < pos thì được nhìn nếu họ chọn L
nếu i > pos thì họ được nhìn nếu họ chọn R
đếm số cách sao cho thằng pos nhìn được đúng k người
nhìn trái a thằng, phải b thằng tổng là a + b = k;
thực tế thì k thằng nào muốn pos nhìn thấy thì đều có thể cho mà ?
Chọn ra k thằng -> (n-1)Ck -> thằng pos muốn chọn gì cũng ok
(n-1)Ck * 2 mod

*/