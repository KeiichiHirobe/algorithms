#include <bits/stdc++.h>

#include <atcoder/all>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using namespace atcoder;
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
// clang-format on

// https://drken1215.hatenablog.com/entry/2019/02/04/013700
// https://torus711.hatenablog.com/entry/20150423/1429794075
// 難し目の問題であるが、https://atcoder.jp/contests/abc295/submissions/40060711
// はわかりやすい書き方で良い。これを真似して以下を書いている

// 桁DP
// 4or9が含まれるn以下の数字の数
// v[i]には各桁が入っている
ll solve(const vector<int> &v) {
    // dp[i][j]
    // i: 0 or 1  i=1なら未満であることが既に確定している
    // j: 0 or 1  j=1なら既に4or9が含まれている
    vector dp(2, vector<ll>(2));
    dp[0][0] = 1;

    int n = v.size();
    rep(i, 0, n) {
        vector prev(2, vector<ll>(2));
        swap(dp, prev);
        rep(j, 0, 2) {
            rep(k, 0, 2) {
                rep(d, 0, 10) {
                    int nj = j;
                    int nk = k;
                    if (j == 0) {
                        if (d < v[i]) {
                            nj = 1;
                        }
                        if (v[i] < d)
                            continue;
                    }
                    if (k == 0) {
                        if (d == 4 or d == 9) {
                            nk = 1;
                        }
                    }
                    dp[nj][nk] += prev[j][k];
                }
            }
        }
    }
    return dp[0][1] + dp[1][1];
}

// 数字を桁の配列にしているだけ
vector<int> digit(ll n) {
    vector<int> v;
    while (n) {
        v.push_back(n % 10);
        n = n / 10;
    }
    reverse(v.begin(), v.end());
    return v;
}

// https://atcoder.jp/contests/abc007/tasks/abc007_4
// n以上m以下の数字で4or9が含まれる数字は全部でいくつか？
// 含まれない数字を求めて全体から引いた方が簡単だが練習のため愚直に解いている
int main() {
    cout << fixed << setprecision(16);
    ll n;
    ll m;
    cin >> n;
    cin >> m;
    ll cnt = solve(digit(m)) - solve(digit(n - 1));
    cout << cnt << endl;
}


// 参考
// 最初の桁がaで最後の桁がbであるv以下の正数の個数
// v[i]には各桁が入っている
ll solve(const vector<int> &v, int a, int b) {
    // dp[i][j]
    // i: 0 or 1  i=1なら未満であることが既に確定している
    // j: 0 or 1  j=1なら既にnot 0が登場
    vector dp(2, vector<ll>(2));
    dp[0][0] = 1;

    int n = v.size();
    rep(i, 0, n) {
        vector prev(2, vector<ll>(2));
        swap(dp, prev);
        rep(j, 0, 2) {
            rep(k, 0, 2) {
                rep(d, 0, 10) {
                    int nj = j;
                    int nk = k;
                    if (j == 0) {
                        if (d < v[i]) {
                            nj = 1;
                        }
                        if (v[i] < d)
                            continue;
                    }
                    if (i == n - 1) {
                        if (d != b) {
                            continue;
                        }
                    }
                    if (k == 0 and d != 0) {
                        if (d != a)
                            continue;
                        nk = 1;
                    }
                    dp[nj][nk] += prev[j][k];
                }
            }
        }
    }
    return dp[0][1] + dp[1][1];
}

