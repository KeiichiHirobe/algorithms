#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
// clang-format off
#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// 2^60
const ll INF = 1LL << 60;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
// clang-format on

int main()
{
    // ĺ�������տ�
    int N, M;
    cin >> N >> M;

    // dp ���� (INF �ǽ�������ޤ�)
    vector<vector<long long>> dp(N, vector<long long>(N, INF));

    // dp ������
    for (int e = 0; e < M; ++e)
    {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        dp[a][b] = w;
    }
    for (int v = 0; v < N; ++v)
        dp[v][v] = 0;

    // dp ���� (�ե��ɡ�������ˡ)
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    // ��̽���
    // �⤷ dp[v][v] < 0 �ʤ�����ϩ��¸�ߤ���
    bool exist_negative_cycle = false;
    for (int v = 0; v < N; ++v)
    {
        if (dp[v][v] < 0)
            exist_negative_cycle = true;
    }
    if (exist_negative_cycle)
    {
        cout << "NEGATIVE CYCLE" << endl;
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (j)
                    cout << " ";
                // �����餯��é��ʤ��Τ�����դˤ�꾮�����ʤäƤ����������
                if (dp[i][j] < INF / 2)
                    cout << dp[i][j];
                else
                    cout << "INF";
            }
            cout << endl;
        }
    }
}
