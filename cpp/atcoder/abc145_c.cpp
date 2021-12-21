#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
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
    cin >> n;

    vector<int> v(n, 0);

    vector<pair<int, int>> pv(n);

    rep(i, n)
    {
        int x;
        int y;
        cin >> x;
        cin >> y;
        pv[i] = {x, y};
    }

    rep(i, n)
    {
        v[i] = i;
    }

    double total = 0;
    int cnt = 0;

    cout << fixed << setprecision(10);

    do
    {
        for (auto t = v.begin(); t + 1 < v.end(); ++t)
        {
            auto a = pv[*t];
            auto b = pv[*(t + 1)];
            int dx = a.first - b.first;
            int dy = a.second - b.second;
            total += sqrt(double(dx * dx + dy * dy));
        }
        ++cnt;
    } while (next_permutation(v.begin(), v.end()));

    cout << total / (double(cnt)) << endl;
}