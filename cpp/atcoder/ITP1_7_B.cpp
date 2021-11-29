#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int count(int n, int x)
{
    int cnt = 0;
    // int max = (x + 2) / 3;
    int max = n;
    for (int i = 1; i <= max; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int r = x - i -j;
            if (r > j && r <= n)
            {
                ++cnt;
            }
        }
    }
    return cnt;
}
int main()
{
    int n;
    int x;

    while (true)
    {
        cin >> n;
        cin >> x;
        if (n == 0 && x == 0)
            break;
        cout << count(n, x) << endl;
    }
}