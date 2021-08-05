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

    bool unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y])
            swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
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

    vector<long long> ret;
    UnionFind uf(N);
    int cnt = 0;
    for (int j = M - 1; j >= 1; --j)
    {
        vector<int> v;
        uf.unite(e[j].first, e[j].second);
        long long total = 0;
        for (int x = 0; x < N; ++x)
        {
            if (uf.root(x) == x)
            {
                v.push_back(uf.size(x));
            }
        }
        for (int i = 0; i < v.size(); ++i)
        {
            for (int j = i + 1; j < v.size(); ++j)
            {
                total += v[i] * v[j];
            }
        }
        ret.push_back(total);
    }
    for (int j = M - 2; j >= 0; --j)
    {
        cout << ret[j] << endl;
    }
    cout << N * (N - 1) / 2 << endl;
}