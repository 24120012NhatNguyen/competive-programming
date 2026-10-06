#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
    int n = nums.size();
    map<int, vector<int>> id;
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
      idx.push_back(id[nums[i]].size());
      id[nums[i]].push_back(i);
    }
    vector<int> result;
    for (int q : queries) {
      vector<int> &qu = id[nums[q]];
      int sz = qu.size();
      if (sz == 1) {
        result.push_back(-1);
      } else {
        int j = idx[q];
        int prev = qu[(j - 1 + sz) % sz];
        int nextt = qu[(j + 1) % sz];
        result.push_back(min((nextt + n - qu[j]) % n, (qu[j] - prev + n) % n));
      }
    }
    return result;
  }
};
