
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Graph = vector<vector<int>>;

template <class T>
void chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
    }
}

// トポロジカルソートする
vector<bool> seen;
vector<int> order; // トポロジカルソート順を表す
void rec(const Graph &G, int v)
{
    seen[v] = true;
    for (auto next_v : G[v])
    {
        if (seen[next_v])
            continue; // すでに訪問済みなら探索しない
        rec(G, next_v);
    }

    // v-out を記録する
    order.push_back(v);
}

int main()
{
    int N, M;
    cin >> N >> M; // 頂点数と枝数
    Graph G(N);    // 頂点数 N のグラフ
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        G[a].push_back(b);
    }

    // 探索
    seen.assign(N, false); // 初期状態では全頂点が未訪問
    order.clear();         // トポロジカルソート順
    for (int v = 0; v < N; ++v)
    {
        if (seen[v])
            continue; // すでに訪問済みなら探索しない
        rec(G, v);
    }
    reverse(order.begin(), order.end()); // 逆順に

    vector<int> mapv(N);
    for (int i = 0; i < N; i++)
    {
        mapv[order[i]] = i;
    }

    vector<int> dp(N, 0);
    for (int i = 0; i < N - 1; i++)
    {
        for (auto next_v : G[order[i]])
        {
            chmax(dp[mapv[next_v]], dp[i] + 1);
        }
    }

    int max = 0;
    for (int i = 0; i < N; i++)
    {
        chmax(max, dp[i]);
    }
    cout << max << endl;
}