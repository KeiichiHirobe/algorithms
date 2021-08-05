#include <iostream>
#include <vector>
using namespace std;

struct UnionFind
{
    vector<int> par, siz;
    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    int root(int x)
    {
        if (par[x] == -1)
            return x;
        else
            return par[x] = root(par[x]);
    }

    bool issame(int x, int y)
    {
        return root(x) == root(y);
    }

    // bool: 新たに連結されたか
    // pair: bool=trueのときのみ意味があり、mergeされる前のそろぞれの要素数
    pair<bool, pair<int, int> > unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x == y)
            return make_pair(false, make_pair(0, 0));
        if (siz[x] < siz[y])
            swap(x, y);
        int size_x = siz[x];
        int size_y = siz[y];
        par[y] = x;
        siz[x] += size_y;
        return make_pair(true, make_pair(size_x, size_y));
    }

    int size(int x)
    {
        return siz[root(x)];
    }
};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<pair<int, int> > e(M);

    int x;
    int y;
    for (int i = 0; i < M; ++i)
    {
        cin >> x >> y;
        e[i] = pair<int, int>(x - 1, y - 1);
    }

    vector<long long> ret(M);
    UnionFind uf(N);
    long long cnt = static_cast<long long>(N) * static_cast<long long>(N - 1) / 2;
    ret[M - 1] = cnt;
    for (int j = M - 1; j >= 1; --j)
    {
        pair<bool, pair<int, int> > united = uf.unite(e[j].first, e[j].second);
        if (united.first == false)
        {
            ret[j - 1] = cnt;
        }
        else
        {
            cnt -= static_cast<long long>(united.second.first) * static_cast<long long>(united.second.second);
            ret[j - 1] = cnt;
        }
    }
    for (int i = 0; i < M; i++)
    {
        cout << ret[i] << endl;
    }
}