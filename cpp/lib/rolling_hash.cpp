#include <bits/stdc++.h>

#include <atcoder/all>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using namespace atcoder;
using Graph = vector<vector<int>>;
template <typename T> ostream &operator<<(ostream &s, vector<T> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << v[i]; if (i != int(v.size()) - 1) { s << ",";}} s << endl; return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<T>> const &v) { for (int i = 0; i < int(v.size()); ++i ){ s << v[i];} return s;}
template <typename T> ostream &operator<<(ostream &s, vector<vector<vector<T>>> const &v) { for (int i = 0; i < int(v.size()); ++i) { s << "[" << i << "]" << endl; s << v[i];} return s;}
// clang-format on

// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
// modは必ず素数にすべき
// baseはmod未満の数であればなんでもいいが、乱数をとるとコードを見て攻撃することができない。コード見られない限り乱数の必要はない
// modを32bitにすると1e5程度でも50%で衝突する
// modを64bitにすると1e10程度で50%、1e8程度で0.1%なので問題ない
// -> 32bitで二つハッシュをとる
// -> 64bitで一つハッシュをとる
// の２択がるが、後者の場合、途中計算が64bitに収まらないので工夫する必要がある
// 以下は mod = 2^61 - 1 とした工夫
struct RollingHash {
private:
    using ull = unsigned long long;
    static const ull _mod = 0x1fffffffffffffff;
    static ull _base;
    vector<ull> _hashed, _power;

    // a*b % mod をオーバフローしないように計算
    inline ull _mul(ull a, ull b) const {
        ull au = a >> 31;
        ull ad = a & ((1UL << 31) - 1);
        ull bu = b >> 31;
        ull bd = b & ((1UL << 31) - 1);
        ull mid = ad * bu + au * bd;
        ull midu = mid >> 30;
        ull midd = mid & ((1UL << 30) - 1);
        ull ans = au * bu * 2 + midu + (midd << 31) + ad * bd;

        ans = (ans >> 61) + (ans & _mod);
        if (ans >= _mod)
            ans -= _mod;
        return ans;
    }

public:
    RollingHash(const string &s) {
        ll n = s.size();
        _hashed.assign(n + 1, 0);
        _power.assign(n + 1, 0);
        _power[0] = 1;
        for (ll i = 0; i < n; i++) {
            _power[i + 1] = _mul(_power[i], _base);
            _hashed[i + 1] = _mul(_hashed[i], _base) + s[i];
            if (_hashed[i + 1] >= _mod)
                _hashed[i + 1] -= _mod;
        }
    }

    // 0-index
    // [l,r) のハッシュ計算
    ull get(ll l, ll r) const {
        ull ret = _hashed[r] + _mod - _mul(_hashed[l], _power[r - l]);
        if (ret >= _mod)
            ret -= _mod;
        return ret;
    }

    // thisの文字列に含まれる文字列二つを連結する
    // h1,h2は計算ずみハッシュ値、h2lenは二つ目の文字列の長さ
    ull connect(ull h1, ull h2, ll h2len) const {
        ull ret = _mul(h1, _power[h2len]) + h2;
        if (ret >= _mod)
            ret -= _mod;
        return ret;
    }

    // thisの文字列とsを連結
    void connect(const string &s) {
        ll n = _hashed.size() - 1, m = s.size();
        _hashed.resize(n + m + 1);
        _power.resize(n + m + 1);
        for (ll i = n; i < n + m; i++) {
            _power[i + 1] = _mul(_power[i], _base);
            _hashed[i + 1] = _mul(_hashed[i], _base) + s[i - n];
            if (_hashed[i + 1] >= _mod)
                _hashed[i + 1] -= _mod;
        }
    }

    // thisの[l1,r1)とbの[l2,r2)のlargest common prefix の長さ(>=0)を返却
    // 範囲のチェックはクライアント側の責務
    ll LCP(const RollingHash &b, ll l1, ll r1, ll l2, ll r2) const {
        ll len = min(r1 - l1, r2 - l2);
        ll low = 0, high = len + 1;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            if (get(l1, l1 + mid) == b.get(l2, l2 + mid))
                low = mid;
            else
                high = mid;
        }
        return low;
    }
};

mt19937_64 mt{(unsigned int)time(NULL)};
RollingHash::ull RollingHash::_base = mt() % RollingHash::_mod;

// https://atcoder.jp/contests/abc284/tasks/abc284_f
int main() {
    int n;
    cin >> n;
    string t;
    cin >> t;
    RollingHash th(t);
    reverse(t.begin(), t.end());
    RollingHash rth(t);
    for (int i = 0; i <= n; i++) {
        auto x = th.get(0, i);
        auto y = th.get(n + i, 2 * n);
        if (th.connect(x, y, n - i) == rth.get(n - i, 2 * n - i)) {
            cout << t.substr(n - i, n) << endl;
            cout << i << endl;
            return 0;
        }
    }
    puts("-1");
    return 0;
}
