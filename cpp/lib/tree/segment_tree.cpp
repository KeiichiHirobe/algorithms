#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <functional>
#include <queue>
#include <iomanip>
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
// clang-format on

// 遅延セグメント木
// READMEを参照

/* [0,n-1] について、区間ごとの管理する構造体
    set(int i, T x), build(): i番目の要素をxにセット。buildにてまとめてセグ木を構築する。O(n)
    update(a,b,m): [a,b)を mにて加算や上書き。O(log(n))
    query(a,b): [a,b) での結果を取得。O(log(n))
*/

// X: 知りたい結果の型
// M: 更新するときの型
template <typename X, typename M>
struct SegTree
{
    // 要素数を冪乗にまで伸ばした数。葉の要素数に該当
    int n;
    // 複数区間をmergeするときの関数
    using FXX = function<X(X, X)>;
    // 区間に対して、更新を反映させるときの関数
    using FXM = function<X(X, M)>;
    // 遅延列をmergeするときの関数
    using FMM = function<M(M, M)>;
    // 長さを考慮する関数
    using FML = function<M(M, long long)>;
    FXX fxx;
    FXM fxm;
    FMM fmm;
    const X ex;
    const M em;
    // 初期値はexとしている。ex以外にしたい場合は、set/buildを呼ぶこと
    // 葉の要素数は実際の要素数と一致しない可能性があるため、初期化は必ず単位元で行う必要がある
    vector<X> dat;
    vector<M> lazy;
    FML fml;
    SegTree(
        int n_, FXX fxx, FXM fxm, FMM fmm, X ex, M em, FML fml = [](M m, long long size) -> M
        { return m; }) : n(), fxx(fxx), fxm(fxm), fmm(fmm), ex(ex), em(em), dat(n_ * 4, ex), lazy(n_ * 4, em), fml(fml)
    {
        int x = 1;
        while (n_ > x)
            x *= 2;
        n = x;
    }
    void set(int i, X x) { dat[i + n - 1] = x; }
    void build()
    {
        for (int k = n - 2; k >= 0; k--)
            dat[k] = fxx(dat[2 * k + 1], dat[2 * k + 2]);
    }

    /* lazy eval */
    void eval(int k, long long len)
    {
        if (lazy[k] == em)
            return; // 更新するものが無ければ終了

        if (k < n - 1)
        { // 葉でなければ子に伝搬
            lazy[k * 2 + 1] = fmm(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = fmm(lazy[k * 2 + 2], lazy[k]);
        }
        // 自身を更新
        dat[k] = fxm(dat[k], fml(lazy[k], len));
        lazy[k] = em;
    }

    void update(int a, int b, M m, int k, int l, int r)
    {
        eval(k, r - l);
        if (a <= l && r <= b)
        { // 完全に内側の時
          // 区間全体に均等に作用することに注意
            lazy[k] = m;
            eval(k, r - l);
        }
        else if (a < r && l < b)
        {                                               // 一部区間が被る時
            update(a, b, m, k * 2 + 1, l, (l + r) / 2); // 左の子
            update(a, b, m, k * 2 + 2, (l + r) / 2, r); // 右の子
            dat[k] = fxx(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, M m) { update(a, b, m, 0, 0, n); }

    // the minimum element of [a,b)
    X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    X query_sub(int a, int b, int k, int l, int r)
    {
        eval(k, r - l);
        if (r <= a || b <= l)
        {
            return ex;
        }
        else if (a <= l && r <= b)
        {
            return dat[k];
        }
        else
        {
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fxx(vl, vr);
        }
    }
    // ノードがminの場合
    // find_rightest_less(a,b,x): [a,b) で 結果がx以下となる最右位置を求める。O(log(n))
    int find_rightest_less(int a, int b, X x) { return find_rightest_sub(a, b, x, 0, 0, n, true); }
    // find_leftest_less(a,b,x): [a,b) で 結果がx以下となる最左位置を求める。O(log(n))
    int find_leftest_less(int a, int b, X x) { return find_leftest_sub(a, b, x, 0, 0, n, true); }

    // ノードがmaxの場合
    // find_rightest_greater(a,b,x): [a,b) で 結果がx以上となる最右位置を求める。O(log(n))
    int find_rightest_greater(int a, int b, X x) { return find_rightest_sub(a, b, x, 0, 0, n, false); }
    // find_leftest_greater(a,b,x): [a,b) で 結果がx以上となる最左位置を求める。O(log(n))
    int find_leftest_greater(int a, int b, X x) { return find_leftest_sub(a, b, x, 0, 0, n, false); }

    int find_rightest_sub(int a, int b, X x, int k, int l, int r, bool less)
    {
        eval(k, r - l);
        if ((less && dat[k] > x) || (!less && dat[k] < x) || r <= a || b <= l)
        {
            return a - 1;
        }
        else if (k >= n - 1)
        { // 自分が葉ならその位置をreturn
            return (k - (n - 1));
        }
        else
        {
            int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, less);
            if (vr != a - 1)
            { // 右の部分木を見て a-1 以外ならreturn
                return vr;
            }
            else
            { // 左の部分木を見て値をreturn
                return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, less);
            }
        }
    }
    int find_leftest_sub(int a, int b, X x, int k, int l, int r, bool less)
    {
        eval(k, r - l);
        if ((less && dat[k] > x) || (!less && dat[k] < x) || r <= a || b <= l)
        {
            return b;
        }
        else if (k >= n - 1)
        { // 自分が葉ならその位置をreturn
            return (k - (n - 1));
        }
        else
        {
            int vl = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, less);
            if (vl != b)
            { // 左の部分木を見て b 以外ならreturn
                return vl;
            }
            else
            { // 右の部分木を見て値をreturn
                return find_leftest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, less);
            }
        }
    }

    // ノードがsumの場合
    // sum_lower_bound(a,b,x): [a,b) で aからの合計がx以上となる最左位置を求める。O(log(n))
    int sum_lower_bound(int a, int b, X x) { return find_leftest_sum_sub(a, b, x, 0, 0, n).first; }

    pair<int, X> find_leftest_sum_sub(int a, int b, X x, int k, int l, int r)
    {
        eval(k, r - l);
        if (dat[k] < x || r <= a || b <= l)
        {
            return {b, x - dat[k]};
        }
        else if (k >= n - 1)
        { // 自分が葉ならその位置をreturn
            return {k - (n - 1), x - dat[k]};
        }
        else
        {
            auto [vl, rest] = find_leftest_sum_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            if (vl != b)
            { // 左の部分木を見て b 以外ならreturn
                return {vl, rest};
            }
            else
            { // 右の部分木を見て値をreturn
                return find_leftest_sum_sub(a, b, rest, 2 * k + 2, (l + r) / 2, r);
            }
        }
    }
};

