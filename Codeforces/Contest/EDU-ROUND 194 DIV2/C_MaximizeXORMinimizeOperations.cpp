#include <bits/stdc++.h>
#define int long long
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...)
#endif

void solve() {
  int x, y;
  cin >> x >> y;
  // find k sao cho ( x - k ) xor (y + k) max.
  // a xor b = a + b - 2 * ( a & b)
  cout << x + y << " ";
  int s = x + y;
  int mask = 0;
  for (int i = 30; i >= 0; i--) {
    if ((s >> i) & 1) {
      if (mask + (1 << i) > x)
        continue;
      mask += (1 << i);
    }
  }
  cout << x - mask << "\n";
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
// a  & b = s ;
// a = x + k = > k = x - a;
