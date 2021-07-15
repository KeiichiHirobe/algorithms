#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    string str;
    cin >> str;
    stack<int> s;

    bool ok = true;

    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == '(')
        {
            s.push(i);
        }
        else if (str[i] == ')')
        {
            if (s.empty())
            {
                ok = false;
                break;
            }
            int idx = s.top();
            s.pop();
            cout << "(" << idx + 1 << "," << i + 1 << ")" << endl;
        }
    }

    if (!ok || !s.empty())
    {
        cout << "NG" << endl;
    }
    else
    {
        cout << "OK" << endl;
    }
}