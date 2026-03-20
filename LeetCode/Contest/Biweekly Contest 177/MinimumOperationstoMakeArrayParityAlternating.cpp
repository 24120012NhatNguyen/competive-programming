#include <bits/stdc++.h>
using namespace std;
class Solution
{
    vector<int> solve(vector<int> &nums, bool even)
    {
        int op = 0;
        int maxi = INT_MIN;
        int mini = INT_MAX;
        for (int num : nums)
        {
            if ((num % 2 && even) || (num % 2 == 0 && !even))
            {
                op++;
                maxi = max(maxi, num - 1);
                mini = min(mini, num + 1);
            }
            else
            {
                maxi = max(num, maxi);
                mini = min(num, mini);
            }
            even = !even;
        }
        return {op, maxi - mini};
    }

public:
    vector<int> makeParityAlternating(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return {0, 0};
        unordered_set<int> st(nums.begin(), nums.end());
        if (st.size() == 1)
        {
            return {(int)n / 2, 1};
        }
        vector<int> res1 = solve(nums, 0);
        vector<int> res2 = solve(nums, 1);
        if (res1[0] == res2[0])
            return res1[1] < res2[1] ? res1 : res2;
        return res1[0] < res2[0] ? res1 : res2;
    }
};