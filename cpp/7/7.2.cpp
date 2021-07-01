#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Point = pair<int, int>;

bool cmpB(const Point &a, const Point &b)
{
    return a.first < b.first;
}
bool cmpA(const Point &a, const Point &b)
{
    return a.second > b.second;
}

int main()
{
    int N;
    cin >> N;
    vector<Point> a(N);
    vector<Point> b(N);
    vector<bool> used(N, false);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> b[i].first >> b[i].second;
    }

    sort(a.begin(), a.end(), cmpA);
    sort(b.begin(), b.end(), cmpB);

    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (a[j].first < b[i].first && a[j].second < b[i].second && used[j] == false)
            {
                ++res;
                used[j] = true;
                break;
            }
        }
    }
    cout << res << endl;
}