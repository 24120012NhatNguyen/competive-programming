#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long weightedSum(vector<int> &parent, vector<int> &nums)
    {
        long long sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += 1LL * nums[i];
        }
        vector<vector<int>> adj(nums.size(), vector<int>());
        for (int i = 1; i < nums.size(); i++)
        {
            adj[parent[i]].push_back(i);
        }
        int h = 1;
        long long sum_d = 0;
        queue<pair<int, int>> q;
        q.push({0, 1});
        while (!q.empty())
        {
            auto [u, d] = q.front();
            h = max(h, d);
            q.pop();
            for (int v : adj[u])
            {
                sum_d += 1LL * (d + 1) * nums[v];
                // cout << u << " " << v << " " << d + 1 << "\n";
                q.push({v, d + 1});
            }
        }
        //   cout << h << " " << sum << " " << sum_d;
        return 1LL * ((h + 1) * sum - sum_d - nums[0]);
    }
};

/*
(h+1) * (nums[i]) - d[i] * nums[i]
*/