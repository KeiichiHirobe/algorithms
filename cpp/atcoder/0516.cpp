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

vector<int> sum;

const int MINVAL = -100000000;

int maxOfK(const vector<int> d, int k)
{
    int n = d.size();
    sum.assign(n + 1, 0);
    rep(i, n)
    {
        sum[i + 1] = sum[i] + d[i];
    }
    int maxV = MINVAL;
    rep(i, n - k)
    {
        chmax(maxV, sum[i + k] - sum[i]);
    }
    return maxV;
}

int main()
{
    while (true)
    {
        cout << fixed << setprecision(16);
        int n;
        int k;
        cin >> n;
        cin >> k;
        if (n == 0 && k == 0)
            break;
        vector<int> d(n, 0);
        rep(i, n)
        {
            cin >> d[i];
        }
        cout << maxOfK(d, k) << endl;
    }
}