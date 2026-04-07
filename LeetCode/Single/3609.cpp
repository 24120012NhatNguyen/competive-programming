#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minMoves(int sx, int sy, int tx, int ty)
    {
        int steps = 0;
        if (sx == tx && sy == ty)
            return 0;
        while (tx > sx || ty > sy)
        {
            if (sx == tx && sy == ty)
                return steps;
            int mxx = max(tx, ty);
            int mii = min(tx, ty);
            if (mxx >= 2 * mii && mxx % 2 == 1)
                return -1;

            if (mxx >= 2 * mii)
            {
                if (tx == mxx)
                {
                    tx /= 2;
                }
                else
                {
                    ty /= 2;
                }
                steps++;
            }
            else
            {
                if (mxx == mii)
                {
                    if (sx > sy)
                    {
                        ty -= mii;
                    }
                    else
                    {
                        tx -= mii;
                    }
                }
                else if (tx == mxx)
                {
                    tx -= mii;
                }
                else
                {
                    ty -= mii;
                }
                steps++;
            }

            if (tx < sx || ty < sy)
                return -1;
        }
        return steps;
    }
};

/*
7,5 -> 2,5 ->
5, 4 -> (1, 4) ->  (1,2) ->
9 ,4 -> ,4
5, 5-> 5
*/