#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int K;
    int N;
    int cnt = 0;
    cin >> K >> N;
    for (int i = 0; i <= K; ++i)
    {
        for (int j = 0; j <= K; ++j)
        {
            int k = N - (i + j);
            if (k <= K && k >= 0)
            {
                ++cnt;
            }
        }
    }
    cout << cnt << endl;
}