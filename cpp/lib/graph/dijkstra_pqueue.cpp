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

// �դ�ɽ�����������ǤϽŤߤ�ɽ������ long long ���Ȥ��ޤ�
struct Edge
{
    int to;      // ����ĺ���ֹ�
    long long w; // �Ť�
    Edge(int to, long long w) : to(to), w(w) {}
};

// �Ť��դ�����դ�ɽ����
using Graph = vector<vector<Edge>>;

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

    // ���������ȥ�ˡ
    vector<long long> dist(N, INF);
    dist[s] = 0;

    // (d[v], v) �Υڥ������ǤȤ����ҡ��פ���
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        que;
    que.push(make_pair(dist[s], s));

    // ���������ȥ�ˡ��ȿ���򳫻�
    while (!que.empty())
    {
        // v: ���ѺѤߤǤʤ�ĺ���Τ��� d[v] ���Ǿ���ĺ��
        // d: v ���Ф��륭����
        int v = que.top().second;
        long long d = que.top().first;
        que.pop();

        // d > dist[v] �ϡ�(d, v) �����ߤǤ��뤳�Ȥ��̣����
        if (d > dist[v])
            continue;

        // ĺ�� v ������Ȥ������դ����
        for (auto e : G[v])
        {
            if (chmin(dist[e.to], dist[v] + e.w))
            {
                // ����������ʤ�ҡ��פ˿���������
                que.push(make_pair(dist[e.to], e.to));
            }
        }
    }

    // ��̽���
    for (int v = 0; v < N; ++v)
    {
        if (dist[v] < INF)
            cout << dist[v] << endl;
        else
            cout << "INF" << endl;
    }
}
