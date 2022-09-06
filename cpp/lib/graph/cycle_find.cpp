#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
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
using Graph = vector<vector<int>>;
// clang-format on

// 0: not visited
// 1: visited (行きがけ)
// 2: visited (帰りがけ)
// 1に訪れた場合、その点はcircleに含まれることを意味する
vector<int> state;

// 弱連結成分(任意の頂点に対してs->tもしくはt->sどちらかにはパスがある)に1つ以下のサイクルがあるという条件下で、サイクル頂点をcycleにつめる
// 返り値はcycle内である場合には起点となった頂点番号。それ以外は-1
// dfsが終わったときにはvが辿れる頂点は全てstate=2になっていることに注意

// 有向グラフを想定している。無向グラフに対応するには辿り元に戻らないように注意
// 具体的には par=-1 を引数に追加してあげる
int dfs(const Graph &G, int v, vector<int> &cycle)
{
    if (state[v] == 1)
        return v;
    if (state[v] == 2)
        return -1;

    state[v] = 1;
    int any = -1;
    for (int x : G[v])
    {
        int r = dfs(G, x, cycle);
        any = max(any, r);
    }
    state[v] = 2;

    if (any == -1)
        return -1;

    cycle.push_back(v);
    // cycleの起点に戻ってきたのでそれ以降はcircleではない
    if (any == v)
    {
        return -1;
    }
    return any;
}

int main()
{
    // 頂点数 (サイクルを一つ含むグラフなので辺数は N で確定)
    int N;
    cin >> N;

    // グラフ入力受取
    Graph G(N);
    for (int i = 0; i < N; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a, --b; // 頂点番号が 1-indexed で与えられるので 0-indexed にする
        G[a].push_back(b);
        // 有向グラフ
        // G[b].push_back(a);
    }

    state.assign(N, 0);
    rep(i, 0, N)
    {
        if (state[i] != 0) continue;
        vector<int> cycle;
        dfs(G, i, cycle);
        for (auto x : cycle)
        {
            cout << x << endl;
        }
    }
}