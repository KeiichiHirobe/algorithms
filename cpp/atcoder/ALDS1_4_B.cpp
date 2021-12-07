#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
// clang-format off
#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
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
    vector<int> v(n, 0);
    rep(i, n)
    {
        cin >> v[i];
    }

    sort(ALL(v));

    int target = 0;
    int cnt = 0;

    cin >> m;
    rep(i, m)
    {
        cin >> target;
        auto l = lower_bound(ALL(v), target);
        auto u = upper_bound(ALL(v), target);

        if (l != v.end() && l != u)
        {
            ++cnt;
        }
    }
    cout << cnt << endl;
}