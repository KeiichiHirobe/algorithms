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

struct S {
    ll v;
    int sz;
};

S op(S a, S b) {
    return S{a.v + b.v, a.sz + b.sz};
}

S e() {
    return S{0, 0};
}

// ax + b
struct F {
    int a;
    int b;
};

S mapping(F f, S x) {
    return {f.a * x.v + f.b * x.sz, x.sz};
}

F comp(F f, F g) {
    return F{f.a * g.a, f.a * g.b + f.b};
}

F id() {
    return F{1, 0};
}

// https://atcoder.jp/contests/abc278/tasks/abc278_d
int main() {
    cout << fixed << setprecision(16);
    int n;
    cin >> n;
    // ax+bを区間に行い、和を取得可能
    lazy_segtree<S, op, e, F, mapping, comp, id> seg(n);
    rep(i, 0, n) {
        int x;
        cin >> x;
        seg.set(i, {x, 1});
    }

    int q;
    cin >> q;
    rep(i, 0, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            seg.apply(0, n, {0, x});
        } else if (t == 2) {
            int j, x;
            cin >> j >> x;
            --j;
            seg.apply(j, {1, x});
        } else {
            int j;
            cin >> j;
            --j;
            cout << seg.get(j).v << endl;
        }
    }
}