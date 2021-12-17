#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
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

int main()
{
    int n;
    int m;
    cin >> n;
    cin >> m;

    vector<vector<long long>> v(n, vector<long long>(m, 0));
    rep(i, n)
    {
        rep(j, m)
        {
            cin >> v[i][j];
        }
    }

    ll max = 0;
    rep(i, m)
    {
        for (int j = i + 1; j < m; j++)
        {
            long long sum = 0;
            rep(k, n)
            {
                sum += std::max(v[k][i], v[k][j]);
            }
            chmax(max, sum);
        }
    }
    cout << max << endl;
}