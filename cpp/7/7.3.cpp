#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Task = pair<int, int>;

bool cmp(const Task &a, const Task &b)
{
    return a.second < b.second;
}

int main()
{
    int N;
    cin >> N;
    vector<Task> a(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end(), cmp);

    int t = 0;
    bool ret = true;

    for (int i = 0; i < N; ++i)
    {
        if (t + a[i].first > a[i].second)
        {
            ret = false;
            break;
        }
        t += a[i].first;
    }
    if (ret)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}