#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve()
{

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        int cnt1 = 0, cnt2 = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] > a[i])
                cnt1++;
            if (a[j] < a[i])
                cnt2++;
        }
        cout << max(cnt1, cnt2) << " ";
    }
    cout << "\n";
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