#include <iostream>
#include <vector>
using namespace std;

// Union-Find
struct UnionFind
{
    vector<int> par, siz;

    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    // 根を求める
    int root(int x)
    {
        if (par[x] == -1)
            return x;
        else
            return par[x] = root(par[x]);
    }

    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y)
    {
        return root(x) == root(y);
    }

    // x を含むグループと y を含むグループとを併合する
    bool unite(int x, int y)
    {
        x = root(x), y = root(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y])
            swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    // グループを返却する
    vector<vector<int>> groups()
    {
        vector<vector<int>> g(par.size());
        for (int i = 0; i < par.size(); ++i)
        {
            g[root(i)].push_back(i);
        }
        auto result = std::remove_if(g.begin(), g.end(), [](auto &x)
                                     { return x.empty(); } );
        g.erase(result, g.end());
        return g;
    }

    // x を含むグループのサイズ
    int size(int x)
    {
        return siz[root(x)];
    }
};