#include <iostream>
#include <vector>
using namespace std;

template <class T>
void chmax(T &a, T &b)
{
    if (a.length() < b.length())
    {
        a = b;
    }
}

int main()
{
    string S, T;
    cin >> S >> T;
    vector<vector<string> > dp(S.size() + 1, vector<string>(T.size() + 1, ""));
    for (unsigned int i = 0; i < S.size(); ++i)
    {
        for (unsigned int j = 0; j < T.size(); ++j)
        {
            if (S[i] == T[j])
            {
                string concated = dp[i][j] + S[i];
                chmax(dp[i + 1][j + 1], concated);
            }
            else
            {
                chmax(dp[i + 1][j + 1], dp[i][j + 1]);
                chmax(dp[i + 1][j + 1], dp[i + 1][j]);
            }
        }
    }
    cout << dp[S.size()][T.size()] << endl;
}