#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <class T>
void chmax(T &a, const T &b)
{
    if (a < b)
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
    string S, T;
    cin >> S >> T;
    vector<vector<int> > dp(S.size() + 1, vector<int>(T.size() + 1, 0));
    for (unsigned int i = 0; i < S.size(); ++i)
    {
        for (unsigned int j = 0; j < T.size(); ++j)
        {
            if (S[i] == T[j])
            {
                chmax(dp[i + 1][j + 1], dp[i][j] + 1);
            }
            else
            {
                chmax(dp[i + 1][j + 1], dp[i][j + 1]);
                chmax(dp[i + 1][j + 1], dp[i + 1][j]);
            }
        }
    }
    string ret = "";
    int i = int(S.size());
    int j = int(T.size());
    // print(dp);
    for (;;)
    {
        if (i == 0 || j == 0)
        {
            break;
        }
        // dp[i - 1][j - 1] + 1 ==  dp[i][j]) のときに当てはまるとは限らないことに注意
        if (S[i - 1] == T[j - 1])
        {
            ret += S[i - 1];
            --i;
            --j;
        }
        else if (dp[i - 1][j] < dp[i][j - 1])
        {
            --j;
        }
        else
        {
            --i;
        }
    }

    reverse(ret.begin(), ret.end());

    cout << ret << endl;
}