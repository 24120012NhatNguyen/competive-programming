#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int peakValleyDifference(vector<int> &nums) {
    int ans1 = 0;
    int ans2 = 0;
    for (int i = 1; i < nums.size() - 1; i++) {
      if (nums[i] < min(nums[i - 1], nums[i + 1]))
        ans1 += nums[i];
      else if (nums[i] > max(nums[i - 1], nums[i + 1]))
        ans2 += nums[i];
    }
    return -ans1 + ans2;
  }
};
