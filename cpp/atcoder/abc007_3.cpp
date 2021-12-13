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
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;

using Graph = vector<vector<int>>;

// 入力: グラフ G と，探索の始点 s
// 出力: s から各頂点への最短路長を表す配列
vector<vector<int>> BFS(const vector<vector<int>> &v, int sx, int sy) {
    vector<vector<int>> dist(v.size(), vector<int>(v[0].size(),-1)); // 全頂点を「未訪問」に初期化
    queue<pair<int,int>> que;

    // 初期条件 (頂点 s を初期頂点とする)
    dist[sx][sy] = 0;
    que.push({sx,sy}); // s を橙色頂点にする

    // BFS 開始 (キューが空になるまで探索を行う)
    while (!que.empty()) {
        auto node = que.front(); // キューから先頭頂点を取り出す
        que.pop();

        int x = node.first;
        int y = node.second;

        rep(i,4) {
            int nx; 
            int ny;
            nx = x + dx[i];
            ny = y + dy[i];

            if (0<=nx && nx < SZ(v)&& 0<=ny && ny< SZ(v[0]) ) {

                if (v[nx][ny] == 1) {

                    continue;
                }
                if (dist[nx][ny] != -1) {
                    continue;
                }
                dist[nx][ny] = dist[x][y] + 1;
                que.push({nx,ny});
            }
        }
    }
    return dist;
}

// clang-format on

int main()
{
    int N;
    int M;
    cin >> N;
    cin >> M;

    vector<vector<int>> v(N, vector<int>(M, 0));

    int sx;
    int sy;
    int gx;
    int gy;

    cin >> sx;
    cin >> sy;
    cin >> gx;
    cin >> gy;
    --sx;
    --sy;
    --gx;
    --gy;

    rep(i, N)
    {
        string s;
        cin >> s;
        rep(j, M)
        {
            if (s[j] == '#')
            {
                v[i][j] = 1;
            }
        }
    }

    auto dist = BFS(v, sx, sy);

    cout << dist[gx][gy] << endl;
}