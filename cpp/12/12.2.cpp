#include <iostream>
#include <vector>
using namespace std;

struct Store
{
    int price;
    int num;
};

int main()
{
    int N, M;
    cin >> N >> M;

    vector<Store> a(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i].price >> a[i].num;
    }

    sort(a.begin(), a.end(), [](const Store &a, const Store &b)
         { return a.price < b.price; });

    long long total = 0;
    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        if (cnt >= M)
            break;

        int incl = min(M - cnt, a[i].num);
        cnt += incl;
        total += 1LL * incl * a[i].price;
    }

    cout << total << endl;
}