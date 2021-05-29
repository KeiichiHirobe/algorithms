#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    int cnt = 0;
    bool ok = true;
    cin >> N;
    vector<int> a(N);

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (; ok;)

    {
        for (int i = 0; i < N; ++i)
        {
            if (a[i] % 2 == 0)
            {
                a[i] = a[i] / 2;
            }
            else
            {
                ok = false;

                break;
            }
        }
        if (ok)
        {
            ++cnt;
        }
    }

    cout << cnt << endl;
}