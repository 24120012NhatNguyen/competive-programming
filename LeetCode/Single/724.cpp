#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int pivotIndex(vector<int> &nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    int l = 0;

    for (int i = 0; i < nums.size(); i++) {
      int r = total - l - nums[i];
      if (r == l) {
        return i;
      }
      l += nums[i];
    }

    return -1;
  }
};
