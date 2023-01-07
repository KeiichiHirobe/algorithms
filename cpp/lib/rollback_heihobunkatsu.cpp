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
// クエリ平方分割ではdelete操作が必要
// deleteが難しいときは、rollback平方分割で対応できる
// 例としては区間に対するunionfindなどがある。ブログを参照
// rollback分の計算量が加算されるが左端を伸ばす計算量と同じであるため、
// O(N √Q * [追加操作の計算量])
// 注意点として、O(√Q * [初期化にかかる計算量]) が追加でかかることを意識すること

// 区間の種類数を答える問題
struct RollbackHeiho {
    using ADD = function<void(int)>;
    using RESET = function<void()>;
    using SNAPSHOT = function<void()>;
    using ROLLBACK = function<void()>;
    using REM = function<void(int)>;

    // 数列の長さ
    int n;
    int bn;
    // クエリ数
    int q;
    // bucket size
    int sz;
    vector<int> l, r;
    // i番目にi番目のbucketに含まれるqueryのインデックスが含まれる
    // 最後の要素はsz以下の区間を持つものが含まれる
    vector<vector<int>> qi;

    RollbackHeiho(int n, int q) : n(n), q(q) {
        // 単純にsqrt(n)でも良いが、bucket数をsqrt(q)にした方が計算量が良い
        sz = max(n / int(sqrt(q)), 1);
        bn = (n + sz - 1) / sz;
        qi.resize(bn + 1);
    }

    // idx番目のクエリで[i,j)
    void add(int i, int j) {
        l.push_back(i);
        r.push_back(j);
    }

    void init() {
        for (int i = 0; i < q; ++i) {
            int len = r[i] - l[i];
            if (len <= sz) {
                qi[bn].push_back(i);
            } else {
                int idx = l[i] / sz;
                qi[idx].push_back(i);
            }
        }
        for (int i = 0; i < bn; ++i) {
            sort(qi[i].begin(), qi[i].end(), [&](int a, int b) -> bool { return r[a] < r[b]; });
        }
    }

    void solve(const ADD &add, const RESET &reset, const SNAPSHOT &snapshot, const ROLLBACK &rollback, const REM &rem) {
        // まずsz以下のクエリ
        for (auto i : qi[bn]) {
            // resetにしてしまうとTLEするので注意
            snapshot();
            for (int x = l[i]; x < r[i]; ++x) {
                add(x);
            }
            rem(i);
            rollback();
        }

        for (int idx = 0; idx < bn; ++idx) {
            reset();
            int base = (idx + 1) * sz;
            int tr = base;
            for (auto i : qi[idx]) {
                int tl = base;
                while (tr != r[i]) {
                    add(tr);
                    ++tr;
                }
                snapshot();
                while (tl != l[i]) {
                    --tl;
                    add(tl);
                }
                rem(i);
                rollback();
            }
        }
    }
};

// curのidxがx
struct history {
    int idx;
    int x;
    int ans;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cur(1e6 + 1, 0);
    vector<history> log;
    int ans = 0;
    rep(i, 0, n) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    RollbackHeiho rh(n, q);
    rep(i, 0, q) {
        int l, r;
        cin >> l >> r;
        --l;
        rh.add(l, r);
    }

    vector<int> qans(q);

    rh.init();

    auto add = [&](int i) -> void {
        log.push_back({a[i], cur[a[i]], ans});
        ++cur[a[i]];
        if (cur[a[i]] == 1) {
            ++ans;
        }
    };

    auto reset = [&]() -> void {
        cur.assign(1e6 + 1, 0);
        ans = 0;
        log.clear();
    };

    auto snapshot = [&]() -> void { log.clear(); };

    auto rollback = [&]() -> void {
        while (not log.empty()) {
            auto e = log.back();
            log.pop_back();
            cur[e.idx] = e.x;
            ans = e.ans;
        }
    };

    auto rem = [&](int i) -> void { qans[i] = ans; };

    rh.solve(add, reset, snapshot, rollback, rem);

    for (auto x : qans) {
        cout << x << "\n";
    }
}