#include <bits/stdc++.h>

// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
// clang-format on

/*
bitDP
https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#11-bit-dp
https://algo-logic.info/bit-dp/

集合の順序に対してDPを行うフレームワーク
*/

int INF = 1e9;

int main() {
    cout << fixed << setprecision(16);
    int n, m;
    cin >> n >> m;
    vector d(n, vector<int>(n, INF));
    rep(i, 0, m) {
        int s, t, dis;
        cin >> s >> t >> dis;
        d[s][t] = dis;
    }

    vector dp((1 << n), vector<int>(n, -1));
    rep(i, 0, n) {
        dp[1 << i][i] = d[0][i];
    }

    auto rec = [&](auto &&f, int bit, int last) -> int {
        if (dp[bit][last] != -1) {
            return dp[bit][last];
        }
        int dd = INF;
        rep(i, 0, n) {
            if (i == last)
                continue;
            if ((bit >> i) & 1) {
                chmin(dd, f(f, bit ^ (1 << last), i) + d[i][last]);
            }
        }
        return dp[bit][last] = dd;
    };

    int ans = rec(rec, (1 << n) - 1, 0);
    if (ans >= INF) {
        ans = -1;
    }
    cout << ans << endl;
}