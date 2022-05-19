#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
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
using Graph = vector<vector<int>>;
// clang-format on
// n:0-9
// n以下の4or9がない数
int cntUnder(int n)
{
    if (n <= 3)
    {
        return n + 1;
    }
    else if (n <= 8)
    {
        return n;
    }
    else
    {
        return n - 1;
    }
}

/*
https://drken1215.hatenablog.com/entry/2019/02/04/013700

桁DPはベースの考え方としては

dp[ i ] := 上からi桁目まで決めたときの暫定スコアの最大値とか最小値など

とするわけですが、例えば K=8357 のとき、

dp[2] を最大にするXが82とかであれば、これは83より小さいので、82の次の桁の数は何でもいい
dp[2] を最大にするXが83であれば、83の次の数は5を超えてはならない

という風に状況が分かれてしまい、困ってしまいます。そこで次元を増やして、8357未満であることが確定しているかを0or1で表現する
*/

// 桁DP
// 4or9が含まれていないn以下の数字の数
// v[i]には各桁が入っている
// 4or9が含まれているn以下の数字の数を返そうとすると、3次元配列になってしまう。なぜなら、ある桁まで含まれていなくてもそれ以降の桁で含まれるようになる可能性があるから。
// そこで、逆に4or9が含まれていないn以下の数字の数を返すようにしている
ll countCondition(const vector<int> &v)
{
    // i:頭からi桁目まで
    // j:exactlyフラグ
    // dp[i][0]:頭からi桁でn未満であることが確定していて、4or9がつかない
    // dp[i][1]:頭からi桁でn未満であることが確定しておらず、4or9がつかない

    int dsize = v.size();
    vector<vector<long long>> dp(dsize + 1, vector<long long>(2, 0));
    // 初期化。dp[0][0] = 0のままであることに注意
    // 1にすると最初の桁で大きい桁を選ぶことを許容してしまう
    dp[0][1] = 1;
    // i-> i+1へのDP
    rep(i, 0, dsize)
    {
        // 頭からi+1桁目
        int D = v[i];
        bool exist = (D == 4 || D == 9);
        // (10 - 2)は、0,1,..9から4,9を除いた数字の数
        dp[i + 1][0] = (dp[i][0] * (10 - 2)) + (dp[i][1] * cntUnder(D - 1));
        if (!exist)
        {
            dp[i + 1][1] = dp[i][1];
        }
    }
    return dp[dsize][0] + dp[dsize][1];
}

// 数字を桁の配列にしているだけ
vector<int> digit(ll n)
{
    vector<int> v;
    while (n)
    {
        v.push_back(n % 10);
        n = n / 10;
    }
    reverse(v.begin(), v.end());
    return v;
}

// https://atcoder.jp/contests/abc007/tasks/abc007_4
// n以上m以下の数字で4or9が含まれる数字は全部でいくつか？
int main()
{
    cout << fixed << setprecision(16);
    ll n;
    ll m;
    cin >> n;
    cin >> m;
    // 4or9が含まれていない数
    ll cnt = countCondition(digit(m)) - countCondition(digit(n - 1));
    cout << m - n + 1 - cnt << endl;
}
