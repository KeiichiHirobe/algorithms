#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int inf = INT_MAX / 2;
const ll infl = 1LL << 60;
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}

int N, L, P;

// a 距離
// b ガゾリン
// posの時点でneed以上必要な場合に可能な最低補給回数
int mover(int pos, int need, const vector<int> &a, const vector<int> &b)
{
    if (pos == 0)
    {
        if (need > P - a[pos] + b[pos])
        {
            return inf;
        }
        else if (need > P - a[pos])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int use = mover(pos - 1, need + (a[pos] - a[pos - 1]) - b[pos], a, b) + 1;
    int not_use = mover(pos - 1, need + (a[pos] - a[pos - 1]), a, b);
    return min(use, not_use);
}

int main()
{
    cin >> N >> L >> P;

    vector<int> a(N);
    vector<int> b(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> b[i];
    }
    int ret = mover(N - 1, L - a[N - 1], a, b);
    if (ret >= inf)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ret << endl;
    }
}
