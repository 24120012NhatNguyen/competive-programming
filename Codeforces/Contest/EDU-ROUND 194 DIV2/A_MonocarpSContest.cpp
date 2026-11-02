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
  cin >> n;
  int a[n + 1];
  int b[2] = {0, 0};
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[a[i]]++;
  }
  if (b[0] < 2)
    cout << "-1\n";
  else if (a[1] == a[n] && a[1] == 0)
    cout << "0\n";
  else if (a[1] != a[n])
    cout << "1\n";
  else
    cout << "2\n";
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
