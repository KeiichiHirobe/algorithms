#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
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
// clang-format on

// K個の連続する整数の和の最大値を求めよ。
int main()
{
    // 入力
    int N, K;
    while (cin >> N >> K)
    {
        if (N == 0)
            break;
        vector<long long> a(N);
        for (int i = 0; i < N; ++i)
            cin >> a[i];

        // 累積和を前計算
        vector<int> s(N + 1, 0);
        for (int i = 0; i < N; ++i)
            s[i + 1] = s[i] + a[i];

        // 答えを求める
        long long res = -INF; // 最初は無限小の値に初期化しておく
        for (int i = 0; i <= N - K; ++i)
        {
            long long val = s[K + i] - s[i];
            if (res < val)
                res = val;
        }
        cout << res << endl;
    }
}