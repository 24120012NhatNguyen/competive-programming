#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string mergeCharacters(string s, int k)
    {
        int cnt[26] = {0};
        string result;
        result.reserve(s.length());
        for (int i = 0; i < s.length(); i++)
        {
            int idx = s[i] - 'a';
            if (cnt[idx] > 0)
                continue; // đã xuất hiện trong cửa sổ -> cần merge
            cnt[idx]++;
            if (result.size() >= k)
            {
                cnt[result[result.size() - k] - 'a']--;
            }
            result.push_back(s[i]);
        }
        return result;
    }
};

/*
điều kiện bài toán <-> với mỗi cửa sổ độ dài k thì không tồn tại 2 thằng bằng nhau
giả sử xây dựng kết quả đúng đến i
khi đó ta quan tâm tần suất các phần tử  cửa sổ quanh i -> [i - k + 1, i  + 1],
*/