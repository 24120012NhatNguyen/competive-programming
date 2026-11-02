#include <bits/stdc++.h>
#define int long long
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...)
#endif
void solve() {
  int n;
  string s;
  cin >> n >> s;
  s = " " + s;
  if (s[1] == '0') {
    cout << "-1\n";
    return;
  }
  for (int i = 2; i <= n; i++) {
    if (s[i] == s[i - 1] && s[i] == '0') {
      cout << "-1\n";
      return;
    }
  }

  auto check = [&](int mid) -> bool {
    vector<pair<int, int>> intervals = {{0, 0}};
    vector<pair<int, int>> next_intervals, merged;
    next_intervals.reserve(4);
    merged.reserve(4);

    for (int i = 1; i <= n; i++) {
      next_intervals.clear();
      merged.clear();
      for (auto p : intervals) {
        int L = p.first, R = p.second;
        if (L == R) {
          next_intervals.push_back({L - mid, L - 1});
          next_intervals.push_back({L + 1, L + mid});
        } else {
          next_intervals.push_back({L - mid, R + mid});
        }
      }
      sort(next_intervals.begin(), next_intervals.end());
      for (auto p : next_intervals) {
        if (p.first > p.second)
          continue;

        if (merged.empty()) {
          merged.push_back(p);
        } else {

          if (merged.back().second + 1 >= p.first) {
            merged.back().second = max(merged.back().second, p.second);
          } else {
            merged.push_back(p);
          }
        }
      }
      intervals.clear();
      for (auto p : merged) {
        int L = p.first, R = p.second;
        if (s[i] == '0') {
          L = max(L, 0LL);
          R = min(R, 0LL);
        } else if (s[i] == '+') {
          L = max(L, 1LL);
        } else if (s[i] == '-') {
          R = min(R, -1LL);
        }

        if (L <= R) {
          intervals.push_back({L, R});
        }
      }
      if (intervals.empty())
        return false;
    }
    return true;
  };

  int l = 1;
  int r = n;
  int ans = -1;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
