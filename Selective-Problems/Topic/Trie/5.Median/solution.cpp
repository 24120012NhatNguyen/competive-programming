// https://oj.vnoi.info/problem/median
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1337377;

void balance(multiset<int> &a, multiset<int> &b)
{
    while (a.size() < b.size())
    {
        int tmp = (*b.begin());
        b.erase(b.begin());
        a.insert(tmp);
    }
    while (a.size() > b.size() + 1)
    {
        auto it = prev(a.end());
        b.insert(*it);
        a.erase(it);
    }
}
void add_val(int val, multiset<int> &a, multiset<int> &b)
{
    if (a.empty() || val <= *a.rbegin())
    {
        a.insert(val);
    }
    else
    {
        b.insert(val);
    }
    balance(a, b);
}
void eraseval(int val, multiset<int> &a, multiset<int> &b)
{
    auto it = a.find(val);
    if (it != a.end())
    {
        a.erase(it);
    }
    else
    {
        b.erase(b.find(val));
    }
    balance(a, b);
}
void solve(int pp)
{
    int seed, add, mul, n, k;
    cin >> seed >> mul >> add >> n >> k;
    int a[n + 1];
    a[1] = seed;
    for (int i = 2; i <= n; i++)
    {
        a[i] = (1LL * a[i - 1] * mul + add) % 65536;
    }
    multiset<int> ms1, ms2;
    int l = 1;
    long long ans = 0LL;
    for (int r = 1; r <= n; r++)
    {
        add_val(a[r], ms1, ms2);
        while (r - l + 1 > k)
        {
            eraseval(a[l++], ms1, ms2);
        }
        balance(ms1, ms2);
        if (r - l + 1 == k)
            ans += 1LL * (*prev(ms1.end()));
    }
    cout << "Case #" << pp << ": " << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    cin >> t;
    int p = t;
    while (t--)
        solve(p - t);

    return 0;
}