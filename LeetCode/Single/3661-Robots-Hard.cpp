#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    struct ab
    {
        int pos, power;
    };
    static bool cmp(ab &a, ab &b)
    {
        if (a.pos != b.pos)
        {
            return a.pos < b.pos;
        }
        return a.power < b.power;
    }
    int maxWalls(vector<int> &robots, vector<int> &distance, vector<int> &walls)
    {

        int n = robots.size();
        const int inf = 1e9 + 1;
        vector<ab> a(n);
        for (int i = 0; i < n; i++)
        {
            a[i] = {robots[i], distance[i]};
        }
        sort(a.begin(), a.end(), cmp);
        sort(walls.begin(), walls.end());
        vector<int> posL(n, 0);
        vector<int> posR(n, 0);
        posL[0] = a[0].pos - a[0].power;
        for (int i = 1; i < n; i++)
        {
            posL[i] = max(a[i - 1].pos, a[i].pos - a[i].power);
        }
        posR[n - 1] = a[n - 1].pos + a[n - 1].power;
        for (int i = n - 2; i >= 0; i--)
        {
            posR[i] = min(a[i + 1].pos, a[i].pos + a[i].power);
        }
        vector<int> dp(2, 0);
        auto get_query = [&walls](const int &l, const int &r)
        {
            if (l > r)
                return 0;
            int ri = upper_bound(walls.begin(), walls.end(), r) - walls.begin();
            int le = lower_bound(walls.begin(), walls.end(), l) - walls.begin();
            return ri - le;
        };
        dp[0] = get_query(posL[0], a[0].pos);
        dp[1] = get_query(a[0].pos, posR[0]);
        for (int i = 1; i < n; i++)
        {
            vector<int> newdp(2, 0);
            newdp[0] = max(dp[0] + get_query(max(posL[i], a[i - 1].pos + 1), a[i].pos), dp[1] + get_query(max(posL[i], posR[i - 1] + 1), a[i].pos));
            newdp[1] = max(dp[0] + get_query(a[i].pos, posR[i]), dp[1] + get_query(max(a[i].pos, posR[i - 1] + 1), posR[i]));
            dp = newdp;
        }
        return max(dp[0], dp[1]);
    }
};
/*
posL[i] là vị trí xa nhất con robot index i bắn tới nếu nó bắn sang trái
gọi x là vị trí của con robot gần nhất ở bên trái thằng i
-> posL[i] = max(x, pos -  distance[i] ,0) ;
ta đương nhiên có thể tiền xử lý 2 mảng posL và posR
 với cái điều kiện viên đạn gặp con robot thì buộc dừng lại thì bài toán dễ hơn rất nhiều
 vì ta có nhận xét nếu con robot thứ i bắn sang phải thì vị trí xa nhất đso là có thể phủ của tất cả con robot trước đó và ngược lại với bên trái
 -> gọi dp[i][0,1] là số bức tường nhiều nhất xét đến con robot thứu i và nó bắn sang trái hoặc phải
 dp[i][0] = max(dp[i-1][0] + get_query(max(a[i-1].pos, posL[i]), a[i].pos)); với getquery (x,y) là số bức tường trong đoạn x, y ;
 -> toois uu chieu luon
-> cái query này bình thường thì có thể giải bằng prefix sum , nhưng mà do giới hạn 1e9 nên khôg thể
-> do walls tăng dần , nên chặt nhị phân tìm 2 biên nằm trong đoạn [x,y] cũng được
*/
