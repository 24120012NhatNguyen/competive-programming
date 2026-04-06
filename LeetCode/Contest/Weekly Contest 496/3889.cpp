#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int mirrorFrequency(string s)
    {
        vector<int> freq(36, 0);
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= '0' and s[i] <= '9')
            {
                freq[26 + (s[i] - '0')]++;
            }
            else
            {
                freq[s[i] - 'a']++;
            }
        }
        int ans = 0;
        for (int i = 0; i < 13; i++)
        {
            ans += abs(freq[i] - freq[25 - i]);
        }
        for (int i = 0; i <= 4; i++)
        {
            ans += abs(freq[i + 26] - freq[35 - i]);
        }
        return ans;
    }
};
