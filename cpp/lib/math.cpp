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


// エラトステネスの篩を使って、1,2,,Nの素因数分解をNlogNにする
// 愚直にやるとN*N^{1/2}

// 約数列挙は計算量はnの約数の個数をσ(n)として、O(σ(n))となります。n≤10^9の範囲ではσ(n)≤1344(n=735134400で最大) であることが知られていますので、十分高速です。
// https://qiita.com/drken/items/3beb679e54266f20ab63#4-1-%E9%AB%98%E9%80%9F%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3

// エラトステネスの篩
struct Eratosthenes {
    // テーブル
    vector<bool> isprime;

    // 整数 i を割り切る最小の素数
    vector<int> minfactor;

    // コンストラクタで篩を回す
    Eratosthenes(int N) : isprime(N+1, true),
                          minfactor(N+1, -1) {
        // 1 は予めふるい落としておく
        isprime[1] = false;
        minfactor[1] = 1;

        // 篩
        for (int p = 2; p <= N; ++p) {
            // すでに合成数であるものはスキップする
            if (!isprime[p]) continue;

            // p についての情報更新
            minfactor[p] = p;

            // p 以外の p の倍数から素数ラベルを剥奪
            for (int q = p * 2; q <= N; q += p) {
                // q は合成数なのでふるい落とす
                isprime[q] = false;

                // q は p で割り切れる旨を更新
                if (minfactor[q] == -1) minfactor[q] = p;
            }
        }
    }

    // 高速素因数分解
    // pair (素因子, 指数) の vector を返す
    vector<pair<int,int>> factorize(int n) {
        vector<pair<int,int>> res;
        while (n > 1) {
            int p = minfactor[n];
            int exp = 0;

            // n で割り切れる限り割る
            while (minfactor[n] == p) {
                n /= p;
                ++exp;
            }
            res.emplace_back(p, exp);
        }
        return res;
    }  

    // 高速約数列挙
    vector<int> divisors(int n) {
        vector<int> res({1});

        // n を素因数分解 (メンバ関数使用)
        auto pf = factorize(n);

        // 約数列挙
        for (auto p : pf) {
            int s = (int)res.size();
            for (int i = 0; i < s; ++i) {
                int v = 1;
                for (int j = 0; j < p.second; ++j) {
                    v *= p.first;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }
};

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
