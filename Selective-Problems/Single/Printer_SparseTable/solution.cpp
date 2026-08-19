#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int N = 1e6 + 10;
int n;
int MOD = 1e9 + 7;
int LG = 20;
vector<vector<int>> up(LG + 1, vector<int>(N, 0));
int pos[N];
int s[N];
int depth[N];
char kitu[N];
void solve()
{
    cin >> n;
    int sz = 0;
    while (n--)
    {
        char c;
        cin >> c;
        if (c == 'T')
        {
            char L;
            cin >> L;
            sz++;
            pos[sz] = sz;
            kitu[sz] = L;
            up[0][sz] = pos[sz - 1];
            depth[sz] = depth[pos[sz - 1]] + 1;
            for (int i = 1; i <= LG; i++)
                if (up[i - 1][sz] != 0)
                    up[i][sz] = up[i - 1][up[i - 1][sz]];
        }
        else if (c == 'U')
        {
            int k;
            cin >> k;
            sz++;
            pos[sz] = pos[sz - 1 - k];
        }
        else
        {
            int x;
            cin >> x;
            int len = depth[pos[sz]] - x - 1;
            int node = pos[sz];
            for (int i = LG; i >= 0; i--)
                if (len >= (1LL << i))
                {
                    node = up[i][node];
                    len -= (1LL << i);
                }
            cout << kitu[node] << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int test = 1;
    //  cin >> test;
    while (test--)
        solve();
    return 0;
}
