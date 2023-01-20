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

/* 参考実装 */
// この実装ではsaの長さは|S|+1であるが、atcoder libは|S|
vector<int> suffixArray(const string &S) {
    int n = S.size();
    vector<int> sa(n + 1);
    vector<int> rank(n + 1);
    rep(i, 0, n) {
        rank[i] = S[i];
    }
    rep(i, 0, n + 1) {
        sa[i] = i;
    }
    rank[n] = 0;
    int sz = 1;

    // 1,0,-1
    auto cmp = [&](int i, int j) {
        int i1 = rank[i];
        int i2 = -1;
        if (i + sz <= n) {
            i2 = rank[i + sz];
        }
        int j1 = rank[j];
        int j2 = -1;
        if (j + sz <= n) {
            j2 = rank[j + sz];
        }
        if (i1 != j1) {
            return (i1 < j1) ? -1 : 1;
        }
        if (i2 != j2) {
            return (i2 < j2) ? -1 : 1;
        }
        return 0;
    };

    vector<int> tmp(n + 1);
    while (sz <= n) {
        sort(sa.begin(), sa.end(), [&](int i, int j) {
            int x = cmp(i, j);
            return x < 0;
        });
        int cur = 0;
        tmp[sa[0]] = 0;
        rep(i, 1, n + 1) {
            if (cmp(sa[i - 1], sa[i]) == 0) {
                tmp[sa[i]] = cur;
            } else {
                tmp[sa[i]] = ++cur;
            }
        }
        rep(i, 0, n + 1) {
            rank[i] = tmp[i];
        }

        sz *= 2;
    }
    return sa;
}

// SにTが存在するかを判定
// 存在するならそのindex、なければ-1
// saの構築にO(n)、検索にO(log|S|*|T|)
int search(const string &S, const string &T, const vector<int> &sa) {
    // atcoder lib
    int l = 0;
    int r = S.size() - 1;
    while (l <= r) {
        int c = (l + r) / 2;
        // < or = or >
        // 負 or 0 or 正
        if (S.compare(sa[c], T.size(), T) < 0) {
            l = c + 1;
        } else {
            r = c - 1;
        }
    }
    if (S.compare(sa[l], T.size(), T) == 0) {
        return sa[l];
    }
    return -1;
}

int op(int a, int b) {
    return min(a, b);
}

int e() {
    return 1e9;
}

// l文字目とr文字目の最長共通文字数
int main() {
    cout << fixed << setprecision(16);
    string S;
    cin >> S;
    int n = S.size();
    // suffix array
    // size n
    vector<int> sa = suffix_array(S);
    // longest common prerfix array
    // size n-1
    vector<int> la = lcp_array(S, sa);
    // 文字列iの位置がsaの何番目か
    vector<int> rank(n);
    rep(i, 0, n) {
        rank[sa[i]] = i;
        int l = -1;
        if (i < n - 1) {
            l = la[i];
        }
        printf("%d:%d %s\n", sa[i], l, S.substr(sa[i]).c_str());
    }

    segtree<int, op, e> seg(la);

    int m;
    cin >> m;
    // 0-indexで、l文字目とr文字目の共通文字列をlog(n)で計算
    // rank[l] < rank[r]とすると
    // min(la[rank[l]], la[rank[l]+1], .. la[rank[r]-1])
    rep(i, 0, m) {
        int l, r;
        cin >> l >> r;
        l = rank[l];
        r = rank[r];
        if (l > r) {
            swap(l, r);
        }
        cout << seg.prod(l, r) << endl;
    }
}