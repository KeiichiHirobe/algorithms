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
using Graph = vector<vector<int>>;
// clang-format on

// https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361

// {2,3,5,7} のように必ずしも 0,1,…,9 のすべてが揃っているわけではない集合が与えられて、その部分集合を列挙する方法を考えます。
// bits = (1<<2) | (1<<3) | (1<<5) | (1<<7)
int itrBits(int A)
{
    // bit = (bit - 1) & A
    // bit - 1 により最下位の1を0にしてそれまでの0を1にする
    for (int bit = A; bit != 0; bit = (bit - 1) & A)
    {
        vector<int> S;
        for (int i = 0; i < 1000; ++i)
        {
            if (bit & (1 << i))
            {
                S.push_back(i);
            }
        }
    }
}
/*
172: {2 3 5 7 }
168: {3 5 7 }
164: {2 5 7 }
160: {5 7 }
140: {2 3 7 }
136: {3 7 }
132: {2 7 }
128: {7 }
44: {2 3 5 }
40: {3 5 }
36: {2 5 }
32: {5 }
12: {2 3 }
8: {3 }
4: {2 }
0: {}
*/

// n個の要素の集合{0,1,…,n−1}の部分集合のうち、要素数がKのもののみを列挙する方法を考えます。

// 蟻本p.145
/*
    * bitの最も右の1のみを抽出する:    nbit = bit & -bit
       * -bitはビット反転して+1したもの
    * bitの最も右の1を0にする:        nbit = bit & (bit - 1)
*/
int next_combination(int sub)
{
    int x = sub & -sub, y = sub + x;
    return (((sub & ~y) / x) >> 1) | y;
}

int main()
{
    int n = 5; // {0, 1, 2, 3, 4} の部分集合を考える
    int k = 3; // k=0の時は例外処理が必要

    int bit = (1 << k) - 1; // bit = {0, 1, 2}
    for (; bit < (1 << n); bit = next_combination(bit))
    {
        /* ここに処理を書く */
    }
}

/*
7: {0 1 2 }
11: {0 1 3 }
13: {0 2 3 }
14: {1 2 3 }
19: {0 1 4 }
21: {0 2 4 }
22: {1 2 4 }
25: {0 3 4 }
26: {1 3 4 }
28: {2 3 4 }
*/