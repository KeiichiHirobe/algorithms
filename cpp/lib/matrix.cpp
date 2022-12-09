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
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
// clang-format on

template <typename T>
struct matrix {
    int h, w;
    vector<vector<T>> v;
    matrix(int h, int w) : h(h), w(w), v(h, vector<T>(w)) {
    }

    vector<T> &operator[](int i) {
        return v[i];
    }

    const vector<T> &operator[](int i) const {
        return v[i];
    }

    matrix operator*(const matrix &b) const {
        assert(w == b.h);
        matrix ret(h, b.w);
        rep(i, 0, h) {
            rep(j, 0, b.w) {
                rep(k, 0, w) {
                    ret[i][j] += v[i][k] * b[k][j];
                }
            }
        }
        return ret;
    }

    matrix operator^(long long p) const {
        assert(h == w);
        matrix ret(h, w);
        rep(i, 0, h) {
            ret[i][i] = 1;
        }
        matrix cur(*this);
        while (p) {
            if (p & 1) {
                ret = ret * cur;
            }
            cur = cur * cur;
            p = p >> 1;
        }
        return ret;
    }
};

using mint = atcoder::modint998244353;

// https://atcoder.jp/contests/abc280/editorial/5343
int main() {
    cout << fixed << setprecision(16);
    int n, p;
    cin >> n >> p;
    mint critical = mint(p) / 100;
    mint normal = 1 - critical;

    matrix<mint> a(3, 3);
    matrix<mint> init(3, 1);
    init[0][0] = 1;
    init[1][0] = 1 + normal;
    init[2][0] = 1;
    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 0;
    a[1][0] = critical;
    a[1][1] = normal;
    a[1][2] = 1;
    a[2][0] = 0;
    a[2][1] = 0;
    a[2][2] = 1;
    cout << ((a ^ (n - 1)) * init)[0][0].val() << endl;
}