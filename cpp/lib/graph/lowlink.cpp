#include <bits/stdc++.h>

#include <atcoder/all>
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
using namespace atcoder;
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
// clang-format on

// https://algo-logic.info/articulation-points/
// https://www.youtube.com/watch?v=aZXi1unBdJA

using Graph = vector<vector<int>>;
using P = pair<long, long>;

/* Lowlink: グラフの関節点・橋を列挙する構造体
    作成: O(E+V)
    関節点の集合: vector<int> aps
    橋の集合: vector<P> bridges
*/

// この実装は無向グラフでのみ動く
// 有向グラフの場合は連結でない頂点から既に辿った頂点(seen=true)に辿ることを考慮する必要がある
struct LowLink {
    const Graph &G;
    vector<bool> seen;
    vector<int> ord, low;
    vector<int> aps;  // articulation points
    vector<P> bridges;
    int k = 0; // for increment

    LowLink(const Graph &G_) : G(G_) {
        seen.assign(G.size(), false);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        for (int i = 0; i < (int)G.size(); i++) {
            if (!seen[i])
                dfs(i,-1);
        }
        sort(aps.begin(), aps.end());          // 必要ならソートする
        sort(bridges.begin(), bridges.end());  // 必要ならソートする
    }

    // サイクルを発見したらそれより先に進まない
    // ord:先かけ順
    // lowlink:後退辺(DFS木において利用しなかった辺)を最大1度のみ辿ることができる時にその頂点から辿ることができる最小のord
    // ∞のようにサイクルが2つ繋がっている場合、2つのサイクルは異なるlowlinkを持つ場合があることに注意すること！具体的には部分木のルートが∞の中心である時に限り等しくなる
    // [不正確情報] サイクルの個数について。辺を共有するサイクルを1つとカウントするのであれば、ord[v] = low[x] の回数がサイクルの個数になりそう
    void dfs(int v, int par) {
        seen[v] = true;
        ord[v] = k++;
        low[v] = ord[v];
        bool is_aps = false;
        // 子の数
        int count = 0;
        for (int x : G[v]) {
            if (x == par)
                continue;
            if (!seen[x]) {
                count++;
                dfs(x, v);
                low[v] = min(low[v], low[x]);
                // v->xに辿ると、xからvもしくはvの祖先にたどり着けないことを意味する
                if (ord[v] < low[x])
                    bridges.emplace_back(min(v, x), max(v, x));
                // rootではなく、橋のたどる元(<)もしくはサイクルの起点(=)
                // 橋だけでは不十分。∞のようにサイクルが二つつながっているグラフの真ん中の点も関節点
                if (par != -1 && ord[v] <= low[x])
                    is_aps = true;
            } else {
                // min(low[v], low[e.to])ではないことに注意！
                low[v] = min(low[v], ord[x]);
            }
        }
        // rootでDFS木の子が2つ以上
        if (par == -1 && count >= 2)
            is_aps = true;
        if (is_aps)
            aps.push_back(v);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph G(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    LowLink lowlink(G);
    cout << lowlink.bridges.size() << endl;
}
