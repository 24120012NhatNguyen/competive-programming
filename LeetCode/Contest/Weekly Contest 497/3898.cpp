#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> findDegrees(vector<vector<int>> &matrix)
    {
        vector<int> ans(matrix.size(), 0);
        for (int i = 0; i < matrix.size(); i++)
        {
            ans[i] = accumulate(matrix[i].begin(), matrix[i].end(), 0);
        }
        return ans;
    }
};