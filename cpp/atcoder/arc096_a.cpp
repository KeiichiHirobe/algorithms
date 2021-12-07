#include <iostream>
#include <vector>
#include <cmath>
#include <map>
// clang-format off
#define rep(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
// clang-format on

int main()
{
    int a;
    int b;
    int c;
    int x;
    int y;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> x;
    cin >> y;

    int both = 0;
    int rest = 0;
    int price = 0;

    if (x < y)
    {
        both = x;
        rest = y - x;
        price = b;
    }
    else
    {
        both = y;
        rest = x - y;
        price = a;
    }

    int total = 0;
    if (a + b < 2 * c)
    {
        total += (a + b) * both;
    }
    else
    {
        total += c * both * 2;
    }

    if (price < 2 * c)
    {
        total += price * rest;
    }
    else
    {
        total += 2 * c * rest;
    }

    cout << total << endl;
}