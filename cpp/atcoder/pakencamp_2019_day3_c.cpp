#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int main()
{
    int n;
    int m;
    cin >> n;
    cin >> m;

    vector<vector<long long>> v(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }

    long long max = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            long long sum = 0;
            for (int k = 0; k < n; k++)
            {
                long long p = v[k][i];
                if (v[k][i] < v[k][j])
                {
                    p = v[k][j];
                }
                sum += p;
            }
            if (max < sum)
            {
                max = sum;
            }
        }
    }
    cout << max << endl;
}