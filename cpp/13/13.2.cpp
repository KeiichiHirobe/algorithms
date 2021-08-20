#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using Graph = vector<vector<int>>;

vector<bool> seen;

void BFS(const Graph &G, int s)
{
    int N = (int)G.size(); // 頂点数
    seen.assign(N, false);
    queue<int> que;

    seen[s] = true;
    que.push(s);

    while (!que.empty())
    {
        int v = que.front();
        que.pop();

        for (int x : G[v])
        {
            if (seen[x] == true)
                continue;

            seen[x] = true;
            que.push(x);
        }
    }
}

int main()
{
    int N, M, s, t;
    cin >> N >> M >> s >> t;

    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    BFS(G, s);

    if (seen[t] == true)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}