#include <bits/stdc++.h>

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
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
// clang-format on

// https://snuke.hatenablog.com/entry/2016/07/01/000000
// https://ei1333.github.io/luzhiled/snippets/other/mo.html
// 長さNの数列に対し、Q回の区間クエリを処理する。
// ただし、[l, middle) と [middle, r) の結果をマージすることはできない。（できるならsegtreeでいい）
// ・値の追加操作ができる。（[l, r) から [l-1, r) や [l, r+1) が求まる）
// ・値の削除操作ができる。（[l, r) から [l+1, r) や [l, r-1) が求まる）
// O(N√Q)

// 区間の種類数を答える問題
struct Mo {
    using ADD = function<void(int)>;
    using DEL = function<void(int)>;
    using REM = function<void(int)>;

    // 数列の長さ
    int n;
    // クエリ数
    int q;
    // bucket size
    int sz;
    vector<int> l, r, qi;

    Mo(int n, int q) : n(n), q(q) {
        // 単純にsqrt(n)でも良いが、bucket数をsqrt(q)にした方が計算量が良い
        sz = max(n / int(sqrt(q)), 1);
    }

    // idx番目のクエリで[i,j)
    void add(int idx, int i, int j) {
        qi.push_back(idx);
        l.push_back(i);
        r.push_back(j);
    }

    void init() {
        sort(qi.begin(), qi.end(), [&](int i, int j) -> bool {
            if (l[i] / sz != l[j] / sz) {
                return l[i] / sz < l[j] / sz;
            }
            return r[i] < r[j];
        });
    }

    void solve(const ADD &add, const DEL &del, const REM &rem) {
        // [tl,tr)
        int tl = 0;
        int tr = 0;
        for (auto i : qi) {
            while (l[i] < tl)
                add(--tl);
            while (tr < r[i])
                add(tr++);
            while (tl < l[i])
                del(tl++);
            while (r[i] < tr)
                del(--tr);
            rem(i);
        }
        return;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cur(1e6 + 1, 0);
    int ans = 0;
    rep(i, 0, n) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    Mo mo(n, q);
    rep(i, 0, q) {
        int l, r;
        cin >> l >> r;
        --l;
        mo.add(i, l, r);
    }

    vector<int> qans(q);

    mo.init();

    auto add = [&](int i) -> void {
        ++cur[a[i]];
        if (cur[a[i]] == 1) {
            ++ans;
        }
    };
    auto del = [&](int i) -> void {
        --cur[a[i]];
        if (cur[a[i]] == 0) {
            --ans;
        }
    };
    auto rem = [&](int i) -> void { qans[i] = ans; };

    mo.solve(add, del, rem);

    for (auto x : qans) {
        cout << x << endl;
    }
}