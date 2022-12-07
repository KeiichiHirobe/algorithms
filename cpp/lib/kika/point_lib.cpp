#include <bits/stdc++.h>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
using ll = long long;
// 2^60
#define INF (1LL << 60)
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on

/* 幾何ライブラリ */
using DD = double;
// この値より小さければ等しいとみなす
const DD EPS = 1e-10;  // to be set appropriately
const DD PI = M_PI;
DD torad(int deg) {
    return (DD)(deg)*PI / 180;
}
DD todeg(DD ang) {
    return ang * 180 / PI;
}

/* Point */
struct Point {
    DD x, y;
    Point(DD x = 0.0, DD y = 0.0) : x(x), y(y) {
    }
    friend ostream &operator<<(ostream &s, const Point &p) {
        return s << '(' << p.x << ", " << p.y << ')';
    }
};

Point operator+(const Point &p, const Point &q) {
    return Point(p.x + q.x, p.y + q.y);
}
Point operator-(const Point &p, const Point &q) {
    return Point(p.x - q.x, p.y - q.y);
}
Point operator*(const Point &p, DD a) {
    return Point(p.x * a, p.y * a);
}
Point operator*(DD a, const Point &p) {
    return Point(a * p.x, a * p.y);
}
Point operator/(const Point &p, DD a) {
    return Point(p.x / a, p.y / a);
}

// https://eman-physics.net/math/imaginary01.html
// 複素数同士の掛け算は複素数平面で考えるとわかりやすい
// 掛け算は元の数値にその絶対値を掛け,その偏角の分だけ元の数値を複素平面上で回転させるという意味を持つ
Point operator*(const Point &p, const Point &q) {
    return Point(p.x * q.x - p.y * q.y, p.x * q.y + p.y * q.x);
}
// 複素数平面だと共役な複素数
Point conj(const Point &p) {
    return Point(p.x, -p.y);
}
Point rot(const Point &p, DD ang) {
    return Point(cos(ang) * p.x - sin(ang) * p.y, sin(ang) * p.x + cos(ang) * p.y);
}
Point rot90(const Point &p) {
    return Point(-p.y, p.x);
}

// 外積
// 外積は正確には3次元以上で定義されるが、z座標が0とみなす。結果はx座標、y座標が0でz座標の値がこの関数の結果となる
// ネジの方向は角度が小さい方向で測る
// 絶対値はベクトルで作る平行四辺形の面積
// 0なら平行
DD cross(const Point &p, const Point &q) {
    return p.x * q.y - p.y * q.x;
}
// 内積
// 0なら直角
DD dot(const Point &p, const Point &q) {
    return p.x * q.x + p.y * q.y;
}
DD norm(const Point &p) {
    return dot(p, p);
}
// ベクトルの長さ
DD abs(const Point &p) {
    return sqrt(dot(p, p));
}
// ベクトルの角度
DD amp(const Point &p) {
    DD res = atan2(p.y, p.x);
    if (res < 0)
        res += PI * 2;
    return res;
}
bool eq(const Point &p, const Point &q) {
    return abs(p - q) < EPS;
}

// 以下3つは謎
bool operator<(const Point &p, const Point &q) {
    return (abs(p.x - q.x) > EPS ? p.x < q.x : p.y < q.y);
}
bool operator>(const Point &p, const Point &q) {
    return (abs(p.x - q.x) > EPS ? p.x > q.x : p.y > q.y);
}
Point operator/(const Point &p, const Point &q) {
    return p * conj(q) / norm(q);
}

/* Line */
struct Line : vector<Point> {
    Line(Point a = Point(0.0, 0.0), Point b = Point(0.0, 0.0)) {
        this->push_back(a);
        this->push_back(b);
    }
    friend ostream &operator<<(ostream &s, const Line &l) {
        return s << '{' << l[0] << ", " << l[1] << '}';
    }
};

// 1：b-aから見てc-aは左側(反時計回り)、-1：b-aから見てc-aは右側(時計回り)、0：一直線上
int simple_ccw(const Point &a, const Point &b, const Point &c) {
    if (cross(b - a, c - a) > EPS)
        return 1;
    if (cross(b - a, c - a) < -EPS)
        return -1;
    return 0;
}

// 点が線分にあるかないか
bool is_point_on_line(const Line &l, const Point &a) {
    return simple_ccw(l[0], l[1], a) == 0 && dot(l[1] - l[0], a - l[0]) > -EPS && dot(l[0] - l[1], a - l[1]) > -EPS;
}

// 直線と点との距離
// http://www.deqnotes.net/acmicpc/2d_geometry/lines を見て実装。未テスト
DD distance(const Line &l, const Point &a) {
    const Point x = l[1] - l[0];
    const Point y = a - l[0];
    return abs(cross(x, y)) / abs(x);
}

// 線分と点の距離
DD distance_ls_p(const Line &l, const Point &a) {
    if (dot(l[1] - l[0], a - l[0]) < EPS) {
        return abs(a - l[0]);
    }
    if (dot(l[0] - l[1], a - l[1]) < EPS) {
        return abs(a - l[1]);
    }
    return distance(l, a);
}

// 線分の交差判定
bool is_intersected_ls(const Line &l1, const Line &l2) {
    return simple_ccw(l1[0], l1[1], l2[0]) * simple_ccw(l1[0], l1[1], l2[1]) &&
           simple_ccw(l2[0], l2[1], l1[0]) * simple_ccw(l2[0], l2[1], l1[1]);
}

// 線分の交点
// 線分の交差判定がされている前提である
Point intersection_ls(const Line &l1, const Line &l2) {
    double d1 = distance(l2, l1[0]);
    double d2 = distance(l2, l1[1]);
    double t = d1 / (d1 + d2);
    return l1[0] + t * (l1[1] - l1[0]);
}

// 二つの直線の交点を求める
// 線分ではないことに注意。そのため、平行でなければ必ず交点がある
// 平行の場合は空を返す
vector<Point> crosspoint(const Line &l, const Line &m) {
    vector<Point> res;
    DD d = cross(m[1] - m[0], l[1] - l[0]);
    if (abs(d) < EPS)
        return vector<Point>();
    res.push_back(l[0] + (l[1] - l[0]) * cross(m[1] - m[0], m[1] - l[0]) / d);
    return res;
}

// 外心
Point gaisin(Point a, Point b, Point c) {
    Line ab((a + b) / 2, (a + b) / 2 + rot90(a - b));
    Line bc((b + c) / 2, (b + c) / 2 + rot90(b - c));
    return crosspoint(ab, bc)[0];
}

// 凸包
// p.234
// 直線上に点が並んでいる場合も考慮している
vector<Point> convex_hull(const vector<Point> &ps) {
    int n = ps.size();
    sort(ps.begin(), ps.end(), [](const Point &a, const Point &b) -> bool {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y;
    });

    int k = 0;
    // 構築中の凸包
    vector<Point> qs(n * 2);
    // 下側
    rep(i, 0, n) {
        while (k > 1 && cross((qs[k - 1] - qs[k - 2]), (ps[i] - qs[k - 1])) >= -EPS)
            k--;
        qs[k++] = ps[i];
    }
    // 上側
    for (int i = n - 2, t = k; i >= 0; --i) {
        while (k > t && cross((qs[k - 1] - qs[k - 2]), (ps[i] - qs[k - 1])) >= -EPS)
            k--;
        qs[k++] = ps[i];
    }
    // 最初と最後が重複しているので除く
    // 上側のloopをi>0としてしまうと、直線上にあったときに１つ余分に含まれてしまうと思われる
    qs.resize(k - 1);
    return qs;
}
