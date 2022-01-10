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

int main()
{
    cout << fixed << setprecision(16);
    int N;
    int W;
    cin >> N;
    cin >> W;

    vector<int> v(N);
    vector<int> w(N);

    rep(i, N)
    {
        cin >> v[i] >> w[i];
    }

    vector<vector<long long>> vmax(W + 1, vector<long long>(N + 1, 0));

    for (int i = 1; i < W + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            chmax(vmax[i][j], vmax[i][j - 1]);
            if (i - w[j - 1] >= 0)
            {
                chmax(vmax[i][j], vmax[i - w[j - 1]][j - 1] + v[j - 1]);
            }
        }
    }
    /*
    rep(i, W + 1)
    {
        rep(j, N + 1)
        {
            cout << vmax[i][j] << ",";
        }
        cout << endl;
    }
    */

    cout << vmax[W][N] << endl;
}