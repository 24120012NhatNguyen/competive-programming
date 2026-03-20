#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> minDistinctFreqPair(vector<int> &nums)
    {
        vector<int> freq(101, 0);
        for (int &x : nums)
        {
            freq[x]++;
        }
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        vector<int> ans(2);
        ans[0] = -1;
        ans[1] = -1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
                if (freq[nums[i]] != freq[nums[j]])
                {
                    ans[0] = nums[i];
                    ans[1] = nums[j];
                    return ans;
                }
        }
        return ans;
    }
};
// 1 3 5 5 7 9
