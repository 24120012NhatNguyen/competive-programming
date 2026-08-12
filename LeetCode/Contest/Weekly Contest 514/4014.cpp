#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    double minPrice(vector<int> &prices, vector<int> &discounts)
    {
        sort(prices.begin(), prices.end());
        sort(discounts.begin(), discounts.end());
        double ans = 0.0;
        int n = prices.size() - 1, m = discounts.size() - 1;
        for (int i = n; i >= 0; i--)
        {
            ans = ans + ((m >= 0) ? 1.0 * prices[i] * (100 - discounts[m--]) / 100 : prices[i]);
        }
        return ans;
    }
};