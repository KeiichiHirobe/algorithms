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

    // ダイクストラ法
    vector<bool> used(N, false);
    vector<long long> dist(N, INF);
    dist[s] = 0;
    for (int iter = 0; iter < N; ++iter)
    {
        // 「使用済み」でない頂点のうち，dist 値が最小の頂点を探す
        long long min_dist = INF;
        int min_v = -1;
        for (int v = 0; v < N; ++v)
        {
            if (!used[v] && dist[v] < min_dist)
            {
                min_dist = dist[v];
                min_v = v;
            }
        }

        // 大事！！ これは始点sから到達できない頂点が存在する場合に起こる
        // もしそのような頂点が見つからなければ終了する
        if (min_v == -1)
            break;

        // min_v を始点とした各辺を緩和する
        for (auto e : G[min_v])
        {
            chmin(dist[e.to], dist[min_v] + e.w);
        }
        used[min_v] = true; // min_v を「使用済み」とする
    }

    // 結果出力
    for (int v = 0; v < N; ++v)
    {
        if (dist[v] < INF)
            cout << dist[v] << endl;
        else
            cout << "INF" << endl;
    }
}
