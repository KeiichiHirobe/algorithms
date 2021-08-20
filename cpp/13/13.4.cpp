#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
using Graph = vector<vector<int>>;

int main()
{
    int L, H;
    cin >> L >> H;
    // S,G,.,#
    vector<vector<int>> m(L, vector<int>(H));
    vector<vector<int>> d(L, vector<int>(H, -1));
    int sx, sy, gx, gy;

    string t;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < H; j++)
        {
            cin >> t;
            if (t == "S")
            {
                m[i][j] = 0;
                sx = i;
                sy = j;
            }
            else if (t == "G")
            {
                m[i][j] = 1;
                gx = i;
                gy = j;
            }
            else if (t == ".")
            {
                m[i][j] = 2;
            }
            else if (t == "#")
            {
                m[i][j] = 3;
            }
        }
    }

    queue<pair<int, int>> que;

    que.push(make_pair(sx, sy));
    d[sx][sy] = 0;

    vector<int> dx = {-1, 0, 1, 0};
    vector<int> dy = {0, 1, 0, -1};

    while (!que.empty())
    {
        pair<int, int> v = que.front();
        que.pop();
        for (int i = 0; i < dx.size(); ++i)
        {
            int ni = v.first + dx[i];
            int nj = v.second + dy[i];
            if (0 <= ni && ni < L && 0 <= nj && nj < H && d[ni][nj] == -1 && m[ni][nj] != 3)
            {
                d[ni][nj] = d[v.first][v.second] + 1;
                que.push(make_pair(ni, nj));
            }
        }
    }
    cout << d[gx][gy] << endl;
}