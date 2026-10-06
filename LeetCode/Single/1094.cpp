#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  bool carPooling(vector<vector<int>> &trips, int capacity) {
    sort(trips.begin(), trips.end(), [](vector<int> &a, vector<int> &b) {
      if (a[1] != b[1])
        return a[1] < b[1];
      return a[2] < b[2];
    });
    int curcap = 0;
    int t = 0;
    auto cmp = [](const vector<int> &a, const vector<int> &b) {
      if (a[0] != b[0])
        return a[0] > b[0];
      return a[1] > b[1];
    };

    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    for (int from = 0; from <= 1000; from++) {
      while (!pq.empty() and pq.top()[0] == from) {
        curcap -= pq.top()[1];
        pq.pop();
      }
      while (t < trips.size() and trips[t][1] == from) {
        curcap += trips[t][0];
        pq.push({trips[t][2], trips[t][0]});
        t++;
      }
      if (curcap > capacity)
        return 0;
    }
    return 1;
  }

  // to -> -
};
