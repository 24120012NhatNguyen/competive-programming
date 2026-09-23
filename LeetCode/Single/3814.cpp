#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  int maxCapacity(vector<int> &costs, vector<int> &capacity, int budget) {
    int n = costs.size();
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++) {
      items[i] = {costs[i], capacity[i]};
    }
    sort(items.begin(), items.end());
    vector<int> pref(n);
    pref[0] = items[0].second;
    for (int i = 1; i < n; i++) {
      pref[i] = max(pref[i - 1], items[i].second);
    }
    int ans = 0;
    vector<int> just_costs(n);
    for (int i = 0; i < n; i++)
      just_costs[i] = items[i].first;
    for (int i = 0; i < n; i++) {
      if (items[i].first < budget)
        ans = max(ans, (int)items[i].second);
      int target = budget - items[i].first - 1;
      if (target < 0)
        continue;
      auto it = upper_bound(just_costs.begin(), just_costs.end(), target);
      int k = distance(just_costs.begin(), it) - 1;
      int valid_limit = min(i - 1, k);
      if (valid_limit >= 0)
        ans = max(ans, (int)items[i].second + pref[valid_limit]);
    }
    return ans;
  }
};
