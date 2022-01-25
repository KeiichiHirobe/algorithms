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

// 想定する要素最大数
const int MAX_N = 1 << 17;
const int MAXVAL = (1LL << 31) - 1;

struct SegmentTree
{
    // 要素数
    int origN;
    // 完全木にした時の要素数
    int n;
    vector<int> dat;

    SegmentTree(int n_) : origN(n_)
    {
        int expoN = 1;
        while (n_ > expoN)
            expoN *= 2;
        n = expoN;
        // 以下の割り当て数に注意！
        dat.assign(2 * n - 1, MAXVAL);
    }

    // k番目(0-indexed)をaにupdate
    void update(int k, int a)
    {
        int i = k + n - 1;
        dat[i] = a;
        while (i > 0)
        {
            i = (i - 1) / 2;
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    ll query(int a, int b)
    {
        return query(a, b, 0, 0, n);
    }
    // [a, b)の最小値
    // kは節点の番号、l,rはその節点が[l,r)に対応づいていることを表す。
    ll query(int a, int b, int k, int l, int r)
    {
        if (b <= l || r <= a)
            return MAXVAL;
        if (a <= l && r <= b)
            return dat[k];

        return min(
            query(a, b, 2 * k + 1, l, (r + l) / 2),
            query(a, b, 2 * k + 2, (r + l) / 2, r));
    }
};

signed main()
{
    int N, Q;
    cin >> N >> Q;
    SegmentTree stree(N);
    while (Q--)
    {
        int c;
        cin >> c;
        if (c == 0)
        {
            int i, value;
            cin >> i >> value;
            stree.update(i, value);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << stree.query(a, b + 1) << endl;
        }
    }
}
