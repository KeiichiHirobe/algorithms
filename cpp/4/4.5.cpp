#include <iostream>
#include <cmath>
using namespace std;

// 3,5,7
bool threeOk(int bitmask)
{
    return bitmask & 0x04;
}
bool fiveOk(int bitmask)
{
    return bitmask & 0x02;
}
bool sevenOk(int bitmask)
{
    return bitmask & 0x01;
}
int valiation(int bitmask)
{
    int cnt = 0;
    if (threeOk(bitmask))
    {
        ++cnt;
    }
    if (fiveOk(bitmask))
    {
        ++cnt;
    }
    if (sevenOk(bitmask))
    {
        ++cnt;
    }
    return cnt;
}

int countFor(int bitmask, int limit, int digit)
{
    // 雑
    if (limit < 3)
    {
        return 0;
    }
    if (digit == 1)
    {
        int num = valiation(bitmask);
        if (num <= 1)
        {
            return 0;
        }
        else if (num == 2)
        {
            if (!threeOk(bitmask))
            {
                if (limit >= 3)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (!fiveOk(bitmask))
            {
                if (limit >= 5)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (!sevenOk(bitmask))
            {
                if (limit >= 7)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            if (limit >= 7)
            {
                return 3;
            }
            else if (limit >= 5)
            {
                return 2;
            }
            else if (limit >= 3)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    // 3
    int cnt1 = countFor(bitmask | 0x04, limit - 3 * pow(10, digit - 1), digit - 1);
    int cnt2 = countFor(bitmask | 0x02, limit - 5 * pow(10, digit - 1), digit - 1);
    int cnt3 = countFor(bitmask | 0x01, limit - 7 * pow(10, digit - 1), digit - 1);
    return cnt1 + cnt2 + cnt3;
}

int main()
{
    int N;
    int digit = 0;
    cin >> N;

    for (int t = N; t != 0; t = t / 10)
    {
        ++digit;
    }
    int cnt = 0;
    for (int t = 3; t <= digit; ++t)
    {
        cnt += countFor(0, N, t);
    }

    cout << cnt << endl;
}
