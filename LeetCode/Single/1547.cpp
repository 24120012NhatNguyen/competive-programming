#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  vector<vector<int>> dp;
  int impl(vector<int> &cuts, int l, int r) {

    if (l > r)
      return 0;
    if (dp[l][r] != 0)
      return dp[l][r];
    int &res = dp[l][r];
    res = (int)1e9;
    for (int k = l; k <= r; k++) {
      res = min(res, impl(cuts, l, k) + impl(cuts, k, r) + (cuts[r] - cuts[l]));
    }
    if (res == int(1e9))
      return res = 0;
    return res;
  }
  int minCost(int n, vector<int> &cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    int m = cuts.size();
    dp.resize(m, vector<int>(m, 0));
    impl(cuts, 0, m - 1);
    return dp[0][m - 1];
  }
};
