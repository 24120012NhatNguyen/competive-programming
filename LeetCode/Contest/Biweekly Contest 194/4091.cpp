// code TLE chua AC , 898/ 900 test pass
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  long long countMagicalPairs(string s) {
    long long cnt = 0;
    // get(l,r) -> so luong ki tu khac nhau tren doan l,r
    // -> tren doan l,r co xuat hien ki tu x khong?
    // ->
    int n = s.length();
    vector<vector<int>> f(26, vector<int>(n + 1, 0));
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < n; j++) {
        f[i][j + 1] = f[i][j] + (s[j] - 'a' == i);
      }
    }
    auto get = [&f](int l, int r) {
      int cntx = 0;
      for (int i = 0; i < 26; i++) {
        if (f[i][r + 1] - f[i][l] > 0)
          cntx += 1;
      }
      return cntx;
    };
    // goi cleft[v] la so idx i sao cho f[i,j] = v;
    // cright[v][j] la so idx k sao cho f[j+1,k] = v;

    for (int j = 0; j < s.length() - 1; j++) {
      vector<int> cleft(27, 0);
      vector<int> cright(27, 0);
      int curr_i = j;
      while (curr_i >= 0) {
        int v = get(curr_i, j);
        int le = 0, ri = curr_i;
        int Lbound = curr_i;
        while (le <= ri) {
          int mid = (le + ri) / 2;
          if (get(mid, j) == v) {
            Lbound = mid;
            ri = mid - 1;
          } else
            le = mid + 1;
        }
        cleft[v] = curr_i - Lbound + 1;
        curr_i = Lbound - 1;
      }

      int curr_k = j + 1;
      while (curr_k < n) {
        int v = get(j + 1, curr_k);
        int Rbound = curr_k;
        int le = curr_k, ri = n - 1;
        while (le <= ri) {
          int mid = (le + ri) / 2;
          if (get(j + 1, mid) == v) {
            Rbound = mid;
            le = mid + 1;
          } else
            ri = mid - 1;
        }
        cright[v] = Rbound - curr_k + 1;
        curr_k = Rbound + 1;
      }
      for (int v = 1; v <= 26; v++) {
        if (cleft[v] > 0 and cright[v] > 0) {
          cnt += 1LL * cleft[v] * cright[v];
        }
      }
    }
    return cnt;
  }
};