// 上書き更新 -> 最小値
// 上書き更新 -> 和の場合、em=0とすると要素の0への更新が反映されないので誤り。-1など要素としてありえない数字にする
void OverWriteAndMin()
{
    cout << fixed << setprecision(16);
    int n;
    int q;
    cin >> n;
    cin >> q;

    using X = int;
    using M = int;
    auto fxx = [](X x1, X x2) -> X
    { return min(x1, x2); };
    auto fxm = [](X x, M m) -> X
    { return m; };
    auto fmm = [](M m1, M m2) -> M
    { return m2; };
    int ex = numeric_limits<int>::max();
    int em = numeric_limits<int>::max();
    SegTree<X, M> rmq(n, fxx, fxm, fmm, ex, em);

    int MINVAL = 2147483647;
    vector<int> ans;
    rep(i, 0, q)
    {
        int c, s, t, x;
        cin >> c;
        if (c == 0)
        {
            cin >> s >> t >> x;
            ++t;
            rmq.update(s, t, x);
        }
        else
        {
            cin >> s >> t;
            ++t;
            int ret = rmq.query(s, t);
            if (ret == ex)
            {
                ret = MINVAL;
            }
            ans.push_back(ret);
        }
    }
    for (auto x : ans)
    {
        cout << x << endl;
    }
}

// 加算 -> 最小値
void AddAndMin()
{
    cout << fixed << setprecision(16);
    int n;
    int q;
    cin >> n;
    cin >> q;

    using X = int;
    using M = int;
    auto fxx = [](X x1, X x2) -> X
    { return min(x1, x2); };
    auto fxm = [](X x, M m) -> X
    { return x + m; };
    auto fmm = [](M m1, M m2) -> M
    { return m1 + m2; };
    int ex = numeric_limits<int>::max();
    int em = 0;
    SegTree<X, M> rmq(n, fxx, fxm, fmm, ex, em);

    rep(i, 0, n)
    {
        rmq.set(i, 0);
    }
    rmq.build();

    vector<int> ans;
    rep(i, 0, q)
    {
        int c, s, t, x;
        cin >> c;
        if (c == 0)
        {
            cin >> s >> t >> x;
            ++t;
            rmq.update(s, t, x);
        }
        else
        {
            cin >> s >> t;
            ++t;
            int ret = rmq.query(s, t);
            ans.push_back(ret);
        }
    }
    for (auto x : ans)
    {
        cout << x << endl;
    }
}

