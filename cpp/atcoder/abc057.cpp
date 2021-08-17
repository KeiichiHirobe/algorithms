#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    long long max;

    for (long long i = 1; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            max = i;
        }
    }
    long long ret = log10(n / max) + 1;

    cout << ret << endl;
}