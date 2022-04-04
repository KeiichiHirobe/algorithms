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

// �դ�ɽ�����������ǤϽŤߤ�ɽ������ long long ���Ȥ���
struct Edge
{
    int to;      // ����ĺ���ֹ�
    long long w; // �Ť�
    Edge(int to, long long w) : to(to), w(w) {}
};

// �Ť��դ�����դ�ɽ����
using Graph = vector<vector<Edge>>;

// ����ϩ�θ��Ф�Ԥ����������ޤǻ���s������ã��ǽ������ϩ�ΤߤǤ��뤳�Ȥ���դ���
int main()
{
    // ĺ�������տ�������
    int N, M, s;
    cin >> N >> M >> s;

    // �����
    Graph G(N);
    for (int i = 0; i < M; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        G[a].push_back(Edge(b, w));
    }

    // �٥�ޥ󡦥ե�����ˡ
    bool exist_negative_cycle = false; // ����ϩ���Ĥ��ɤ���
    vector<long long> dist(N, INF);
    dist[s] = 0;
    for (int iter = 0; iter < N; ++iter)
    {
        bool update = false; // ������ȯ���������ɤ�����ɽ���ե饰
        for (int v = 0; v < N; ++v)
        {
            // dist[v] = INF �ΤȤ���ĺ�� v ����δ��¤�Ԥ�ʤ�
            if (dist[v] == INF)
                continue;

            for (auto e : G[v])
            {
                // ���½�����Ԥ����������줿�� update �� true �ˤ���
                if (chmin(dist[e.to], dist[v] + e.w))
                {
                    update = true;
                }
            }
        }

        // �������Ԥ��ʤ��ä��顤���Ǥ˺�ûϩ�������Ƥ���
        if (!update)
            break;

        // N ���ܤ�ȿ���ǹ������Ԥ�줿�ʤ�С�����ϩ����
        if (iter == N - 1 && update)
            exist_negative_cycle = true;
    }

    // ��̽���
    if (exist_negative_cycle)
        cout << "NEGATIVE CYCLE" << endl;
    else
    {
        for (int v = 0; v < N; ++v)
        {
            if (dist[v] < INF)
                cout << dist[v] << endl;
            else
                cout << "INF" << endl;
        }
    }
}
