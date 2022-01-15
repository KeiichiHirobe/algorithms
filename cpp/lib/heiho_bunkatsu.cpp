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

// https://kujira16.hateblo.jp/entry/2016/12/15/000000
const int sqrtN = 512;
struct SqrtDecomposition
{
    int N, K;
    vector<int> data;
    vector<int> bucketSum;
    SqrtDecomposition(int n) : N(n)
    {
        K = (N + sqrtN - 1) / sqrtN;
        data.assign(K * sqrtN, 0);
        bucketSum.assign(K, 0);
    }
    void add(int x, int y)
    {
        int k = x / sqrtN;
        data[x] += y;
        int sum = 0;
        for (int i = k * sqrtN; i < (k + 1) * sqrtN; ++i)
        {
            sum += data[i];
        }
        bucketSum[k] = sum;
    }
    // [x, y)
    ll getSum(int x, int y)
    {
        ll sum = 0;
        for (int k = 0; k < K; ++k)
        {
            int l = k * sqrtN, r = (k + 1) * sqrtN;
            if (r <= x || y <= l)
                continue;
            if (x <= l && r <= y)
            {
                sum += bucketSum[k];
            }
            else
            {
                for (int i = max(x, l); i < min(y, r); ++i)
                {
                    sum += data[i];
                }
            }
        }
        return sum;
    }
};

signed main()
{
    int N, Q;
    cin >> N >> Q;
    SqrtDecomposition decomp(N);
    while (Q--)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
        {
            decomp.add(x - 1, y);
        }
        else
        {
            cout << decomp.getSum(x - 1, y) << endl;
        }
    }
}
