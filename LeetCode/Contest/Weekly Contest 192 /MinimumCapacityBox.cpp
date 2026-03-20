#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minimumIndex(vector<int> &capacity, int itemSize)
    {
        int res = -1;
        int sz_res = 1e9;
        for (int i = 0; i < capacity.size(); i++)
        {
            if (capacity[i] >= itemSize and capacity[i] < sz_res)
            {
                sz_res = capacity[i];
                res = i;
            }
        }
        return res;
    }
};