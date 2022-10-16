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

// suffix array
// O(N*(log N)^2)
// 基本的には https://atcoder.github.io/ac-library/document_ja/string.html を使う
vector<int> construct_sa(string S) {
    int n = S.size();
    vector<int> sa(n);
    vector<int> rank(n);
    int k;
    auto cmp = [&](int i, int j) -> bool {
        if (rank[i] != rank[j]) {
            return rank[i] < rank[j];
        }
        int a = i + k < n ? rank[i + k] : -1;
        int b = j + k < n ? rank[j + k] : -1;
        return a < b;
    };

    rep(i, 0, n) {
        sa[i] = i;
        rank[i] = S[i];
    }
    vector<int> trank(n);
    for (k = 1; k <= n; k *= 2) {
        sort(sa.begin(), sa.end(), cmp);
        trank[sa[0]] = 0;
        int cur = 0;
        rep(i, 1, n) {
            if (cmp(sa[i - 1], sa[i])) {
                ++cur;
                trank[sa[i]] = cur;
            } else {
                trank[sa[i]] = cur;
            }
        }
        swap(trank, rank);
    }
    return sa;
}

int main() {
    cout << fixed << setprecision(16);
    string s = "abracadabra";
    for (int x : construct_sa(s)) {
        cout << s.substr(x) << endl;
    }
}
