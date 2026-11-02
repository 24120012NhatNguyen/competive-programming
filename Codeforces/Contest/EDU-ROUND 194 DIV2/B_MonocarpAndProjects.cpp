#include <bits/stdc++.h>
#define int long long
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...)
#endif

void solve() {
  int x, y, k;
  cin >> x >> y >> k;
  // (y % x) + ((y + 1) % (x+1) + + .. + (y + k) % (x + k))
  // (y + i ) = (x + i) + ( y - x)
  // neu y < 2x -> y - x < x + i voi moi i
  k--;
  if (y < 2 * x) {
    cout << (k + 1) * (y - x) << "\n";
  } else {
    // y >= 2 * x
    int m = y - 2 * x;
    // m = 10 - 2  * 3 = 4;
    // y - x = x + i => y - 2x = i;
    int ans = 0;

    if (k > m) {
      for (int i = 0; i <= m; i++) {
        ans += (y + i) % (x + i);
      }
      ans += (k - m) * (y - x);
      cout << ans << "\n";

    } else {
      for (int i = 0; i <= k; i++) {
        //  cout << (y + i) << " " << (x + i) << "\n";
        ans += (y + i) % (x + i);
      }
      //   cout << m << " " << k << " " << ans << "\n";
      cout << ans << "\n";
    }
  }
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
