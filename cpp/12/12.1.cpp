#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    int target_idx;
    cin >> N;

    vector<int> v(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> v[i];
    }
    cin >> target_idx;
    int target = v[target_idx];

    sort(v.begin(), v.end());

    int cnt = 0;

    auto itr = lower_bound(v.begin(), v.end(), target);
    cout << itr - v.begin() + 1 << endl;
}