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

long long extGCD(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
// 負の数にも対応した%
long long normalize_mod(long long val, long long m)
{
    long long res = val % m;
    if (res < 0)
        res += m;
    return res;
}

// a^{-1} mod
// Euclidの互除法
// a,pが互いに素として
// ax + py = 1　を満たす整数yが存在するときのxが逆元
long long modinv(long long a, long long mod)
{
    long long x;
    long long y;
    extGCD(a, mod, x, y);
    return normalize_mod(x, mod);
}

// aCb mod
int combi(ll a, ll b, ll mod)
{
    ll ret = 1;
    for (int i = 1; i <= b; ++i)
    {
        ret = ret * modinv(i, mod) % mod;
    }
    for (int i = a; i >= a - b + 1; --i)
    {
        ret = ret * i % mod;
    }
    return ret;
}

int main()
{
    cout << fixed << setprecision(16);
    int n;
    int m;
    cin >> n;
    cin >> m;

    cout << combi((n - 1) + (m - 1), n - 1, 1000000007) << endl;
}
