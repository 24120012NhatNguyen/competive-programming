#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int countMagicalPairs(string s) {
    int cnt = 0;
    int n = s.length();
    // i -> j
    // j + 1 -> k;
    vector<vector<int>> f(n, vector<int>(n, 0));
    for (int l = 0; l < n; l++) {
      vector<bool> vis(26, 0);
      int dis = 0;
      for (int r = l; r < n; r++) {
        int charr = s[r] - 'a';
        if (vis[charr] == 0) {
          vis[charr] = 1;
          dis += 1;
        }
        f[l][r] = dis;
      }
    }
    for (int j = 0; j < s.length() - 1; j++) {
      map<int, int> mp;
      for (int k = j + 1; k < n; k++) {
        mp[f[j + 1][k]] += 1;
      }
      for (int i = 0; i <= j; i++) {
        cnt += mp[f[i][j]];
      }
    }
    return cnt;
  }
};
