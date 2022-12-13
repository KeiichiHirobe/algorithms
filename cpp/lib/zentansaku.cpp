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

// 参考問題: https://atcoder.jp/contests/abc268/submissions/34753666

void solve() {
    int n = 3;
    vector<int> A(n);
    // 合計で最大restを任意の要素に足せる時の配列の全探索
    auto dfs = [&](auto &&f, vector<int> cur, int idx, int rest) -> void {
        if (idx == n) {
            cout << cur;
            return;
        }
        if (rest) {
            ++A[idx];
            f(f, cur, idx, rest - 1);
            --A[idx];
        }
        cur.push_back(A[idx]);
        f(f, cur, idx + 1, rest);
        cur.pop_back();
    };
    dfs(dfs, {}, 0, 3);
}
/*
3,0,0
2,1,0
2,0,1
2,0,0
1,2,0
1,1,1
1,1,0
1,0,2
1,0,1
1,0,0
0,3,0
0,2,1
0,2,0
0,1,2
0,1,1
0,1,0
0,0,3
0,0,2
0,0,1
0,0,0
*/

// 同じ結果
// こちらの方が再帰の種類が1種類なのでわかりやすいが汎用性は低いと思われる
void solve2() {
    int n = 3;
    vector<int> A(n);
    // 合計で最大restを任意の要素に足せる時の配列の全探索
    auto dfs = [&](auto &&f, vector<int> &cur, int idx, int rest) -> void {
        if (idx == n) {
            cout << cur;
            return;
        }
        for (int i = rest; i >= 0; --i) {
            cur.push_back(A[idx] + i);
            f(f, cur, idx + 1, rest - i);
            cur.pop_back();
        }
    };
    vector<int> tmp;
    dfs(dfs, tmp, 0, 3);
}

int main() {
    solve2();
}

// n^n の計算量がかかるが簡単にnext_permutationを実装できる
// https://cpprefjp.github.io/reference/algorithm/next_permutation.html
// 本家だと、n!*n
void nextpermutation(int n) {
    vector<int> cur;
    vector<bool> used(n);

    auto nextp = [&](auto &&f) -> void {
        bool all = true;
        rep(i, 0, n) {
            if (not used[i]) {
                all = false;
                cur.push_back(i + 1);
                used[i] = true;
                f(f);
                cur.pop_back();
                used[i] = false;
            }
        }
        if (all) {
            cout << cur;
        }
    };
    nextp(nextp);
}
