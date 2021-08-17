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