#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int largestInteger(int n, int s)
    {
        if (s > 9 * n)
            return -1;
        int ans = 0;
        while (s > 0 or n > 0)
        {
            ans = ans * 10 + min(s, 9);
            s -= min(s, 9);
            n--;
        }
        return ans;
    }
};
