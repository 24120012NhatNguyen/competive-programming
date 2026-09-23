#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int maxSatisfaction(vector<int> &satisfaction) {
    int n = satisfaction.size();
    sort(satisfaction.begin(), satisfaction.end());
    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
      pref[i + 1] = pref[i] + satisfaction[i];
    }
    auto get = [&pref](int l, int r) { return pref[r + 1] - pref[l]; };
    int ans = 0;
    int pos = lower_bound(satisfaction.begin(), satisfaction.end(), 0) -
              satisfaction.begin();
    for (int i = pos; i < n; i++) {
      ans += (i - pos + 1) * satisfaction[i];
    }
    if (pos == n) {
      return 0;
    } else if (pos == 0) {
      return ans;
    }
    int l = 0;
    int r = pos - 1;
    int res = -1;

    // cần tìm vị trí k sao cho f[k] =  k * VAL + a[pos - 1] * k + .. + a[pos -
    // k] * 1 đạt gtln (a sắp xếp tăng dần a[i] < 0 )
    //  f[k] - f[k-1] = VAL + a[pos - 1] + .. + a[pos - k] -> khi k tang thi
    //  f[k] - f[k-1] giam
    // f[1] = f[0] + 2
    // f[2] = f[1] + 1
    // f[3] = f[2] - 1
    // ...
    while (l <= r) {
      int mid = (l + r) / 2;
      int delta = get(pos, n - 1) + get(mid, pos - 1);
      if (delta >= 0) {
        res = mid;
        r = mid - 1;
      } else
        l = mid + 1;
    }
    ans = (res == -1) ? ans : ans + (pos - res) * get(pos, n - 1);
    for (int i = res; i <= pos - 1; i++) {
      ans += satisfaction[i] * (i - res + 1);
    }
    return ans;
  }
};
