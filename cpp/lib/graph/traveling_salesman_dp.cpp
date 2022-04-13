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
// const ll INF = 1LL << 60;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on

/*
bitDP
https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#11-bit-dp
https://algo-logic.info/bit-dp/

集合に対してDPを行うフレームワーク

dp[S] := 全体集合 {0,1,…,n−1} の部分集合Sについて、その中で順序を最適化したときの、Sの中での最小コスト

をDPにて

* dp[S] = min i∈S ( dp[S-{i}] + cost(S\{i},i) )
* 初期値：dp[0] = 0
* 答え: dp[(1<<n)-1]

が基本。

循環セールスマン問題(全ての頂点を一度だけ通って始点に戻った時の最小値)を解くことを考える。

cost(S\{i},i)を算出できない。S\{i}の順序が未知のためである。

dp[S][v] := 全体集合 {0,1,…,n−1} の部分集合Sについて、最後がvであるという制約の下で順序を最適化したときの、Sの中での最小コスト


けんちょんさんの記事は、始点に戻るコストを加味しない想定になっている。それは一般的ではないので実装は通常通り始点に戻るまでを考慮している。
始点に戻るまでを考慮する場合、閉路の長さは始点(=終点)に依存しないので、始点(=終点)を0としてしまって問題ない。

* dp[S][v] = min u∈(S-{v}) ( dp[S-{v}][u] + dist[u][v] )
  * 基本式では集合から除かれるiが変動したが、この式では固定でvとなることに注意。その代わりにuが変動
* 初期値：dp[1<<v][v] = dist[0][v]
  * 1 -> 2 -> 0 の場合、v=1であるが、d[0][1]を足し合わせないといけない
  * けんちょんさんの場合、右辺は0
* 答え: dp[(1<<n)-1][0]
  * 終点は0と仮定しているので
  * けんちょんさんの場合、min dp[(1<<n)-1][v]


とする
*/

// 1LL >>60 はだめ
const int INF = 100000000;
int N;
int dist[21][21];
int dp[(1 << 20) + 1][21];

int main()
{
    // 入力
    cin >> N;
    int M;
    cin >> M;

    rep(i, N)
    {
        rep(j, N)
        {
            dist[i][j] = INF;
        }
    }
    rep(i, M)
    {
        int from;
        int to;
        int w;
        cin >> from >> to >> w;
        dist[from][to] = w;
    }

    for (int bit = 0; bit < (1 << N); ++bit)
    {
        for (int v = 0; v < N; ++v)
        {
            dp[bit][v] = INF;
        }
    }

    for (int bit = 1; bit < (1 << N); bit = 2 * bit)
    {
        for (int v = 0; v < N; ++v)
        {
            dp[bit][v] = dist[0][v];
        }
    }

    // 2進数の数i,jが表す集合が𝑆(𝑖)⊂𝑆(𝑗) ならば 𝑖≤𝑗 となる性質から、配るDPのループを利用した更新順序でも問題なく更新ができる
    for (int bit = 0; bit < (1 << N); ++bit)
    {
        for (int v = 0; v < N; ++v)
        {
            for (int u = 0; u < N; ++u)
            {
                if (bit & (1 << u) && !(bit & 1 << v))
                {
                    chmin(dp[bit | 1 << v][v], dp[bit][u] + dist[u][v]);
                }
            }
        }
    }
    int res = INF;
    chmin(res, dp[(1 << N) - 1][0]);
    if (res >= INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << res << endl;
    }
}