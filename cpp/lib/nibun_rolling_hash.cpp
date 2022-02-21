#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// 2^60
const ll INF = 1LL << 60;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
// clang-format on

// https://atcoder.jp/contests/abc141/tasks/abc141_e
// 非空文字列であって、S の連続する部分文字列として重ならずに 2 回以上現れるもののうち、最長のものの長さを出力せよ。そのような非空文字列が存在しないときは、0 を出力せよ
typedef unsigned long long ull;
#define B1 100000007
#define B2 1000000007

// hash計算にはmodを利用してないが、実質的に 2^64 でmodを取っているのと同値になっている
// hash衝突が起きると誤るが競プロの世界ではcheckしてはいけないらしい
bool rolling_hash(string const &S, int t_start, int m)
{
    int s_start = t_start + m;

    // B^mを用意する
    ull pow_B_m_1 = 1, pow_B_m_2 = 1;
    for (int k = 0; k < m; k++)
    {
        pow_B_m_1 *= B1, pow_B_m_2 *= B2;
    }

    // sとtの先頭m文字のハッシュ値sh,thを計算
    ull sh1 = 0, sh2 = 0, th1 = 0, th2 = 0;
    for (int k = 0; k < m; k++)
    {
        th1 = th1 * B1 + S[t_start + k], th2 = th2 * B2 + S[t_start + k];
        sh1 = sh1 * B1 + S[s_start + k], sh2 = sh2 * B2 + S[s_start + k];
    }

    // sをずらしてハッシュ値を更新
    for (int k = 0; s_start + k < S.length(); k++)
    {
        if (sh1 == th1 && sh2 == th2)
            return true;
        if (k + s_start < S.length())
        {
            sh1 = sh1 * B1 + S[s_start + m + k] - S[s_start + k] * pow_B_m_1;
            sh2 = sh2 * B2 + S[s_start + m + k] - S[s_start + k] * pow_B_m_2;
        }
    }
    return false;
}

int main()
{
    int n;
    string S;
    cin >> n >> S;

    // 2部探索では、ある点を境に左はOK、右はNGとなる単調性を利用している。
    // OKとなる最も右の場所が知りたい
    int ng = n + 1, ok = 0, mid;
    // この実装では要素がng or okの2択であることを前提としている
    // 一般的なlower_boundの実装はずっと難しい
    // ref: https://en.cppreference.com/w/cpp/algorithm/lower_bound
    while (ng - ok > 1)
    {
        mid = (ng + ok) / 2;
        bool matched = false;
        // Sのi文字目をtの先頭として,t = S[i:i+mid], s = S[i+mid:]
        for (int i = 0; i < n; i++)
        {
            if (i + mid * 2 > n)
                break;
            if (rolling_hash(S, i, mid))
            {
                matched = true;
                break;
            }
        }
        if (matched)
            ok = mid;
        else
            ng = mid;
    }
    cout << ok << endl;
}

// ref: https://en.cppreference.com/w/cpp/algorithm/lower_bound
int my_lower_bound(const vector<int> &v, const int &value)
{
    int a = 0;
    int count = v.size();
    int step;
    while (count > 0)
    {
        step = count / 2;
        int mid = a + step;
        if (v[mid] < value)
        {
            a = mid + 1;
            count = count - step - 1;
        }
        else
        {
            count = step;
        }
    }
    return a;
}