// 加算 -> 合計
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja
void AddAndSum()
{
    cout << fixed << setprecision(16);
    int n;
    int q;
    cin >> n;
    cin >> q;

    using X = ll;
    // Mもlong longにする必要があることにする必要があることに注意！！
    // lazyに溜まり続ける可能性があるため
    using M = ll;
    auto fxx = [](X x1, X x2) -> X
    { return x1 + x2; };
    auto fxm = [](X x, M m) -> X
    { return x + m; };
    auto fmm = [](M m1, M m2) -> M
    { return m1 + m2; };
    auto fml = [](M m, ll size) -> M
    { return m * size; };
    ll ex = 0;
    ll em = 0;
    SegTree<X, M> rmq(n, fxx, fxm, fmm, ex, em, fml);

    vector<ll> ans;
    rep(i, 0, q)
    {
        int c, s, t, x;
        cin >> c;
        if (c == 0)
        {
            cin >> s >> t >> x;
            // ここだけデクリメントしているのは単に1-indexのため
            --s;
            --t;
            ++t;
            rmq.update(s, t, x);
        }
        else
        {
            cin >> s >> t;
            --s;
            --t;
            ++t;
            ll ret = rmq.query(s, t);
            ans.push_back(ret);
        }
    }
    for (auto x : ans)
    {
        cout << x << endl;
    }
}

// https://atcoder.jp/contests/arc033/tasks/arc033_3
// 数の集合 S に対する以下のクエリを処理してください。
// タイプ 1 ： S に数 X を追加する。
// タイプ 2 ： S に含まれる数のうち X 番目に小さい数を答え、その数を S から削除する。

// シンプルに区間に和を保持。find_leftest_sumで取得
void AddAndSumLowerBound()
{
    cout << fixed << setprecision(16);
    // 0,1, ... 200000
    int n = 200001;

    int q;
    cin >> q;

    using X = ll;
    using M = ll;
    auto fxx = [](X x1, X x2) -> X
    { return x1 + x2; };
    auto fxm = [](X x, M m) -> X
    { return x + m; };
    auto fmm = [](M m1, M m2) -> M
    { return m1 + m2; };
    auto fml = [](M m, ll size) -> M
    { return m * size; };

    ll ex = 0;
    ll em = 0;
    SegTree<X, M> rmq(n, fxx, fxm, fmm, ex, em, fml);

    vector<ll> ans;
    rep(i, 0, q)
    {
        int c;
        int x;
        cin >> c;
        cin >> x;
        if (c == 1)
        {
            rmq.update(x, x + 1, 1);
        }
        else
        {
            // 1-index
            int idx = rmq.sum_lower_bound(0, n, x);
            ans.push_back(idx);
            rmq.update(idx, idx + 1, -1);
        }
    }
    for (auto x : ans)
    {
        cout << x << endl;
    }
}

// AddAndSumLowerBoundの別解
// 追加時にX以上の区間に全て1を足す
// ノードにmaxを持たせる
// find_leftest_greater(0,n,x): 全区間で結果がx以上となる最左位置を求める。O(log(n))
void AddAndMaxLowerBound()
{
    cout << fixed << setprecision(16);
    // 0,1, ... 200000
    int n = 200001;

    int q;
    cin >> q;

    using X = ll;
    using M = ll;
    auto fxx = [](X x1, X x2) -> X
    { return max(x1, x2); };
    auto fxm = [](X x, M m) -> X
    { return x + m; };
    auto fmm = [](M m1, M m2) -> M
    { return m1 + m2; };
    ll ex = 0;
    ll em = 0;
    SegTree<X, M> rmq(n, fxx, fxm, fmm, ex, em);

    vector<ll> ans;
    rep(i, 0, q)
    {
        int c;
        int x;
        cin >> c;
        cin >> x;
        if (c == 1)
        {
            rmq.update(x, n, 1);
        }
        else
        {
            // 1-index
            int idx = rmq.find_leftest_greater(0, n, x);
            ans.push_back(idx);
            rmq.update(idx, n, -1);
        }
    }
    for (auto x : ans)
    {
        cout << x << endl;
    }
}

int main()
{
    // OverWriteAndMin();
    AddAndSumLowerBound();
}
