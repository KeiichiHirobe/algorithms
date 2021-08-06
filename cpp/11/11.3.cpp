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
    int N, K, L;
    cin >> N >> K >> L;

    vector<pair<int, int> > k(K);
    vector<pair<int, int> > l(L);
    UnionFind ufk(N);
    UnionFind ufl(N);
    int x;
    int y;
    for (int i = 0; i < K; ++i)
    {
        cin >> x >> y;
        --x;
        --y;
        ufk.unite(x, y);
    }
    for (int i = 0; i < L; ++i)
    {
        cin >> x >> y;
        --x;
        --y;
        ufl.unite(x, y);
    }

    vector<int> ret(N, 0);
    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < N; ++j)
        {
            if (i != j)
            {
                if (ufk.issame(i, j) && ufl.issame(i, j))
                {
                    ret[i] += 1;
                    ret[j] += 1;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << ret[i] + 1 << endl;
    }
}