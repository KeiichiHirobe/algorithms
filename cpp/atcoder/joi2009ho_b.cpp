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
    int d;
    int n;
    int m;
    cin >> d;
    cin >> n;
    cin >> m;
    vector<int> v(n + 1, 0);
    v[0] = 0;
    v[n] = d;
    rep(i, n - 1)
    {
        cin >> v[i + 1];
    }

    sort(ALL(v));

    int target = 0;
    int total = 0;
    rep(i, m)
    {
        cin >> target;
        auto l = lower_bound(ALL(v), target);
        auto lbefore = l - 1;

        int ldiff = abs(*l - target);
        int lbeforediff = abs(*lbefore - target);

        total += min(ldiff, lbeforediff);
    }
    cout << total << endl;
}