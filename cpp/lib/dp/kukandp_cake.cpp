#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// 2^60
const ll INF = 1LL << 60;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on


/*
https://atcoder.jp/contests/joi2015ho/tasks/joi2015ho_b

ホールケーキを両端から取っていく。自分は最善の方法を選択できるが、相手は大きい方を必ずとる
自分はどれだけの量を取れるか

ポイントは以下
* 最初の一つ何取るかは固定して考える。固定してしまえばあとは両端のどちらかかを場合分けすれば良い
* 区間に対して、[5,2) 等の区間があり得ることに注意する
*/

int n;
vector<ll> v;
vector<vector<ll>> dp;

// 幅wのときに自分が取る番かいなか
bool turn(int cnt)
{
    return (n - cnt) % 2 == 0;
}

int main()
{
    cout << fixed << setprecision(16);
    cin >> n;
    v.resize(n);
    dp.assign(n + 1, vector<ll>(n + 1, 0));
    rep(i, 0, n)
    {
        cin >> v[i];
    }

    // 1 ~ n-1
    rep(w, 1, n)
    {
        // l ~ (l+w)%n
        // 円環なので、[5,2)等も考慮する
        rep(l, 0, n)
        {
            if (turn(w))
            {
                chmax(dp[l][(l + w) % n], v[l] + dp[(l + 1) % n][(l + w) % n]);
                chmax(dp[l][(l + w) % n], v[(l + w - 1) % n] + dp[l][(l + w - 1) % n]);
            }
            else
            {
                if (v[l] < v[(l + w - 1) % n])
                {
                    dp[l][(l + w) % n] = dp[l][(l + w - 1) % n];
                }
                else
                {
                    dp[l][(l + w) % n] = dp[(l + 1) % n][(l + w) % n];
                }
            }
        }
    }
    ll maxV = 0;
    // 一番最初に取るケーキをi番目にする時
    rep(i, 0, n)
    {
        // 幅n-1と組み合わせる
        chmax(maxV, v[i] + dp[(i + 1) % n][(i+1+n-1) % n]);
    }
    cout << maxV << endl;
}
