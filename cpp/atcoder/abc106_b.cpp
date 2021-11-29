#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

// 素因数分解
vector<pair<long long, long long>> prime_factorize(long long N)
{
    vector<pair<long long, long long>> res;
    for (long long a = 2; a * a <= N; ++a)
    {
        if (N % a != 0)
            continue;
        long long ex = 0;
        while (N % a == 0)
        {
            ++ex;
            N /= a;
        }
        res.push_back({a, ex});
    }

    // 素数
    if (N != 1)
        res.push_back({N, 1});
    return res;
}

int count(int n)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            continue;
        auto v = prime_factorize(i);
        int ret = 1;
        for (auto el : v)
        {
            ret *= (el.second + 1);
        }
        if (ret == 8)
            ++cnt;
    }
    return cnt;
}
int main()
{
    int n;

    cin >> n;
    cout << count(n) << endl;
}