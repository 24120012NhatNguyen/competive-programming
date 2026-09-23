#include <bits/stdc++.h>
using namespace std; 
class Solution {
public:
    int maxValidSplits(vector<int>& a) {
        int n = a.size(); 
        int p1 = a[0]; 
        vector <int> idx; 
        for (int i = 1; i < n; i++){
            int x =  __gcd(p1,a[i]);
            if (x != p1) idx.push_back(i); 
            p1 = x; 
        }
        p1 = a[n-1];
        for (int i = n - 2; i >= 0; i--){
            int x = __gcd(p1,a[i]);
            if (x != p1) idx.push_back(i); 
            p1 = x; 
        }
        // 
        sort(idx.begin(), idx.end());
        idx.erase(unique(idx.begin(), idx.end()), idx.end());
        int ANS = 0;
        int m = idx.size();
        for (int j = -1; j < m; j++){
            vector <int> b;
            int ans = 0; 
            b.reserve(n); 
            if (j == -1){
                b = a; 
            }
            else{
               // cout << idx[j] << "\n"; 
                for (int i = 0; i < n; i++){
                    if (i == idx[j]) continue; 
                    b.push_back(a[i]);
                }
            }
            int N = b.size(); 
            vector <int> f(N), s(N);
            s[N-1] = b[N-1]; 
            f[0] = b[0];
            for (int i = 0; i < N - 1; i++) f[i+1] = __gcd(f[i], b[i+1]); 
            for (int i = N - 2; i >= 0; i--) s[i] = __gcd(s[i+1], b[i]); 

            for (int i = 0; i < N - 1; i++) {
                if (f[i] == s[i+1]) ans++; 
            } 
           // if (ANS  <= ans ) {cout << j << " "; if (j != -1) cout << idx[j] << "\n";}
            ANS = max(ANS,ans);
        }
        return ANS;
    } 
};
/*
    giá trị gcd giảm đúng log(K) lần 
    nếu xóa giá trị a[i] mà làm tăng được score 
    gcd(a[0..i] , gcd(a[i+1..n] 
    f[i] = f[i-1]  -> a[i] là bội f[i-1] 
    s[i] = s[i+1] -> a[i] là bôi s[i+1] 
    nếu xóa a[i] -> các split k < i là các split thỏa a[0..k] = a[k+1..n] -> a[k+1...i-1] a[i] , s[i+1] mà a[i] là bội s[i+1] nen k thay đổi 
    ....
    */