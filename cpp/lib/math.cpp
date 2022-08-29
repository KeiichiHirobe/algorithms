#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <random>
using namespace std;

// memo:
// 場合の数
// https://manabitimes.jp/math/1101
// 包除原理 
// https://manabitimes.jp/math/612
// https://manabitimes.jp/math/892
// https://atcoder.jp/contests/abc246/editorial/3703
// __builtin_popcountll
// にて、bitcountした方がlonglongにも対応


// end memo


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

// nCrの性質
// https://manabitimes.jp/math/588

const int MAX = 510000;
const int MOD = 1000000007;

long long fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
// k! (k!)^-1 の計算なので他の用途でも使える
// 以下条件
// * n > 10^7
// * MODは素数
// * MOD > n
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

// nPk
long long PER(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * finv[n - k] % MOD;
}

// nCk
long long COM(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}


// modを必要としないときにnCkがたくさん必要な場合
// パスカルの3角形
// 50C25 = 1e14ほどになることに注意
// https://algo-logic.info/pascal-triangle/

/*
    前処理: O(MAX_N*MAX_N)
    nCk(n,k): nCk の計算。O(1)
*/
const int MAX_N = 50;         // n の最大値
vector<vector<long long>> com;  // 前計算の結果を保存
// 動的計画法で前処理
void init() {
    com.assign(MAX_N, vector<long long>(MAX_N));
    com[0][0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        com[i][0] = 1;
        for (int j = 1; j < MAX_N; j++) {
            com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]);
        }
    }
}
// nCk を取得
long long nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return com[n][k];
}

// エラトステネスの篩を使って、1,2,,Nの素因数分解をNlogNにする
// 愚直にやるとN*N^{1/2}

// 約数列挙は計算量はnの約数の個数をσ(n)として、O(σ(n))となります。n≤10^9の範囲ではσ(n)≤1344(n=735134400で最大) であることが知られていますので、十分高速です。
// https://qiita.com/drken/items/3beb679e54266f20ab63#4-1-%E9%AB%98%E9%80%9F%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3

// エラトステネスの篩
struct Eratosthenes
{
    // テーブル
    vector<bool> isprime;

    // 整数 i を割り切る最小の素数
    vector<int> minfactor;

    // メビウス関数値
    // * μ(1)=1
    // * nがある素数pで2回以上割り切れるとき、μ(n)=0
    // * n=p1×p2×…pkと素因数分解できるとき、μ(n)=(−1)^K
    vector<int> mobius;

    // コンストラクタで篩を回す
    Eratosthenes(int N) : isprime(N + 1, true),
                          minfactor(N + 1, -1),
                          mobius(N + 1, 1)
    {
        // 1 は予めふるい落としておく
        isprime[1] = false;
        minfactor[1] = 1;

        // 篩
        for (int p = 2; p <= N; ++p)
        {
            // すでに合成数であるものはスキップする
            if (!isprime[p])
                continue;

            // p についての情報更新
            minfactor[p] = p;
            mobius[p] = -1;

            // p 以外の p の倍数から素数ラベルを剥奪
            for (int q = p * 2; q <= N; q += p)
            {
                // q は合成数なのでふるい落とす
                isprime[q] = false;

                // q は p で割り切れる旨を更新
                if (minfactor[q] == -1)
                    minfactor[q] = p;
                // update mobius
                if ((q / p) % p == 0)
                    mobius[q] = 0;
                else
                    mobius[q] = -mobius[q];
            }
        }
    }

    // 高速素因数分解
    // pair (素因子, 指数) の vector を返す
    vector<pair<int, int>> factorize(int n)
    {
        vector<pair<int, int>> res;
        while (n > 1)
        {
            int p = minfactor[n];
            int exp = 0;

            // n で割り切れる限り割る
            while (minfactor[n] == p)
            {
                n /= p;
                ++exp;
            }
            res.emplace_back(p, exp);
        }
        return res;
    }

    // 高速約数列挙
    // 計算量はnの約数の個数をσ(n)として、O(σ(n))となります。n≤10^9の範囲では、σ(n)≤1344(n=735134400で最大)
    vector<int> divisors(int n)
    {
        vector<int> res({1});

        // n を素因数分解 (メンバ関数使用)
        auto pf = factorize(n);

        // 約数列挙
        for (auto p : pf)
        {
            int s = (int)res.size();
            for (int i = 0; i < s; ++i)
            {
                int v = 1;
                for (int j = 0; j < p.second; ++j)
                {
                    v *= p.first;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }
};

// 高速ゼータ変換
// 正の整数nに対する関数f(n)があって、f(1),f(2),…,f(N)が与えられている状況を考えます。ただし n>Nのときf(n)=0であるものと仮定
// F(n)=∑n|i f(i)
// N=12の時
// F(1)=f(1)+f(2)+f(3)+ . . .+f(12)
// F(3)=f(3)+f(6)+f(9)+f(12)
// F(11)=f(11)

// 高速メビウス変換
// 高速ゼータ変換の逆変換
// N=12の時
// f(1)=F(1)−F(2)−F(3)−F(5)−F(7)−F(11)+F(6)+F(10)
// f(3)=F(3)−F(6)−F(9)
// f(11)=F(11)

// f(n)=∑n|i μ(i/n)F(i)
// となることが知られる

// 高速ゼータ変換
// 入力 f が in-place に更新されて、F になる
template <class T>
void fast_zeta(vector<T> &f)
{
    int N = f.size();

    // エラトステネスの篩を用いて素数を列挙
    vector<bool> isprime = Eratosthenes(N).isprime;

    // 各素数 p 軸に対して
    // 大きい座標 (k * p) から小さい座標 (k) へと足し込む
    for (int p = 2; p < N; ++p)
    {
        if (!isprime[p])
            continue;

        // 座標が大きい方を起点として累積和をとる
        // Nは0-indexのサイズなので最後の数字はN-1
        for (int k = (N - 1) / p; k >= 1; --k)
        {
            f[k] += f[k * p];
        }
    }
}

// 高速メビウス変換
// 入力 F が in-place に更新されて、f になる
template <class T>
void fast_mobius(vector<T> &F)
{
    int N = F.size();

    // エラトステネスの篩を用いて素数を列挙
    vector<bool> isprime = Eratosthenes(N).isprime;

    // 各素数 p 軸に対して
    // 小さい座標 (k) から大きい座標 (k * p) を引いていく
    for (int p = 2; p < N; ++p)
    {
        if (!isprime[p])
            continue;

        // 座標が小さい方を起点として差分をとる
        for (int k = 1; k * p < N; ++k)
        {
            F[k] -= F[k * p];
        }
    }
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

// 乱数でshuffle
random_device rnd; // 非決定的な乱数生成器
mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版

template <typename T>
void shuffleV(vector<T> &v)
{
    shuffle(v.begin(), v.end(), mt);
}

// 0~n-1までをshuffle
vector<int> shuffleSeq(int n)
{
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    shuffleV(v);
    return v;
}