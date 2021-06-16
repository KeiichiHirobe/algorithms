#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    for (int i = 0; i < N; ++i)
    {
        cout << lower_bound(b.begin(), b.end(), a[i]) - b.begin() << endl;
    }
}