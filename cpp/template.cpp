#include <bits/stdc++.h>

#include <atcoder/all>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using namespace atcoder;
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
// clang-format on

// 幅優先の例
// 入力: グラフ G と，探索の始点 s
// 出力: s から各頂点への最短路長を表す配列
vector<int> BFS(const Graph &G, int s) {
    int N = (int)G.size();  // 頂点数
    // vector<bool> seen(N, false);
    vector<int> dist(N, -1);  // 全頂点を「未訪問」に初期化
    queue<int> que;

    dist[s] = 0;
    que.push(s);

    while (!que.empty()) {
        int v = que.front();
        que.pop();

        for (int x : G[v]) {
            if (dist[x] != -1)
                continue;

            dist[x] = dist[v] + 1;
            que.push(x);
        }
    }
    return dist;
}

int main() {
    cout << fixed << setprecision(16);
    int n, s, t;
    cin >> n >> s >> t;
    vector<bool> seen(n, false);
    Graph G(n);
    auto dfs = [&](auto &&f, int v) -> void {
        seen[v] = true;
        for (auto nv : G[v]) {
            if (seen[nv])
                continue;
            f(f, nv);
        }
    };

    dfs(dfs, s);
    if (seen[t]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}