#include <iostream>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

// https://qiita.com/drken/items/b97ff231e43bce50199a
// 返り値: gcd(a,b)
// ax+by=gcd(a,b) を満たす(x,y)が格納される
long long extGCD(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

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

// /usr/bin/clang++ --std c++17 /Users/keiichi/go/src/github.com/algorithms/cpp/lib/math.cpp -o ./out  -L/usr/local/lib -lgtest -lgtest_main
TEST(extendEuclid, wikipedia)
{
    long long x;
    long long y;
    long long gcd;
    gcd = extGCD(1071, 1029, x, y);
    EXPECT_EQ(gcd, 21);
    EXPECT_EQ(x, -24);
    EXPECT_EQ(y, 25);
    // a < bでも無問題
    gcd = extGCD(1029, 1071, x, y);
    EXPECT_EQ(gcd, 21);
    EXPECT_EQ(x, 25);
    EXPECT_EQ(y, -24);
}

TEST(primefactor, 2020)
{
    const auto &ret = prime_factorize(2020);
    vector<pair<long long, long long>> expected{{2, 2},
                                                {5, 1},
                                                {101, 1}};
    EXPECT_EQ(ret, expected);
}
