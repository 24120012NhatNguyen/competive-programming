#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long minCost(int m, int n, vector<vector<int>> &penalty)
    {
        struct state
        {
            int row;
            int col;
            bool parity;
            long long cost;
            bool operator>(const state &other) const
            {
                return cost > other.cost;
            }
        };
        vector<vector<array<bool, 2>>> visited(
            m, vector<array<bool, 2>>(n, {false, false}));
        int a[5] = {0, 1, 0, -1, 0};
        int b[5] = {1, 0, -1, 0, 0};
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push({0, 0, 1, 1LL});

        while (!pq.empty())
        {
            auto [row, col, parity, cost] = pq.top();
            pq.pop();
            if (row == m - 1 and col == n - 1)
                return cost;
            if (visited[row][col][parity] == 1)
                continue;
            visited[row][col][parity] = 1;
            long long newcost = 0;
            for (int i = 0; i <= 4; i++)
            {
                int nr = row + a[i];
                int nc = col + b[i];
                if (nr >= m or nc >= n or nr < 0 or nc < 0)
                    continue;
                // TH1 : di chuyen
                newcost = 1LL * (1 + nr) * (1 + nc);
                if (parity == 1 && (i >= 2 and i <= 3))
                    newcost += 1LL * penalty[row][col];
                if (parity == 0 && (i < 2))
                    newcost += 1LL * penalty[row][col];
                // TH2 : dung yen;
                if (i == 4)
                    newcost = penalty[row][col];
                pq.push({nr, nc, !parity, cost + newcost});
            }
        }
        return 1;
    }
};
// 1 2
// 2 4

// 5 3
// 1 4

// 5 3
// 1 4