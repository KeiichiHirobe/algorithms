#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <functional>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
#define INF (1LL << 60)
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on

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

int main()
{
    cout << fixed << setprecision(16);
    int n;
    int m;
    cin >> n;
    cin >> m;

    vector<vector<long long>> v(n, vector<long long>(m, 0));
    rep(i, 0, n)
    {
        rep(j, 0, m)
        {
            cin >> v[i][j];
        }
    }

    ll max = 0;
    rep(i, 0, m)
    {
        for (int j = i + 1; j < m; j++)
        {
            long long sum = 0;
            rep(k, 0, n)
            {
                sum += std::max(v[k][i], v[k][j]);
            }
            chmax(max, sum);
        }
    }
    cout << max << endl;
}
