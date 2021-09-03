#include <iostream>
#include <vector>
using namespace std;

// 無限大を表す値
const long long INF = 1LL << 60; // 十分大きな値を用いる (ここでは 2^60)

// 辺を表す型，ここでは重みを表す型を long long 型とする
struct Edge
{
    int to;      // 隣接頂点番号
    long long w; // 重み
    Edge(int to, long long w) : to(to), w(w) {}
};

// 重み付きグラフを表す型
using Graph = vector<vector<Edge>>;

// 緩和を実施する関数
template <class T>
bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    else
        return false;
}
vector<bool> seen;
bool reachable(const Graph &G, int v, int t)
{
    seen[v] = true; // v を訪問済にする
    if (v == t)
    {
        return true;
    }

    // v から行ける各頂点 next_v について
    for (auto next_v : G[v])
    {
        if (seen[next_v.to])
            continue; // next_v が探索済ならば探索しない
        if (reachable(G, next_v.to, t))
        {
            return true;
        };
    }
    return false;
}

int main()
{
    // 頂点数，辺数，始点
    int N, M, s;
    cin >> N >> M;
    s = 0;

    // グラフ
    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        --a;
        --b;
        // -をつける
        G[a].push_back(Edge(b, -w));
    }

    // ベルマン・フォード法
    seen.assign(N, false);
    bool exist_negative_cycle = false;     // 負閉路をもつかどうか
    bool exist_s_t_negatvie_cycle = false; // s-tパスの間に負閉路をもつかどうか
    vector<long long> dist(N, INF);
    dist[s] = 0;
    vector<int> updated;
    for (int iter = 0; iter < N; ++iter)
    {
        updated.clear();
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
                    updated.push_back(v);
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
    if (exist_negative_cycle)
    {
        for (auto e : updated)
        {
            if (reachable(G, e, N - 1) == true)
            {
                exist_s_t_negatvie_cycle = true;
                break;
            }
        }
    }

    // 結果出力
    if (exist_s_t_negatvie_cycle)
        cout << "inf" << endl;
    else
    {
        cout << -dist[N - 1] << endl;
    }
}
