#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

vector<pair<long long, long long> > prime_factorize(long long N)
{
    vector<pair<long long, long long> > res;
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

int main()
{
    long long n;
    cin >> n;

    long long ret = 1;
    map<int, int> m;
    for (int i = 1; i <= n; i++)
    {
        const auto &pf = prime_factorize(i);
        for (auto p : pf)
        {
            m[p.first] += p.second;
        }
    }

    for (auto itr = m.begin(); itr != m.end(); ++itr)
    {
        ret *= (itr->second + 1);
        ret %= 1000000007;
    }
    cout << ret << endl;
}
