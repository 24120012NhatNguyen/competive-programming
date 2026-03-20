#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int get(int l, int r, vector<int> &cnt)
    {
        return cnt[r + 1] - cnt[l];
    }
    long long recursion(const string &s, vector<int> &cnt, int encCost, int flatCost, int l, int r)
    {
        if (l > r)
            return 0;
        long long value = 0;
        int count = get(l, r, cnt);
        if (count == 0)
        {
            value = 1LL * flatCost;
        }
        else
        {
            value = 1LL * count * encCost * (r - l + 1);
        }
        if ((r - l + 1) % 2 == 0)
        {
            int mid = (l + r) / 2;
            long long tmp = 1LL * recursion(s, cnt, encCost, flatCost, l, mid) + recursion(s, cnt, encCost, flatCost, mid + 1, r);
            return min(value, tmp);
        }
        return value;
    }
    // [2... 9] -> [1...3] [4..6]
    long long minCost(string &s, int encCost, int flatCost)
    {
        int n = s.length();
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            cnt[i + 1] = cnt[i] + (s[i] == '1');
        }
        return recursion(s, cnt, encCost, flatCost, 0, n - 1);
    }
};