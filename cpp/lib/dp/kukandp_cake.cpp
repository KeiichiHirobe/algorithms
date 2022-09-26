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

/*
https://atcoder.jp/contests/joi2015ho/tasks/joi2015ho_b

ホールケーキを両端から取っていく。自分は最善の方法を選択できるが、相手は大きい方を必ずとる
自分はどれだけの量を取れるか

[i,j)として区間DPする。
円環の区間をどう表現するか。

n=4の例(0-index)

* 通常の区間の場合

5 x 5 配列

xoooo
xxooo
xxxoo
xxxxo

[0,4)が答え

* 円環の場合

4 x 4 配列

oooo
oooo
oooo
oooo

[3,2) -> 3始まり長さ3の区間
[i,(i+w)%n] となる

(n+1) x (n+1) 配列で表現すると、[i,n) = [i,0)で重複するので n x n で表現する。

[0,0),[1,1),[2,2),[3,3)のmaxが答え

*/

int main()
{
    cout << fixed << setprecision(16);
    int n;
    cin >> n;
    vector<ll> A(n);
    vector dp(n, vector<ll>(n));
    rep(i, 0, n)
    {
        cin >> A[i];
    }

    // この問題の場合、w=1の時にJOIのターンとは限らないので、w=1時点ではdp要素全て0もあり得る
    // 初期値設定の処理を別で書かないのがポイント

    rep(w, 1, n + 1)
    {
        rep(i, 0, n)
        {
            // [i,j)
            int j = (i + w) % n;
            int end = (i + w - 1) % n;
            // joiのターン
            if (w % 2 == n % 2)
            {
                chmax(dp[i][j], A[i] + dp[(i + 1) % n][j]);
                chmax(dp[i][j], A[end] + dp[i][end]);
            }
            else
            {
                if (A[i] > A[end])
                {
                    dp[i][j] = dp[(i + 1) % n][j];
                }
                else
                {
                    dp[i][j] = dp[i][end];
                }
            }
        }
    }

    ll ans = 0;
    rep(i, 0, n)
    {
        chmax(ans, dp[i][i]);
    }

    cout << ans << endl;
}