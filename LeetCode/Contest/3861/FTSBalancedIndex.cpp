#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int smallestBalancedIndex(vector<int> &nums)
    {
        int n = nums.size();
        long long summ = 0;
        for (int i = 0; i < n; i++)
        {
            summ += 1LL * nums[i];
        }
        long long prod = 1;
        int ans = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            summ -= nums[i];
            if (prod == summ)
                ans = i;
            if (prod > 1e18 / nums[i])
                break;
            prod *= 1LL * nums[i];
        }
        return ans;
    }
};