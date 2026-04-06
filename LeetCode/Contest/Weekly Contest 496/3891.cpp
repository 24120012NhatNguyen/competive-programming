#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long minIncrease(vector<int> &a)
    {
        long long ans = 0;
        int n = a.size();
        for (int i = 1; i < n - 1; i += 2)
        {
            ans += max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0);
        }
        if (n % 2 == 1)
            return ans;
        auto get_cost = [&](int i)
        {
            int t = max(a[i - 1], a[i + 1]) + 1;
            return max(0, t - a[i]);
        };
        int k = (n - 1) / 2;
        vector<long long> pref(k + 1, 0);
        vector<long long> suff(k + 1, 0);
        // nếu đã trượt phải thì các peak sau cũng phải trượt theo -> nếu đang đi lẻ mà chuyển chẳn thì đi chẳn đến hết
        long long cur_pref = 0;
        for (int i = 1; i <= k; ++i)
        {
            cur_pref += 1LL * get_cost(2 * i - 1);
            pref[i] = cur_pref;
        }
        long long cur_suff = 0;
        for (int i = 1; i <= k; ++i)
        {
            cur_suff += 1LL * get_cost(n - 2 * i);
            suff[i] = cur_suff;
        }
        for (int i = 0; i <= k; ++i)
        {
            ans = min(ans, pref[i] + suff[k - i]);
        }

        return ans;
    }
};
/*
nếu a[i] làm peak thì a[i+1] và a[i-1] không làm peak được
peak đều có thể ổn , số peak maximum luôn cố định -> ( n - 1) / 2;
rõ hơn tí thì có thể thấy nếu n lẻ thì nó cố định luôn các peaks các vị trí như [0..n-1]
1 3 5 7 .. n - 2
-> nếu n chẳn thì cho phép peak bất kỳ truot phải đúng 1 em
// 0 1 2 3 4 5 6 7
// 1 3 6 ->  1 4 6 -> 1 3 5 -> 2 4 6
// for (int i = 1; i < n - 2 ; i++){
        //     long long tmp1 = 0, tmp2 = 0, tmp3 = 0;
        //     // chon thang i nay lech phai 4 -> 5 : (3,2)
        //     // prev
        //     for (int j = i - 1; j >= 1; j-=2){
        //         tmp1 += 1LL*max(max(a[j-1], a[j+1]) - a[j] + 1, 0);
        //     }
        //     for (int j = i - 2; j >= 1; j-=2){
        //         tmp2 += 1LL*max(max(a[j-1], a[j+1]) - a[j] + 1, 0);
        //     }
        //     for (int j = i + 1; j < n - 1; j += 2){
        //         tmp3 += 1LL*max(max(a[j-1], a[j+1]) - a[j] + 1, 0);
        //     }
        //     cout << i << " " << tmp1 << " "<< tmp2 << " " << tmp3 << "\n";
        //     ans = min(ans, min(tmp1,tmp2) + tmp3);
            // toi uu bang prefix sum
*/