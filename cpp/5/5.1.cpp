#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<vector<int> > a(N, vector<int>(3, 0));
    vector<vector<int> > s((N + 1), vector<int>(3, 0));

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i][0];
        cin >> a[i][1];
        cin >> a[i][2];
    }

    s[0][0] = 0;
    s[0][1] = 0;
    s[0][2] = 0;

    for (int i = 1; i < N + 1; i++)
    {
        if (s[i - 1][1] < s[i - 1][2])
        {
            s[i][0] = s[i - 1][2] + a[i - 1][0];
        }
        else
        {
            s[i][0] = s[i - 1][1] + a[i - 1][0];
        }
        if (s[i - 1][0] < s[i - 1][2])
        {
            s[i][1] = s[i - 1][2] + a[i - 1][1];
        }
        else
        {
            s[i][1] = s[i - 1][0] + a[i - 1][1];
        }
        if (s[i - 1][0] < s[i - 1][1])
        {
            s[i][2] = s[i - 1][1] + a[i - 1][2];
        }
        else
        {
            s[i][2] = s[i - 1][0] + a[i - 1][2];
        }
    }

    int ret = 0;
    if (s[N][0] < s[N][1])
    {
        ret = s[N][1];
    }
    else
    {
        ret = s[N][0];
    }
    if (ret < s[N][2])
    {
        ret = s[N][2];
    }
    cout << ret << endl;
}