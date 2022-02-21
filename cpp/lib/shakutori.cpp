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

#include <iostream>
#include <vector>
using namespace std;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_C&lang=jp
// a_{l} + a_{l+1} + .. + a_{r-1} + a_{r} <= x を満たす(l,r) の組の個数
int main()
{
    /* 入力受け取り */
    int n, Q;
    cin >> n >> Q;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    /* Q 回分のクエリを処理 */
    for (int j = 0; j < Q; ++j)
    {
        long long x;
        cin >> x; // 各クエリ x

        /* 合計値 */
        long long res = 0;

        /* 区間の左端 left で場合分け */
        int right = 0;     // 毎回 right を使い回すようにする
        long long sum = 0; // sum も使い回す
        for (int left = 0; left < n; ++left)
        {
            /* sum に a[right] を加えても大丈夫なら right を動かす */
            while (right < n && sum + a[right] <= x)
            {
                sum += a[right];
                ++right;
            }

            /* break した状態で right は条件を満たす最大 */
            res += (right - left);

            /* left をインクリメントする準備 */
            if (right == left)
                ++right; // right が left に重なったら right も動かす
            else
                sum -= a[left]; // left のみがインクリメントされるので sum から a[left] を引く
        }

        cout << res << endl;
    }
}