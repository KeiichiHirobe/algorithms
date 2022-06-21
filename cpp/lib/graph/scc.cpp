#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// 2^60
#define INF (1LL << 60);
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on

int cur = 1;
// 深さ優先探索
// CAUTION:
// seen.assign(N, false);
vector<bool> seen;
void dfs(const Graph &G, int v, vector<int> &postOrder)
{
    seen[v] = true;
    for (auto next_v : G[v])
    {
        if (seen[next_v])
            continue;
        dfs(G, next_v, postOrder);
    }
    postOrder.push_back(v);
}

void dfs2(const Graph &G, int v, vector<int> &cycle)
{
    seen[v] = true;
    cycle.push_back(v);
    for (auto next_v : G[v])
    {
        if (seen[next_v])
            continue;
        dfs2(G, next_v, cycle);
    }
}

// https://manabitimes.jp/math/1250
// グラフの辺を逆順にする
// 元のグラフの帰りがけ順の逆順でまだ辿ってない頂点から始める
// 辿れたところまでが強連結
int main()
{
    cout << fixed << setprecision(16);
    int n;
    int m;
    cin >> n;
    cin >> m;

    Graph G(n);
    // 辺を逆向きにしたもの
    Graph GR(n);

    vector<int> postOrder;
    seen.assign(n, false);
    rep(i, 0, m)
    {
        int from, to;
        cin >> from >> to;
        --from;
        --to;
        G[from].push_back(to);
        GR[to].push_back(from);
    }

    rep(i, 0, n)
    {
        if (seen[i])
            continue;
        dfs(G, i, postOrder);
    }

    seen.assign(n, false);

    // 強連結成分分解された頂点集合
    // 任意の頂点s,tについて、s->t,t->sで辿れる
    vector<vector<int>> cycles;

    while (!postOrder.empty())
    {
        int next = postOrder.back();
        postOrder.pop_back();
        vector<int> cycle;
        if (!seen[next])
        {
            dfs2(GR, next, cycle);
            cycles.push_back(cycle);
        }
    }

    for (auto x : cycles)
    {
        for (auto el : x)
        {
            cout << el + 1 << ",";
        }
        cout << endl;
    }
}
