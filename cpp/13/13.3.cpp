#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> color;
// 幅優先の例
// 入力: グラフ G と，探索の始点 s
// 出力: s から各頂点への最短路長を表す配列
bool BFS(const Graph &G, int s, int initial = 0)
{
    int N = (int)G.size(); // 頂点数
    queue<int> que;

    color[s] = initial;
    que.push(s);

    while (!que.empty())
    {
        int v = que.front();
        que.pop();

        for (int x : G[v])
        {
            if (color[x] != -1)
            {
                if (color[x] == color[v])
                    return false;
                continue;
            }
            color[x] = 1 - color[v];
            que.push(x);
        }
    }
    return true;
}

int main()
{
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ入力受取
    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 探索
    color.assign(N, -1);
    bool is_bipartite = true;
    for (int v = 0; v < N; ++v)
    {
        if (color[v] != -1)
            continue; // v が探索済みの場合は探索しない
        if (!BFS(G, v, 0))
            is_bipartite = false;
    }

    if (is_bipartite)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}