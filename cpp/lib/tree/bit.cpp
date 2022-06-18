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

/*
https://algo-logic.info/binary-indexed-tree/
http://hos.ac/slides/20140319_bit.pdf

BITの使い所
* 1点に対する加算で区間和を求めたい時
* 特に、多次元の場合

厳密には、和以外も可能な場合があったり、区間に対する加算もできるが複雑なのでsegment treeを使った方がいい
例えば、以下は対応可能
* 要素をより大きい値にのみ更新
* 区間の最大値を取得


BITの応用

BITとBIT上での二分探索を活用すると、集合を管理して、

a が何番目に小さいか
w 番目に小さい要素 a は何か
というのを以下のように𝑂(𝑙𝑜𝑔𝑛)で高速に取得することが可能です。

add(a,1): 集合への要素aの追加(a番目を1にする)
add(a,-1): 集合への要素aの削除(a番目を1から0にする)
sum(a): a が何番目に小さいか
lower_bound(w): w 番目に小さい要素 a は何か

ただし、この場合aの範囲が10^6を超えてくるとメモリが足りなくなるので座標圧縮が必要

*/

/* BIT: 区間和の更新や計算を行う構造体
    初期値は a_1 = a_2 = ... = a_n = 0
    ・add(i,x): a_i += x とする
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    計算量は全て O(logn)
    実装の都合上、1-indexであることに注意
*/
template <typename T>
struct BIT
{
    int n;         // 配列の要素数(数列の要素数+1)
    vector<T> bit; // データの格納先
    BIT(int n_) : n(n_ + 1), bit(n, 0) {}

    // i >= 1
    void add(int i, T x)
    {
        for (int idx = i; idx < n; idx += (idx & -idx))
        {
            bit[idx] += x;
        }
    }

    T sum(int i)
    {
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx))
        {
            s += bit[idx];
        }
        return s;
    }

    // [l,r)
    T rangeSum(int l, int r)
    {
        return sum(r - 1) - sum(l - 1);
    }

    // a_1 + a_2 + ... + a_x >= w となるような最小のxを求める(ただし a_i >= 0)
    // O(log(n))
    int lower_bound(T w)
    { // a_1 + a_2 + ... + a_x >= w となるような最小の x を求める(ただし a_i >= 0)
        if (w <= 0)
        {
            return 0;
        }
        else
        {
            int x = 0, r = 1;
            while (r < n)
                r = r << 1;
            for (int len = r; len > 0; len = len >> 1)
            { // 長さlenは1段下るごとに半分に
                if (x + len < n && bit[x + len] < w)
                { // 採用するとき
                    w -= bit[x + len];
                    x += len;
                }
            }
            return x + 1;
        }
    }
};

/* BIT2D:
    初期値は全て0
    ・add(h,w,x): (h,w) に x を加算する
    ・sum(h,w): 1≦i≦h かつ 1≦j≦w の範囲の合計値を求める
    ・rangeSum(h1,w1,h2,w2): h1≦i<h2 かつ w1≦j<w2 の範囲の合計値を求める(1-indexed)
    計算量は全て O(logW * logH)
*/
template <typename T>
struct BIT2D
{
    int H, W;
    vector<vector<T>> bit;
    BIT2D(int H_, int W_) { init(H_, W_); }
    void init(int H_, int W_)
    {
        H = H_ + 1;
        W = W_ + 1;
        bit.assign(H, vector<T>(W, 0));
    }

    void add(int h, int w, T x)
    {
        for (int i = h; i < H; i += (i & -i))
        {
            for (int j = w; j < W; j += (j & -j))
            {
                bit[i][j] += x;
            }
        }
    }
    // 1≦i≦h かつ 1≦j≦w
    T sum(int h, int w)
    {
        T s(0);
        for (int i = h; i > 0; i -= (i & -i))
        {
            for (int j = w; j > 0; j -= (j & -j))
            {
                s += bit[i][j];
            }
        }
        return s;
    }

    // h1≦i<h2 かつ w1≦j<w2
    T rangeSum(int h1, int w1, int h2, int w2)
    {
        return sum(h2 - 1, w2 - 1) - sum(h2 - 1, w1 - 1) - sum(h1 - 1, w2 - 1) + sum(h1 - 1, w1 - 1);
    }
};

// https://yukicoder.me/problems/no/649
// 値を追加
// K番目に大きい値を取得して削除

int main()
{
    int Q, K;

    cin >> Q >> K;
    // 1 or 2
    vector<int> C(Q);
    // case 1
    vector<ll> V(Q, -1);
    vector<ll> Map;

    rep(i, 0, Q)
    {
        int which;
        int v;
        cin >> which;
        C[i] = which;
        if (which == 1)
        {
            cin >> V[i];
            Map.push_back(V[i]);
        }
    }

    sort(Map.begin(), Map.end());
    auto itr = unique(Map.begin(), Map.end());
    Map.erase(itr, Map.end());

    // Mapのidx+1をbitのvalueとしていることに注意
    BIT<int> bit(Map.size());
    rep(i, 0, Q)
    {
        if (C[i] == 1)
        {
            bit.add(lower_bound(Map.begin(), Map.end(), V[i]) - Map.begin() + 1, 1);
        }
        else
        {
            int idx = bit.lower_bound(K);
            if (idx > Map.size()) {
                cout << -1 << endl;
            } else {
                cout << Map[idx-1] << endl;
                bit.add(idx, -1);
            }
        }
    }
}