#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minOperations(string s)
    {
        bool ok = true;
        char mii = 'z', maa = 'a';
        for (int i = 0; i < s.length() - 1; i++)
        {
            if (s[i] > s[i + 1])
            {
                ok = false;
                break;
            }
        }
        if (ok)
            return 0;
        else
        {
            if (s.length() == 2)
                return -1;
        }
        for (char &x : s)
        {
            mii = min(mii, x);
            maa = max(maa, x);
        }
        if (s[0] == mii || s[s.length() - 1] == maa)
            return 1;
        for (int i = 1; i < s.length() - 1; i++)
        {
            if (s[i] == mii || s[i] == maa)
                return 2;
        }
        return 3;
    }
};
// khi sort [0..k] [k+1..n]
// để sort được đúng 1 lần, ta mong muốn tìm được vị trí k sao cho k+1...n đã được sort, và  max(0..k) < a[k+1]
// điều này cũng có nghĩa là do k + 1.. n đã được sort nên ta có thể tịnh tiến k đến n - 1 vẫn khôgn thay đổi -> max(0...k-1) k + 1 , điều này có nghĩa là nếu vị trí a[n] là max hoặc a[0] là min -> ta mất duy nhất 1 lần và đó case 1 lần duy nhất
// còn về 2 lần tức là không thỏa trên kia, tức là max không nằm biên phải , min khôgn nằm biên trái -> cần đúng 2 hoặc 3 lần
// nếu sau khi sort 1 lần n - 1 phần tử -> ta đưa đúng 1 trong 2 về đúng vị trí
// và khi đó theo case 1 cần đúng 1 lần nữa
// -> điều này xảy ra khi 2 thằng không đổi biên, vaf 2 thang la duy nhat