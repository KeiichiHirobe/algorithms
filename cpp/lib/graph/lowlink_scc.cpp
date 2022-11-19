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

// 有向グラフにlowlinkをつけ、sccする。
// lowlinkは無向グラフと同じ
// https://www.youtube.com/watch?v=wUgWX0nc4NY
using Graph = vector<vector<int>>;
using P = pair<long, long>;

// 連結でない頂点から既に辿った頂点(seen=true)に辿ることを考慮するためにstackに存在するか否かを確認している
struct LowLink {
    const Graph &G;
    vector<bool> seen;
    vector<bool> inStack;
    // lowlinkが違うものでも同じ成分にあることもあるので注意
    vector<int> ord, low;
    vector<vector<int>> scc;  // 強連結成分分解された頂点集合。各要素を潰すとトポロジカルソートされている
    stack<int> st;
    int k = 0;  // for increment

    LowLink(const Graph &G_) : G(G_) {
        seen.assign(G.size(), false);
        inStack.assign(G.size(), false);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        for (int i = 0; i < (int)G.size(); i++) {
            if (!seen[i])
                dfs(i);
            assert(st.size() == 0);
        }
        reverse(scc.begin(),scc.end());
    }

    void dfs(int v) {
        seen[v] = true;
        ord[v] = k++;
        low[v] = ord[v];
        st.push(v);
        inStack[v] = true;
        for (int x : G[v]) {
            if (seen[x] and not inStack[x]) {
                continue;
            }
            if (!seen[x]) {
                dfs(x);
                low[v] = min(low[v], low[x]);
            } else {
                // youtube実装では以下だが実はロジックに影響ない 
                // 以下だとシンプルにその頂点から辿れる最小の頂点番号になる
                // low[v] = min(low[v], low[x]);
                low[v] = min(low[v], ord[x]);
            }
        }
        // st.pop();
        // inStack[v] = false;
        // stackから取り出すのをサイクルの根元に戻るまで遅延させることで辿りながらsccに分解している
        if (ord[v] == low[v]) {
            vector<int> sc;
            while (true) {
                int x = st.top();
                st.pop();
                inStack[x] = false;
                sc.push_back(x);
                if (x == v)
                    break;
            }
            scc.push_back(sc);
        }
        return;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph G(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }
    LowLink lowlink(G);
    cout << lowlink.scc.size() << endl;
    for (auto x : lowlink.scc) {
        cout << x.size();
        for (auto el : x) {
            cout << " " << el;
        }
        cout << endl;
    }
}
/*
12 16
12 11
11 8
11 10
8 10
10 9
9 8
9 7
7 6
6 5
5 7
6 3
6 4
4 3
2 3
3 2
4 1
*/

/*
12,
11,
9,10,8,
6,7,5,
4,
3,2,
1,
*/
