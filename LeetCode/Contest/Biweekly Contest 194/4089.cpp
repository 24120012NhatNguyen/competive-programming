#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  long long countSubarrays(vector<int> &nums, int minK, int maxK) {
    long long cnt = 0;
    int start = 0;
    nums.push_back((int)1e9);
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] < minK or nums[i] > maxK) {
        int len = i - start;
        cnt += 1LL * len * (len + 1) / 2;
        start = i + 1;
      }
    }
    return cnt;
  }
};
// 0 2
