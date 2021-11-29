#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
//ACGT
bool ok(char c)
{
    return c == 'A' || c == 'C' || c == 'G' || c == 'T';
}

int count(string s)
{
    int max = 0;

    int n = int(s.length());

    for (int i = 0; i < n; i++)
    {
        int t = 0;
        for (int j = i; j < n; j++)
        {
            if (ok(s[j]))
            {
                ++t;
            }
            else
            {
                break;
            }
        }
        if (max < t)
        {
            max = t;
        }
    }
    return max;
}

int main()
{
    string s;
    cin >> s;
    cout << count(s) << endl;
}