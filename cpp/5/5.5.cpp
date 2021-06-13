#include <iostream>
#include <vector>
using namespace std;

template <class T>
void chmin(T &a, const T &b)
{
    if (a > b)
    {
        a = b;
    }
}

void print(const vector<vector<int> > &dp)
{
    for (unsigned int i = 0; i < dp.size(); ++i)
    {
        for (unsigned int j = 0; j < dp[i].size(); ++j)
        {
            cout << dp[i][j] << ",";
        }
        cout << endl;
    }
}

int main()
{
    int N, W, K;
    cin >> N >> W >> K;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
        cin >> a[i];

    vector<vector<int> > dp((1 + N), vector<int>(W + 1, INT_MAX));

    dp[0][0] = 0;
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 0; j < W + 1; ++j)
        {
            if (dp[i - 1][j] != INT_MAX)
            {
                chmin(dp[i][j], dp[i - 1][j]);
                // over O(NW)
                // https://github.com/drken1215/book_algorithm_solution/blob/master/solutions/chap05.md#55-%E5%80%8B%E6%95%B0%E5%88%B6%E9%99%90%E3%81%AA%E3%81%97%E9%83%A8%E5%88%86%E5%92%8C%E5%95%8F%E9%A1%8Cv
                for (int k = 1; j + a[i - 1] * k < W + 1; k++)
                {
                    chmin(dp[i][j + a[i - 1] * k], dp[i][j] + k);
                }
            }
        }
    }

    print(dp);
    if (dp[N][W] != INT_MAX)
    {
        if (dp[N][W] <= K)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "NG" << endl;
        }
    }
    else
    {
        cout << "NG" << endl;
    }
}