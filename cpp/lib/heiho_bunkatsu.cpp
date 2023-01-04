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

int INF = 2147483647;

// https://kujira16.hateblo.jp/entry/2016/12/15/000000
// 範囲に対する代入
// 範囲に対するsum取得
// に対応できる平方分割
struct heiho {
    int n;
    // bucket count
    int nb;
    // 1 bucket size
    int B;
    vector<int> a;
    vector<int> b;
    // lazy update
    vector<int> lb;

    heiho(int n) : n(n) {
        B = sqrt(n);
        nb = (n + B - 1) / B;
        a.assign(n, INF);
        b.assign(nb, INF);
        lb.assign(nb, -1);
    }

    // lazyをeval
    void eval(int bi) {
        if (lb[bi] == -1)
            return;
        for (int i = bi * B; i < (bi + 1) * B; ++i) {
            a[i] = lb[bi];
        }
        lb[bi] = -1;
    }

    // bucketをeval
    void evalBucket(int bi) {
        if (lb[bi] != -1)
            return;
        int ans = INF;
        for (int i = bi * B; i < (bi + 1) * B; ++i) {
            chmin(ans, a[i]);
        }
        b[bi] = ans;
    }

    // [l,r)
    void update(int l, int r, int x) {
        eval(l / B);
        eval((r - 1) / B);
        int tl = l;
        int tr = r;
        while (tl < tr and tl % B != 0) {
            a[tl] = x;
            ++tl;
        }
        while (tl < tr and tr % B != 0) {
            --tr;
            a[tr] = x;
        }
        while (tl < tr) {
            b[tl / B] = x;
            lb[tl / B] = x;
            tl += B;
        }
        evalBucket(l / B);
        evalBucket((r - 1) / B);
    }

    int query(int l, int r) {
        eval(l / B);
        eval((r - 1) / B);
        int tl = l;
        int tr = r;
        int ans = INF;
        while (tl < tr and tl % B != 0) {
            chmin(ans, a[tl]);
            ++tl;
        }
        while (tl < tr and tr % B != 0) {
            --tr;
            chmin(ans, a[tr]);
        }
        // tl,trはbucketの左端
        while (tl < tr) {
            chmin(ans, b[tl / B]);
            tl += B;
        }
        return ans;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    heiho hf(n);
    rep(i, 0, q) {
        int c;
        cin >> c;
        if (c == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            ++r;
            hf.update(l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            ++r;
            cout << hf.query(l, r) << endl;
        }
    }
}