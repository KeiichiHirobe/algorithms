#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
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

using point = pair<int, int>;

vector<vector<int>> short_path(const vector<vector<int>> &v, point s)
{
    vector<vector<int>> dist(v.size(), vector<int>(v[0].size(), -1));
    queue<point> que;

    dist[s.first][s.second] = 0;
    que.push(s);

    while (!que.empty())
    {
        point p = que.front();
        que.pop();

        rep(i, 4)
        {
            point t = {p.first + dx[i], p.second + dy[i]};
            if (0 <= t.first && t.first < v.size() && 0 <= t.second && t.second < v[0].size() && v[t.first][t.second] != -1)
            {
                if (dist[t.first][t.second] != -1)
                {
                    continue;
                }
                dist[t.first][t.second] = 1 + dist[p.first][p.second];
                que.push(t);
            }
        }
    }
    return dist;
}

int main()
{
    int n;
    int m;
    // 1-9
    int f;
    cin >> n;
    cin >> m;
    cin >> f;

    vector<vector<int>> v(n, vector<int>(m, 0));

    vector<point> vnum(10, {-1, -1});
    int vlen = 1;

    rep(i, n)
    {
        string s;
        cin >> s;
        rep(j, m)
        {
            auto c = s[j];
            if (c == 'X')
            {
                v[i][j] = -1;
            }
            else if (c == 'S')
            {
                vnum[0] = {i, j};
            }
            else if (c == '.')
            {
                //
            }
            else
            {
                ++vlen;
                vnum[c - '0'] = {i, j};
            }
        }
    }

    vector<vector<int>> d(vlen, vector<int>(vlen, -1));
    rep(i, vlen)
    {
        auto ret = short_path(v, vnum[i]);
        rep(j, vlen)
        {
            d[i][j] = ret[vnum[j].first][vnum[j].second];
        }
    }
    ll mind = INF;
    vector<int> tper(vlen - 1, 0);
    rep(i, vlen - 1)
    {
        tper[i] = i + 1;
    }

    int total = 0;
    rep(i, tper.size())
    {
        if (i == 0)
        {
            total += d[0][tper[i]];
        }
        else
        {
            total += d[tper[i - 1]][tper[i]];
        }
    }
    if (total < mind)
    {
        mind = total;
    }

    /*
    do
    {
        int total = 0;
        rep(i, tper.size())
        {
            if (i == 0)
            {
                total += d[0][tper[i]];
            }
            else
            {
                total += d[tper[i - 1]][tper[i]];
            }
        }
        if (total < mind)
        {
            mind = total;
        }
    } while (next_permutation(tper.begin(), tper.end()));
  */
    cout << mind << endl;
}