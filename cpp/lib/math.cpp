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
// N=1の時のみ空を返却!!
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

// a^n mod を計算する
// 二分累乗法 O(log n)
// 3^45 = 3^{2^0} * 3^{2^2} * 3^{2^3} * 3^{2^5}
long long modpow(long long a, long long n, long long mod)
{
    long long ret = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        n = n >> 1;
    }
    return ret;
}

// a^{-1} mod
// 基本はmodinvを使うこと！！
// Fermat の小定理
// pを素数、aをpの倍数でない整数として
// a^{p−1} ≡ 1 (mod p)
// a * a^{p−2} ≡ 1 (mod p)
long long modinv_fermat(long long a, long long mod)
{
    return modpow(a, mod - 2, mod);
}

// 負の数にも対応した%
long long normalize_mod(long long val, long long m)
{
    long long res = val % m;
    if (res < 0)
        res += m;
    return res;
}

// a^{-1} mod
// Euclidの互除法
// a,pが互いに素として
// ax + py = 1　を満たす整数yが存在するときのxが逆元
long long modinv(long long a, long long mod)
{
    long long x;
    long long y;
    extGCD(a, mod, x, y);
    return normalize_mod(x, mod);
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
