#include <iostream>
#include <list>

using namespace std;

list<int> st;

// スタックを初期化する
void init()
{
}

// スタックが空かどうかを判定する
bool isEmpty()
{
    return st.size() == 0;
}

// push
void push(int x)
{
    st.push_back(x);
}

// pop
int pop()
{
    if (isEmpty())
    {
        cout << "error: stack is empty." << endl;
        return -1;
    }
    auto itr = st.end();
    int ret = *(--itr);
    st.erase(itr);
    return ret;
}

int main()
{
    init(); // スタックを初期化

    push(3); // スタックに 3 を挿入する {} -> {3}
    push(5); // スタックに 5 を挿入する {3} -> {3, 5}
    push(7); // スタックに 7 を挿入する {3, 5} -> {3, 5, 7}

    cout << pop() << endl; // {3, 5, 7} -> {3, 5} で 7 を出力
    cout << pop() << endl; // {3, 5} -> {3} で 5 を出力

    push(9); // 新たに 9 を挿入する {3} -> {3, 9}
}