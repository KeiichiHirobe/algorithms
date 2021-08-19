#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

// 深さ優先探索
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

int main()
{
    int N, M;
    cin >> N >> M;
    Graph G(N);
    seen.assign(N, false);
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        if (!seen[i])
        {
            ++cnt;
        }
        dfs(G, i);
    }
    cout << cnt << endl;
}