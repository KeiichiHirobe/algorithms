#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
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
using Graph = vector<vector<int>>;
// clang-format on

/*
https://algo-logic.info/range-dp/

長さnの数列が与えられ、以下の操作を好きなだけ行える。

数列の中から隣り合うペアを1つ選び、差が1以内になるなら除去する
最大でいくつ取り除くことができるか求めよ。

𝑑𝑝[𝑙][𝑟] := 区間 [l,r) について、取り除くことができる数の最大値
として、

更新は、2通りの場合を考えればよいです。

1. l,r-1番目が一緒に取り除かれる時: 区間[l+1,r-1)は全て取り除け、更にl,r-1番目の値の差が 1以下の時のみ生じる
2. 1以外の時： 区間[l,i)と区間[i,r)に分けて考える

実装はメモ化の方が楽でリンク先はメモ化で実装しているが、ここではDPで実装している。DPで実装するときは幅を徐々に増やしていけばいい。

int rec(int l = 0, int r = N) { // メモ化再帰
    if ((r - l) <= 1) return 0;
    if ((r - l) == 2) {
        if (abs(w[l] - w[l + 1]) <= 1) {  // 隣り合う2つの差が1以下
            return 2;
        } else {
            return 0;
        }
    }
    int &ret = dp[l][r]; // 更新の対象についての参照を宣言
    if (ret != -1) return ret;  // 既に計算済みならその値を使う
    // 1. 全部取り除けるとき
    if (abs(w[l] - w[r-1]) <= 1 && rec(l + 1, r - 1) == r - l - 2) chmax(ret, r - l);
    // 2. そうでない時
    for (int i = l + 1; i <= r - 1; i++) {
        chmax(ret, rec(l, i) + rec(i, r));
    }
    return ret;
}

*/

int n;
vector<int> v;
vector<vector<int>> dp;
int daruma()
{
    // 2~n
    rep(w, 2, n + 1)
    {
        // [l,l+w)
        rep(l, 0, n - w + 1)
        {
            rep(i, 1, w)
            {
                chmax(dp[l][l + w], dp[l][l + i] + dp[l + i][l + w]);
            }
            if (dp[l + 1][l + w - 1] == w - 2 && abs(v[l] - v[l + w - 1]) <= 1)
            {
                chmax(dp[l][l + w], w);
            }
        }
    }
    return dp[0][n];
}

int main()
{
    cout << fixed << setprecision(16);
    vector<int> ans;

    while (true)
    {
        cin >> n;
        if (n == 0)
            break;

        v.resize(n);
        dp.assign(n + 1, vector<int>(n + 1, 0));

        rep(i, 0, n)
        {
            cin >> v[i];
        }
        ans.push_back(daruma());
    }

    for (auto ret : ans)
    {
        cout << ret << endl;
    }
}
