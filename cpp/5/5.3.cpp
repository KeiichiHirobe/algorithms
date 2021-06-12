#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int cnt = 0;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
        cin >> a[i];

    vector<vector<bool> > dp(1 + N, vector<bool>(10000, false));

    dp[0][0] = true;
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 0; j < 10000; ++j)
        {
            if (dp[i - 1][j])
            {
                dp[i][j] = true;
                dp[i][j + a[i - 1]] = true;
            }
        }
    }
    for (int j = 0; j < 10000; ++j)
    {
        if (dp[N][j])
        {
            ++cnt;
        }
    }
    cout << cnt << endl;
}