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
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
// clang-format on

int main()
{
    cout << fixed << setprecision(16);
    int n;
    cin >> n;
    Graph G(n);

    rep(i, 0, n)
    {
        int k;
        cin >> k;
        rep(j, 0, k)
        {
            int c;
            cin >> c;
            G[i].push_back(c);
            G[c].push_back(i);
        }
    }

    vector<int> H(n);
    int MAXD = 20;
    vector D(MAXD, vector<int>(n, -1));
    auto dfs = [&](auto &&f, int v, int h = 0, int par = -1) -> void
    {
        H[v] = h;
        D[0][v] = par;
        for (auto next_v : G[v])
        {
            if (next_v == par)
                continue;
            f(f, next_v, h + 1, v);
        }
    };
    // 0がroot
    dfs(dfs, 0);

    rep(i, 1, MAXD)
    {
        rep(j, 0, n)
        {
            if (D[i - 1][j] >= 0)
            {
                D[i][j] = D[i - 1][D[i - 1][j]];
            }
        }
    }

    int q;
    cin >> q;
    rep(loop, 0, q)
    {
        int u, v;
        // H[u] > H[v]
        cin >> u >> v;
        if (H[u] < H[v])
        {
            swap(u, v);
        }
        // uをvと同じ高さにする
        int more = H[u] - H[v];
        for (int i = MAXD - 1; i >= 0; --i)
        {
            if ((more >> i) & 1)
            {
                u = D[i][u];
            }
        }
        if (u == v)
        {
            cout << u << endl;
            continue;
        }
        // uとvの共通祖先の一歩手前まで進める
        // 単純な2分探索だとO(logN^2) だが、O(logN) にできる
        for (int i = MAXD - 1; i >= 0; --i)
        {
            int tu = D[i][u];
            int tv = D[i][v];
            if (tu != tv)
            {
                u = tu;
                v = tv;
            }
        }
        // 最後に一つ上がる
        cout << D[0][u] << endl;
    }
}