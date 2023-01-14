#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
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

typedef unsigned long long ull;
#define B1 100000007
#define B2 1000000007

// hash計算にはmodを利用してないが、実質的に 2^64 でmodを取っているのと同値になっている
// hash衝突が起きると誤るが競プロの世界ではcheckしてはいけないらしい
// 実際にはmodは十分大きな素数で取るべきで (2^61-1)
// などが良いようであるが、その場合掛け算がオーバーフローしてしまうので注意が必要 ref:
// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6

// 文字列Sのt_startからsz文字と同じ文字列がs_start以降に存在するか
bool rolling_hash(string const &S, int t_start, int s_start, int sz) {
    // sとtの先頭m文字のハッシュ値sh,thを計算
    ull sh1 = 0, sh2 = 0, th1 = 0, th2 = 0;
    for (int k = 0; k < sz; k++) {
        sh1 = sh1 * B1 + S[s_start + k], sh2 = sh2 * B2 + S[s_start + k];
        th1 = th1 * B1 + S[t_start + k], th2 = th2 * B2 + S[t_start + k];
    }

    if (sh1 == th1 && sh2 == th2)
        return true;

    // B^mを用意する
    ull pow_B_m_1 = 1, pow_B_m_2 = 1;
    for (int k = 0; k < sz; k++) {
        pow_B_m_1 *= B1, pow_B_m_2 *= B2;
    }

    // sをずらしてハッシュ値を更新
    for (int s = s_start + 1; s + sz <= (int)S.length(); s++) {
        sh1 = sh1 * B1 + S[s + sz - 1] - S[s - 1] * pow_B_m_1;
        sh2 = sh2 * B2 + S[s + sz - 1] - S[s - 1] * pow_B_m_2;
        if (sh1 == th1 && sh2 == th2)
            return true;
    }
    return false;
}

// https://atcoder.jp/contests/abc141/tasks/abc141_e
// 非空文字列であって、S の連続する部分文字列として重ならずに 2回以上現れるもののうち、最長のものの長さを出力せよ。
// そのような非空文字列が存在しないときは、0を出力せよ
int main() {
    int n;
    string S;
    cin >> n >> S;

    auto exist = [&](int sz) -> bool {
        if (sz == 0)
            return true;
        bool ok = false;
        for (int i = 0; i + sz + sz <= n; ++i) {
            if (rolling_hash(S, i, i + sz, sz)) {
                ok = true;
                break;
            }
        }
        return ok;
    };

    int ok = 0;
    int ng = (n + 1) / 2 + 1;
    while (ng - ok > 1) {
        int c = (ok + ng) / 2;
        if (exist(c)) {
            ok = c;
        } else {
            ng = c;
        }
    }
    cout << ok << endl;
}
