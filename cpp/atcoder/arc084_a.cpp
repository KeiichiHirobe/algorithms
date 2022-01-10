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
// 素因数分解
vector<pair<long long, long long>> prime_factorize(long long N)
{
    vector<pair<long long, long long>> res;
    for (long long a = 2; a * a <= N; ++a)
    {
        if (N % a != 0)
            continue;
        long long ex = 0;
        while (N % a == 0)
        {
            ++ex;
            N /= a;
        }
        res.push_back({a, ex});
    }

    // 素数
    if (N != 1)
        res.push_back({N, 1});
    return res;
}

bool is2017(int n)
{
    if (n == 1)
        return false;
    auto a = prime_factorize(n);
    if (a[0].first != n)
    {
        return false;
    }
    int m = (n + 1) / 2;
    auto aa = prime_factorize(m);
    if (aa[0].first != m)
    {
        return false;
    }
    return true;
}

// i番目までに満たす数
// res[ri-1] - res[li-2]
vector<int> res(100000, 0);

int main()
{
    cout << fixed << setprecision(16);

    int tmp = 0;
    rep(i, 100000)
    {
        int n = i + 1;
        if (n % 2 != 0)
        {
            if (is2017(n))
            {
                tmp += 1;
            }
        }
        res[i] = tmp;
    }

    int n;
    cin >> n;

    rep(i, n)
    {
        int a;
        int b;
        cin >> a;
        cin >> b;
        int count = 0;
        cout << res[b - 1] - res[a - 2] << endl;
    }
}