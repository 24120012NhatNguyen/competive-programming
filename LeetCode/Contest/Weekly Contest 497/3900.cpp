#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestBalanced(string s)
    {
        int cnt0 = 0;
        int n = s.length();
        for (char &p : s)
        {
            if (p == '0')
                cnt0++;
        }
        int cnt1 = n - cnt0;
        if (cnt1 == cnt0)
            return n;
        if (cnt1 == 0 or cnt0 == 0)
            return 0;

        vector<int> pos1(200005, -2);
        vector<int> pos2(200005, -2);
        int offset = 100000;

        pos1[offset] = -1;

        int cur = 0;
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            cur += (s[i] == '0') ? -1 : 1;

            if (pos1[cur + offset] == -2)
            {
                pos1[cur + offset] = i;
            }
            else if (pos2[cur + offset] == -2)
            {
                pos2[cur + offset] = i;
            }

            if (pos1[cur + offset] != -2)
            {
                ans = max(ans, i - pos1[cur + offset]);
            }

            int cand1 = cur - 2, cand2 = cur + 2;
            if (pos1[cand1 + offset] != -2)
            {
                int len1 = i - pos1[cand1 + offset];
                int nums_zero = len1 / 2 - 1;

                if (nums_zero < cnt0)
                {
                    ans = max(ans, len1);
                }

                else if (pos2[cand1 + offset] != -2)
                {
                    int len2 = i - pos2[cand1 + offset];
                    ans = max(ans, len2);
                }
            }

            if (pos1[cand2 + offset] != -2)
            {
                int len1 = i - pos1[cand2 + offset];
                int nums_one = len1 / 2 - 1;
                if (nums_one < cnt1)
                {
                    ans = max(ans, len1);
                }
                else if (pos2[cand2 + offset] != -2)
                {
                    int len2 = i - pos2[cand2 + offset];
                    ans = max(ans, len2);
                }
            }
        }
        return ans;
    }
};