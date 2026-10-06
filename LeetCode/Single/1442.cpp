#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int countTriplets(vector<int> &arr) {
    int n = arr.size();
    vector<int> f(n + 1, 0);
    for (int i = 0; i < n; i++) {
      f[i + 1] = f[i] ^ arr[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int k = i + 1; k < n; k++) {
        if (f[k + 1] == f[i]) {
          ans += (k - i);
        }
      }
    }
    return ans;
  }
};
