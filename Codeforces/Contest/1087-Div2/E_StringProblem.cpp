#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> z_function(const string &s)
{
    int n = (int)s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int process_query(const string &T)
{
    int n = T.length();
    vector<int> Z = z_function(T);
    vector<int> DP(n + 1, 0);
    vector<int> head(n + 2, -1);
    vector<int> nxt;
    vector<int> val;
    nxt.reserve(n);
    val.reserve(n);

    vector<int> count_dp(n + 1, 0);
    int current_max = 0;
    int total_sum = 0;

    for (int i = 1; i <= n; i++)
    {
        int k = i - 1;
        if (k > 0 && Z[k] > 0)
        {
            count_dp[DP[k]]++;
            current_max = max(current_max, DP[k]);
            int exp_time = k + Z[k] + 1;
            if (exp_time <= n + 1)
            {
                val.push_back(k);
                nxt.push_back(head[exp_time]);
                head[exp_time] = val.size() - 1;
            }
        }
        for (int e = head[i]; e != -1; e = nxt[e])
        {
            int expired_k = val[e];
            count_dp[DP[expired_k]]--;
            while (current_max > 0 && count_dp[current_max] == 0)
            {
                current_max--;
            }
        }
        DP[i] = 1;
        if (current_max > 0)
        {
            DP[i] = max(DP[i], current_max + 1);
        }

        total_sum += DP[i];
    }

    return total_sum;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        string T = s.substr(l - 1, r - l + 1);
        cout << process_query(T) << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}