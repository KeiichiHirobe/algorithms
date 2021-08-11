#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> a(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }

    priority_queue<int> q;
    for (int i = 0; i < K; ++i)
    {
        q.push(a[i]);
    }
    cout << q.top() << endl;
    for (int i = K; i < N; ++i)
    {
        int max = q.top();
        if (a[i] < max)
        {
            q.pop();
            q.push(a[i]);
        }
        cout << q.top() << endl;
    }
}