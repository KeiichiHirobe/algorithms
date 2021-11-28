#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int count(int n, int x)
{
    return 1;
}
int main()
{
    int n;
    int x;

    while (true)
    {
        cin >> n;
        cin >> x;
        if (n == 0 && x == 0)
            break;
        cout << count(n, x) << endl;
    }
}