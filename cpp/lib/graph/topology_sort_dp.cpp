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

vector<int> seen;

void dfs(Graph G, int from, vector<int> &v)
{
    seen[from] = true;
    for (auto e : G[from])
    {
        if (!seen[e.to])
        {
            dfs(G, e.to, v);
        }
    }
    v.push_back(from);
}

void topologySort(Graph G, vector<int> &v)
{
    seen.assign(G.size(), false);
    rep(i, G.size())
    {
        if (!seen[i])
        {
            dfs(G, i, v);
        }
    }
    reverse(v.begin(), v.end());
}

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

    vector<int> sorted;
    topologySort(G, sorted);

    vector<long long> dist(N, INF);
    dist[s] = 0;

    rep(i, N) {
        int from = sorted[i];
        if (dist[from] < INF) {
            for (auto e:G[from]) {
                chmin(dist[e.to], dist[from] + e.w);
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
