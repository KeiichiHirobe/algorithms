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
    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int res = 0;

    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        for (; j < N; ++j)
        {
            if (a[i] < b[j])
            {
                ++res;
                ++j;
                break;
            }
        }
    }
    cout << res << endl;
}