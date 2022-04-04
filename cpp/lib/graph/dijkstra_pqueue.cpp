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

// 辺を表す型，ここでは重みを表す型を long long 型とします
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
    vector<long long> dist(N, INF);
    dist[s] = 0;

    // (d[v], v) のペアを要素としたヒープを作る
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        que;
    que.push(make_pair(dist[s], s));

    // ダイクストラ法の反復を開始
    while (!que.empty())
    {
        // v: 使用済みでない頂点のうち d[v] が最小の頂点
        // d: v に対するキー値
        int v = que.top().second;
        long long d = que.top().first;
        que.pop();

        // d > dist[v] は，(d, v) がゴミであることを意味する
        if (d > dist[v])
            continue;

        // 頂点 v を始点とした各辺を緩和
        for (auto e : G[v])
        {
            if (chmin(dist[e.to], dist[v] + e.w))
            {
                // 更新があるならヒープに新たに挿入
                que.push(make_pair(dist[e.to], e.to));
            }
        }
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
