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

// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a

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

// a^{-1} mod p (pは素数、aはpの倍数でなければいい)
// 基本はmodinvを使うこと！！ aがpの倍数の時は逆元は存在しない
// Fermat の小定理
// pを素数、aをpの倍数でない整数として
// a^{p−1} ≡ 1 (mod p)
// a * a^{p−2} ≡ 1 (mod p)
// -> aの逆元は mod p において一意に存在し、それは a^{p-2} である。
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

// a^{-1} mod p (aとpが互いに素であればいい)
// Euclidの互除法
// a*x-1 がpの倍数であることを意味するので
// a,pが互いに素として
// ax + py = 1　を満たす整数yが存在するときのxが逆元
long long modinv(long long a, long long mod)
{
    long long x;
    long long y;
    extGCD(a, mod, x, y);
    return normalize_mod(x, mod);
}

// modinvはlog(N)である。
// 1,2,..N それぞれの逆元を知りたい場合は普通にやると N*log(N)になってしまうが、以下で O(N)になる
// aの逆元がp%aの逆元で表現できることを利用している
// https://drken1215.hatenablog.com/entry/2018/06/08/210000

const int MAX = 510000;
const int MOD = 1000000007;

long long fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit()
{
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算
long long COM(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

// 中国の剰余定理
// https://qiita.com/drken/items/ae02240cd1f8edfc86fd
// b={2,3}
// m={3,5}
// ret={8,15}
// -> 「3で割って2余り、5で割って3余る数」は「15で割って8余る数」と同値
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<long long, long long> ChineseRem(const vector<long long> &b, const vector<long long> &m)
{
    long long r = 0, M = 1;
    for (int i = 0; i < (int)b.size(); ++i)
    {
        long long p, q;
        // m1とm2の最大公約数をdとして、m1 * p + m2 * q = d
        // 両辺dで割ることによって、p は　m1/d の逆元(mod m2/d) であることがわかる
        long long d = extGCD(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
        // dをmodとしてb1とb2は同値であることが必要十分条件
        // 特にm1とm2が互いに素であればd=1となり、上記条件は必ず成り立つ
        if ((b[i] - r) % d != 0)
            return make_pair(0, -1);

        // (m[i]/d) のmodをMをかける前に適用できる
        // 一般に m1 * a と m1 * (a mod  m2) はm1*m2を法として同値になるためと思われる
        long long tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        // Mはm1とm2の最小公倍数
        // 特にm1とm2が互いに素であればm1*m2
        M *= m[i] / d;
    }
    return make_pair(normalize_mod(r, M), M);
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
