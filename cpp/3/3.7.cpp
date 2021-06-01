#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    long long N;
    cin >> N;
    vector<int> a;
    int len = 0;
    long long rest = N;
    for (;;)
    {
        long long n = rest % 10;
        rest = rest / 10;
        ++len;
        a.push_back(n);
        if (rest == 0)
        {
            break;
        }
    }
    reverse(a.begin(), a.end());

    long long sum = 0;
    for (int bit = 0; bit < (1 << (len - 1)); ++bit)
    {
        long long t = 0;
        for (int i = 0; i < len; ++i)
        {
            int shift = len - i - 1;
            if ((bit & (1 << shift)) && i != 0)
            {
                sum += t;
                t = a[i];
            }
            else
            {
                t = t * 10 + a[i];
            }
        }
        sum += t;
    }
    cout << sum << endl;
}