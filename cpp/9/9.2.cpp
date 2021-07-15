#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    int N;
    cin >> N;
    stack<string> s;
    vector<string> a(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }

    for (int i = 0; i < N; ++i)
    {
        string e = a[i];
        if (e == "+" || e == "-" || e == "*" || e == "/")
        {
            string a = s.top();
            s.pop();
            string b = s.top();
            s.pop();
            if (e == "+")
            {
                s.push(to_string(stoi(b) + stoi(a)));
            }
            else if (e == "-")
            {
                s.push(to_string(stoi(b) - stoi(a)));
            }
            else if (e == "*")
            {
                s.push(to_string(stoi(b) * stoi(a)));
            }
            else if (e == "/")
            {
                s.push(to_string(stoi(b) / stoi(a)));
            }
        }
        else
        {
            s.push(e);
        }
    }

    cout << s.top() << endl;
}