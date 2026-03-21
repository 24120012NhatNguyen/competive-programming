#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve()
{
    int n, c, k;
    cin >> n >> c >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int current = c;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > current)
        {
            cout << current << "\n";
            return;
        }
        int increase = min(k, current - a[i]);
        current += (a[i] + increase);
        k -= increase;
    }
    cout << current << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}