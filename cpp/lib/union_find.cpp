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

// ポテンシャル付きUnionFind
struct UnionFind {
    vector<int> par, siz;
    vector<int> diff_weight;

    UnionFind(int n) : par(n, -1), siz(n, 1), diff_weight(n) {
    }

    // 根を求める
    int root(int x) {
        if (par[x] == -1) {
            return x;
        } else {
            int r = root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }

    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    // weight(y) - weight(x) = w となるように merge する
    bool merge(int x, int y, int w) {
        // x と y それぞれについて、 root との重み差分を補正
        w += weight(x);
        w -= weight(y);

        x = root(x), y = root(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y]) {
            swap(x, y);
            w = -w;
        }
        par[y] = x;
        siz[x] += siz[y];
        diff_weight[y] = w;
        return true;
    }

    int weight(int x) {
        root(x);
        return diff_weight[x];
    }

    int diff(int x, int y) {
        return weight(y) - weight(x);
    }

    // グループを返却する
    vector<vector<int>> groups() {
        vector<vector<int>> g(par.size());
        for (int i = 0; i < par.size(); ++i) {
            g[root(i)].push_back(i);
        }
        auto result = std::remove_if(g.begin(), g.end(), [](auto &x) { return x.empty(); });
        g.erase(result, g.end());
        return g;
    }

    // x を含むグループのサイズ
    int size(int x) {
        return siz[root(x)];
    }
};