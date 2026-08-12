#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>> &series1, vector<vector<int>> &series2)
    {
        vector<vector<int>> ans;
        int p1 = 0, p2 = 0;
        int n = series1.size(), m = series2.size();

        while (p1 < n || p2 < m)
        {

            int t1 = (p1 < n) ? series1[p1][0] : INT_MAX;
            int t2 = (p2 < m) ? series2[p2][0] : INT_MAX;

            int v1 = (p1 < n) ? series1[p1][1] : 0;
            int v2 = (p2 < m) ? series2[p2][1] : 0;

            int current_t = min(t1, t2);

            ans.push_back({current_t, v1 + v2});

            if (t1 == current_t)
                p1++;
            if (t2 == current_t)
                p2++;
        }

        return ans;
    }
};