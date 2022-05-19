#include <iostream>
#include <vector>
using namespace std;

template <class T>
void chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
    }
}

// ナップサック問題
int main()
{
    int N;
    long long W;
    cin >> N >> W;
    vector<long long> weight(N), value(N);
    for (int i = 0; i < N; ++i)
        cin >> weight[i] >> value[i];

    // dp[i][w] = 最初のi個の品物{0,1,..i-1}までの中から重さがwを超えないように選んだ時の価値の最大値
    vector<vector<long long>> dp(N + 1, vector<long long>(W + 1, 0));

    for (int i = 0; i < N; ++i)
    {
        for (int w = 0; w <= W; ++w)
        {
            if (w - weight[i] >= 0)
            {
                chmax(dp[i + 1][w], dp[i][w - weight[i]] + value[i]);
            }
            chmax(dp[i + 1][w], dp[i][w]);
        }
    }

    // 最適値の出力
    cout << dp[N][W] << endl;
}

// 個数制限なし部分和問題
int main() {
    // 入力
    int N, W;
    cin >> N >> W;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // 最初のi個の整数のみを用いて、重複ありを許して総和をとった値をjにすることが可能かどうか
    vector<vector<bool>> dp(N+1, vector<bool>(W+1, false));

    // 初期条件
    dp[0][0] = true;

    // ループ
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (dp[i][j]) dp[i+1][j] = true;
            // 個数制限1の場合、以下がdp[i][j-a[i]] になる
            if (j >= a[i] && dp[i+1][j-a[i]]) dp[i+1][j] = true;
        }
    }

    // 答え
    if (dp[N][W]) cout << "Yes" << endl;
    else cout << "No" << endl;
}