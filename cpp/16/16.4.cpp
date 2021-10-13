#include <iostream>
#include <vector>
using namespace std;

// グラフを表す構造体
struct Graph
{
    // 辺を表す構造体
    // rev: 逆辺 (to, from) が G[to] の中で何番目の要素か
    // cap: 辺 (from, to) の容量
    struct Edge
    {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
    };

    // 隣接リスト
    vector<vector<Edge>> list;

    // N: 頂点数
    Graph(int N = 0) : list(N) {}

    // グラフの頂点数取得
    size_t size()
    {
        return list.size();
    }

    // Graph インスタンスを G として，
    // G.list[v] を G[v] と書けるようにしておく
    vector<Edge> &operator[](int i)
    {
        return list[i];
    }

    // 辺 e = (u, v) の逆辺 (v, u) を取得する
    Edge &redge(const Edge &e)
    {
        return list[e.to][e.rev];
    }

    // 辺 e = (u, v) に流量 f のフローを流す
    // e = (u, v) の流量が f だけ減少する
    // このとき逆辺 (v, u) の流量を増やす
    void run_flow(Edge &e, int f)
    {
        e.cap -= f;
        redge(e).cap += f;
    }

    // 頂点 from から頂点 to へ容量 cap の辺を張る
    // このとき to から from へも容量 0 の辺を張っておく
    void addedge(int from, int to, int cap)
    {
        int fromrev = (int)list[from].size();
        int torev = (int)list[to].size();
        list[from].push_back(Edge(torev, from, to, cap));
        list[to].push_back(Edge(fromrev, to, from, 0));
    }
};

struct FordFulkerson
{
    static const int INF = 1 << 30; // 無限大を表す値を適切に
    vector<int> seen;

    FordFulkerson() {}

    // 残余グラフ上で s-t パスを見つける (深さ優先探索)
    // 返り値は s-t パス上の容量の最小値 (見つからなかったら 0)
    // f: s から v へ到達した過程の各辺の容量の最小値
    int fodfs(Graph &G, int v, int t, int f)
    {
        // 終端 t に到達したらリターン
        if (v == t)
            return f;

        // 深さ優先探索
        seen[v] = true;
        for (auto &e : G[v])
        {
            if (seen[e.to])
                continue;

            // 容量 0 の辺は実際には存在しない
            if (e.cap == 0)
                continue;

            // s-t パスを探す
            // 見つかったら flow はパス上の最小容量
            // 見つからなかったら f = 0
            int flow = fodfs(G, e.to, t, min(f, e.cap));

            // s-t パスが見つからなかったら次辺を試す
            if (flow == 0)
                continue;

            // 辺 e に容量 flow のフローを流す
            G.run_flow(e, flow);

            // s-t パスを見つけたらパス上最小容量を返す
            return flow;
        }

        // s-t パスが見つからなかったことを示す
        return 0;
    }

    // グラフ G の s-t 間の最大流量を求める
    // ただしリターン時に G は残余グラフになる
    int solve(Graph &G, int s, int t)
    {
        int res = 0;

        // 残余グラフに s-t パスがなくなるまで反復
        while (true)
        {
            seen.assign((int)G.size(), 0);
            int flow = fodfs(G, s, t, INF);

            // s-t パスが見つからなかったら終了
            if (flow == 0)
                return res;

            // 答えを加算
            res += flow;
        }

        // no reach
        return 0;
    }
};

long long GCD(long long a, long long b)
{
    if (b == 0)
        return a;
    else
        return GCD(b, a % b);
}
int main()
{
    vector<int> ret;
    for (;;)
    {

        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        vector<int> a(n);
        vector<int> b(m);
        Graph G(n + m + 2);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; ++i)
        {
            cin >> b[i];
        }

        for (int i = 0; i < n; ++i)
        {
            G.addedge(0, i + 1, 1);
        }

        for (int i = 0; i < m; ++i)
        {
            G.addedge(n + 1 + i, m + n + 1, 1);
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (GCD(a[i], b[j]) != 1)
                {
                    G.addedge(i + 1, n + 1 + j, 1);
                }
            }
        }

        // フォード・ファルカーソン法
        FordFulkerson ff;
        int s = 0, t = m + n + 1;
        ret.push_back(ff.solve(G, s, t));
    }
    for (auto v : ret)
    {
        cout << v << endl;
    }
}
