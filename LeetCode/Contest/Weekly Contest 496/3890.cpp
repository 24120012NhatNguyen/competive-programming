#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    // vector<int> findGoodIntegers(int n) {
    //     int bound = cbrt(n);
    //     map<int, int> mp;
    //     vector <int> ans;
    //     for (int a = 1; a <= bound; a++){
    //         for (int b = a; b <= bound; b++){
    //             int tmp = a * a * a + b * b * b;
    //             if (tmp > n ) break;
    //             if (mp[tmp] == 2) continue;
    //             mp[tmp]++;
    //             if (mp[tmp] == 2){
    //                 ans.push_back(tmp);
    //             }
    //         }
    //     }
    //     sort(ans.begin(), ans.end());
    //     return ans;
    // }
    vector<int> findGoodIntegers(int n)
    {
        int bound = cbrt(n);
        vector<int> sums;
        sums.reserve((bound * bound) / 2 + 1);
        for (int a = 1; a <= bound; a++)
        {
            int a3 = a * a * a;
            for (int b = a; b <= bound; b++)
            {
                int tmp = a3 + b * b * b;
                if (tmp > n)
                    break;
                sums.push_back(tmp);
            }
        }
        sort(sums.begin(), sums.end());
        vector<int> ans;
        for (int i = 1; i < sums.size(); i++)
        {
            if (sums[i] == sums[i - 1])
            {
                if (ans.empty() || ans.back() != sums[i])
                {
                    ans.push_back(sums[i]);
                }
            }
        }
        return ans;
    }
};