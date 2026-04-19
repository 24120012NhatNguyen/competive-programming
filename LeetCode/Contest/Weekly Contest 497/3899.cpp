#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool valid(int x, int y, int z){
        double p = 1.0*(x + y + z)/2;
        return (p > x && p > y && p > z); 
    }
    vector<double> internalAngles(vector<int>& sides) {
        vector <double> ans;
        if (!valid(sides[0],sides[1],sides[2])) return ans; 
        for (int i = 0; i < 3; i++){
            double tmp = acos(1.0 * (sides[(i+1)%3] * sides[(i+1)%3] + 
                         sides[(i+2)%3] * sides[(i+2)%3] -
                         sides[i] * sides[i]) / (2 * sides[(i+1)%3] * sides[(i+2)%3]));
            tmp = tmp * 180.0 / M_PI;
            ans.push_back(tmp);
        }
        sort(ans.begin(),ans.end());
        return ans; 
    }
};