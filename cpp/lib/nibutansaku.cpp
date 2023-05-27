#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
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

// midの計算は厳密には left + (right-left) / 2 の方がオーバフローしないので良い

// 基本的な２部探索
// 存在しない場合は-1
int binary_search(const vector<int> &v, const int &value) {
    int left = 0, right = (int)v.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (v[mid] == value) {
            return mid;
        }
        if (v[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// lower_boundを実装したもの
// ng->okとなる単調性において最小のokを返すとした時、
// okの条件は「value以上」となる
int my_lower_bound(const vector<int> &v, const int &value) {
    int left = 0, right = (int)v.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (v[mid] < value) {
            left = mid + 1;
        } else {
            // 等しい場合も含む
            right = mid - 1;
        }
    }
    return left;
}

// ng->ok となる単調性がある時、最小のokを返す
// P(ng) = false, P(ok) = trueが保証されている
int binary_search_min_ok(int ng, int ok, function<bool(int)> P) {
    while (ok - ng > 1) {
        int mid = (ng + ok) / 2;
        if (P(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

// 処理系の実装
// ref: https://en.cppreference.com/w/cpp/algorithm/lower_bound
int my2_lower_bound(const vector<int> &v, const int &value) {
    int a = 0;
    // countはvalueより小さい可能性があり得る要素の個数
    int count = v.size();
    int step;
    while (count > 0) {
        step = count / 2;
        int mid = a + step;
        if (v[mid] < value) {
            a = mid + 1;
            count = count - step - 1;
        } else {
            count = step;
        }
    }
    return a;
}
