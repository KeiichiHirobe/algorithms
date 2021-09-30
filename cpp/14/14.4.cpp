#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// 四方向への移動ベクトル
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// 入力
int H, W;
vector<string> field;

// 探索
vector<vector<int>> dist(510, vector<int>(510, -1));

void dfs(int h, int w)
{

    // 四方向を探索
    for (int dir = 0; dir < 4; ++dir)
    {
        int nh = h + dx[dir];
        int nw = w + dy[dir];

        // 場外アウトしたり、移動先が壁の場合はスルー
        if (nh < 0 || nh >= H || nw < 0 || nw >= W)
            continue;
        if (field[nh][nw] == '#')
        {
            if ((dist[nh][nw] > dist[h][w] + 1 || dist[nh][nw] == -1) && dist[h][w] + 1 <= 2)
            {
                dist[nh][nw] = dist[h][w] + 1;
            }
            else
            {
                continue;
            }
        }
        else
        {
            if ((dist[nh][nw] > dist[h][w] || dist[nh][nw] == -1) && dist[h][w] <= 2)
            {
                dist[nh][nw] = dist[h][w];
            }
            else
            {
                continue;
            }
        }

        // 再帰的に探索
        dfs(nh, nw);
    }
}

int main()
{
    // 入力受け取り
    cin >> H >> W;
    field.resize(H);
    for (int h = 0; h < H; ++h)
        cin >> field[h];

    // s と g のマスを特定する
    int sh, sw, gh, gw;
    for (int h = 0; h < H; ++h)
    {
        for (int w = 0; w < W; ++w)
        {
            if (field[h][w] == 's')
                sh = h, sw = w;
            if (field[h][w] == 'g')
                gh = h, gw = w;
        }
    }

    dist[sh][sw] = 0;

    // 探索開始
    dfs(sh, sw);

    // 結果
    if (dist[gh][gw] <= 2 && dist[gh][gw] != -1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}