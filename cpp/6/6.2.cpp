#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N, 0);
    vector<int> b(N, 0);
    vector<int> c(N, 0);
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int i = 0; i < N; ++i)
        cin >> b[i];
    for (int i = 0; i < N; ++i)
        cin >> c[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    long long total = 0;
    for (int i = 0; i < N; ++i)
    {
        auto citr = upper_bound(c.begin(), c.end(), b[i]);
        long long ccnt = c.end() - citr;

        auto aitr = lower_bound(a.begin(), a.end(), b[i]);
        long long acnt = aitr - a.begin();
        total += ccnt * acnt;
    }
    cout << total << endl;
}