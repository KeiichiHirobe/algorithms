#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using Graph = vector<vector<int>>;

// 入力
int N;               // 頂点数
vector<long long> w; // 各頂点の重み
Graph G;             // グラフ

// 木上の動的計画法テーブル
vector<bool> used;

int dfs(int v, int p = -1)
{
    int cnt = 0;
    int usedCnt = 0;
    // 最初に各子頂点を探索しておきます
    for (auto ch : G[v])
    {
        if (ch == p)
            continue;
        cnt += dfs(ch, v);
        if (used[ch])
        {
            ++usedCnt;
        }
    }
    if (usedCnt == 0)
    {
        ++cnt;
        used[v] = true;
    }
    return cnt;
}

int main()
{
    // 頂点数 (木なので辺数は N - 1 で確定)
    cin >> N;

    // 重みとグラフの入力受取
    w.resize(N);
    for (int i = 0; i < N; ++i)
        w[i] = 1;
    G.clear();
    G.resize(N);
    for (int i = 0; i < N - 1; ++i)
    {
        int a, b; // 葉
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // 探索
    int root = 0; // 仮に頂点 0 を根とする
    used.assign(N, false);
    dfs(root);

    // 結果
    cout << dfs(root) << endl;
}
