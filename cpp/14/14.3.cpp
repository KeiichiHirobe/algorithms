#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

// 入力: グラフ G と，探索の始点 s
// 出力: s から各頂点への最短路長を表す配列
int BFS(const Graph &G, int s, int t)
{
    int N = (int)G.size();                                // 頂点数
    vector<vector<int>> dist(N, vector<int>{-1, -1, -1}); // 全頂点を「未訪問」に初期化
    queue<pair<int, int>> que;

    // 初期条件 (頂点 s を初期頂点とする)
    dist[s][0] = 0;
    dist[s][1] = -1;
    dist[s][2] = -1;
    que.push(make_pair(s, 0)); // s を橙色頂点にする

    // BFS 開始 (キューが空になるまで探索を行う)
    while (!que.empty())
    {
        pair<int, int> v = que.front(); // キューから先頭頂点を取り出す
        que.pop();
        int which = v.second;
        ++which;
        which %= 3;
        // v からたどれる頂点をすべて調べる
        for (int x : G[v.first])
        {
            // すでに発見済みの頂点は探索しない
            if (dist[x][which] != -1)
                continue;

            // 新たな白色頂点 x について距離情報を更新してキューに挿入
            dist[x][which] = dist[v.first][v.second] + 1;
            que.push(make_pair(x, which));
        }
    }
    return dist[t][0];
}

int main()
{
    // 頂点数と辺数
    int N, M;
    cin >> N >> M;

    // グラフ入力受取 (ここでは無向グラフを想定)
    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        G[a].push_back(b);
    }

    int s, t;
    cin >> s >> t;
    --s;
    --t;

    // 頂点 0 を始点とした BFS
    int d = BFS(G, s, t);
    if (d == -1)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << (d / 3) << endl;
    }
}
