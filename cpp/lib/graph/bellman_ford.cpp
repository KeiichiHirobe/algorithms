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

// 辺を表す型，ここでは重みを表す型を long long 型とする
struct Edge
{
    int to;      // 隣接頂点番号
    long long w; // 重み
    Edge(int to, long long w) : to(to), w(w) {}
};

// 重み付きグラフを表す型
using Graph = vector<vector<Edge>>;

// 負閉路の検出を行うが、あくまで始点sから到達可能な負閉路のみであることに注意する
int main()
{
    // 頂点数，辺数，始点
    int N, M, s;
    cin >> N >> M >> s;

    // グラフ
    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        G[a].push_back(Edge(b, w));
    }

    // ベルマン・フォード法
    bool exist_negative_cycle = false; // 負閉路をもつかどうか
    vector<long long> dist(N, INF);
    dist[s] = 0;
    for (int iter = 0; iter < N; ++iter)
    {
        bool update = false; // 更新が発生したかどうかを表すフラグ
        for (int v = 0; v < N; ++v)
        {
            // dist[v] = INF のときは頂点 v からの緩和を行わない
            if (dist[v] == INF)
                continue;

            for (auto e : G[v])
            {
                // 緩和処理を行い，更新されたら update を true にする
                if (chmin(dist[e.to], dist[v] + e.w))
                {
                    update = true;
                }
            }
        }

        // 更新が行われなかったら，すでに最短路が求められている
        if (!update)
            break;

        // N 回目の反復で更新が行われたならば，負閉路をもつ
        if (iter == N - 1 && update)
            exist_negative_cycle = true;
    }

    // 結果出力
    if (exist_negative_cycle)
        cout << "NEGATIVE CYCLE" << endl;
    else
    {
        for (int v = 0; v < N; ++v)
        {
            if (dist[v] < INF)
                cout << dist[v] << endl;
            else
                cout << "INF" << endl;
        }
    }
}
