#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

// 幅優先の例
// 入力: グラフ G と，探索の始点 s
// 出力: s から各頂点への最短路長を表す配列
vector<int> BFS(const Graph &G, int s)
{
    int N = (int)G.size(); // 頂点数
    // vector<bool> seen(N, false);
    vector<int> dist(N, -1); // 全頂点を「未訪問」に初期化
    queue<int> que;

    dist[s] = 0;
    que.push(s);

    while (!que.empty())
    {
        int v = que.front();
        que.pop();

        for (int x : G[v])
        {
            if (dist[x] != -1)
                continue;

            dist[x] = dist[v] + 1;
            que.push(x);
        }
    }
    return dist;
}

// 深さ優先探索
// CAUTION:
// seen.assign(N, false);
vector<bool> seen;
void dfs(const Graph &G, int v)
{
    seen[v] = true;
    for (auto next_v : G[v])
    {
        if (seen[next_v])
            continue;
        dfs(G, next_v);
    }
}