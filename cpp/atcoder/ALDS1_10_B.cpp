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

int calc(int a, int b, const vector<vector<int>> &dp, const vector<int> &v)
{
    ll min = INF;
    for (int i = 1; i <= b - a; ++i)
    {
        int t = dp[a][a + i - 1] + dp[a + i][b] + v[a - 1] * v[a + i - 1] * v[b];
        chmin(min, ll(t));
    }
    return min;
}

int main()
{
    cout << fixed << setprecision(16);
    int n;
    cin >> n;

    vector<int> v;
    // DP[ i ][ j ] = i 番目から j 番目までの行列をかけた時の最小コスト
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    rep(i, n)
    {
        int a;
        int b;
        cin >> a;
        cin >> b;
        if (i == 0)
        {
            v.push_back(a);
            v.push_back(b);
        }
        else
        {
            v.push_back(b);
        }
    }

    rep(i, n - 1)
    {
        dp[i + 1][i + 2] = v[i] * v[i + 1] * v[i + 2];
    }
    /*
    rep(i, n)
    {
        rep(j, n)
        {
            cout << dp[i + 1][j + 1];
            if (j == n - 1)
            {
                cout << endl;
            }
            else
            {
                cout << ",";
            }
        }
    }
    */
    for (int diff = 2; diff <= n - 1; ++diff)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (i + diff <= n)
            {
                dp[i][i + diff] = calc(i, i + diff, dp, v);
            }
        }
    }
    cout << dp[1][n] << endl;
}