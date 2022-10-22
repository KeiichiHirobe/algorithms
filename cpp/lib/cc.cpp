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

template <typename T = int>
struct CC {
    CC() = default;
    void add(const T &x) {
        dat.push_back(x);
    }
    size_t size() const {
        return dat.size();
    }
    size_t operator()(T x) const {
        return lower_bound(dat.begin(), dat.end(), x) - dat.begin();
    }
    const T &operator[](size_t i) const {
        return dat[i];
    }
    void init() {
        sort(dat.begin(), dat.end());
        dat.erase(unique(dat.begin(), dat.end()), dat.end());
    }
    vector<T> dat;
};

int main() {
    vector<int> v = {1, 3, 4, 2, 2, 3, 6, 1};
    CC cc;
    for (auto x : v) {
        cc.add(x);
    }
    cc.init();
    for (auto x : v) {
        cout << cc(x) << endl;
    }
    cout << "------" << endl;
    rep(i, 0, cc.size()) {
        cout << cc[i] << endl;
    }
}

/*
0
2
3
1
1
2
4
0
------
1
2
3
4
6
*/
