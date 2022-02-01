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
    int n;
    cin >> n;
    vector<ll> v(n + 1, 0);
    rep(i, n)
    {
        int x;
        cin >> x;
        v[i + 1] = v[i] + x;
    }

    sort(v.begin(), v.end());

    ll total = 0;
    ll t = v[0];
    ll cnt = 1;

    rep(i, n + 1)
    {
        if (i == 0)
            continue;
        if (t == v[i])
        {
            ++cnt;
        }
        else
        {
            total += cnt * (cnt - 1) / 2;
            cnt = 1;
            t = v[i];
        }
    }
    total += cnt * (cnt - 1) / 2;
    cout << total << endl;
}