#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minAbsoluteDifference(vector<int> &nums)
    {
        int lst = -1, lst2 = -1;
        int mii = 1e9;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 1)
            {
                if (lst2 != -1)
                {
                    mii = min(mii, i - lst2);
                }
                lst = i;
            }
            else if (nums[i] == 2)
            {
                if (lst != -1)
                {
                    mii = min(mii, i - lst);
                }
                lst2 = i;
            }
        }
        return mii == 1e9 ? -1 : mii;
    }
};