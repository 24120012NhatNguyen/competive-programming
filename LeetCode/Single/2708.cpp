#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  long long rec(vector<int> &nums, int cur, int limit, long long val, int pos) {
    if (cur == limit) {
      return val;
    }
    if (pos == nums.size())
      return (long long)-1e18;
    long long g = -1e18;
    long long A = rec(nums, cur + 1, limit, val * nums[pos], pos + 1);
    long long B = rec(nums, cur, limit, val, pos + 1);
    g = max({g, A, B});

    return g;
  }
  long long maxStrength(vector<int> &nums) {
    long long ans = 0;
    int n = nums.size();
    long long val = -1e18;
    for (int i = 1; i <= n; i++) {
      val = max(val, rec(nums, 0LL, i, 1LL, 0LL));
    }
    return val;
  }
};
