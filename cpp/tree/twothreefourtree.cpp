#include <iostream>
#include <assert.h>
#include <gtest/gtest.h>
// 最大リンク数
// 最大要素数はN-1
#define N 4
using namespace std;

// chのいずれかがNull -> 必ず底
// 底 -> chの全てがNull
struct Node
{
    // array[N-1]
    int *val;
    // 0 - N-1
    int cnt;
    // array[N]
    Node **ch;
    Node()
    {
        cnt = 0;
        val = new int[N - 1];
        ch = new Node *[N];
        memset(ch, 0, sizeof(Node *) * N);
    }
    void Reset()
    {
        cnt = 0;
        for (int i = 0; i < N - 1; i++)
            val[i] = 0;
        memset(ch, 0, sizeof(Node *) * N);
    }
};

bool findr(Node *p, int x)
{
    if (p == nullptr)
        return false;

    if (p->cnt == 0)
    {
        return false;
    }
    int ch_idx = 0;
    for (; ch_idx < p->cnt; ++ch_idx)
    {
        if (p->val[ch_idx] == x)
            return true;
        if (x < p->val[ch_idx])
        {
            break;
        }
    }
    return findr(p->ch[ch_idx], x);
}

void sortr(Node *p, vector<int> &v)
{
    if (p == nullptr)
        return;
    for (int i = 0; i < p->cnt + 1; ++i)
    {
        sortr(p->ch[i], v);
        if (i < p->cnt)
        {
            v.push_back(p->val[i]);
        }
    }
}

Node *insertr(Node *p, int x)
{
    // 初回のみ
    if (p == nullptr)
    {
        Node *e = new Node;
        e->cnt = 1;
        e->val[0] = x;
        return e;
    }
    // split root
    // increment height
    if (p->cnt == N - 1)
    {
        Node *ch1 = new Node;
        Node *ch2 = new Node;
        ch1->cnt = 1;
        ch2->cnt = 1;
        ch1->val[0] = p->val[0];
        ch2->val[0] = p->val[2];
        ch1->ch[0] = p->ch[0];
        ch1->ch[1] = p->ch[1];
        ch2->ch[0] = p->ch[2];
        ch2->ch[1] = p->ch[3];
        int middle = p->val[1];
        p->Reset();
        p->cnt = 1;
        p->val[0] = middle;
        p->ch[0] = ch1;
        p->ch[1] = ch2;
    }
    int ch_idx = 0;
    for (; ch_idx < p->cnt; ++ch_idx)
    {
        if (p->val[ch_idx] == x)
            // found x
            // do nothing
            return p;
        if (x < p->val[ch_idx])
        {
            break;
        }
    }
    Node *ch = p->ch[ch_idx];
    if (ch == nullptr)
    {
        ++p->cnt;
        assert(p->cnt <= N - 1);
        for (int i = p->cnt - 1; i > ch_idx; i--)
            p->val[i] = p->val[i - 1];
        p->val[ch_idx] = x;
        return p;
    }
    // split child
    if (ch->cnt == N - 1)
    {
        Node *ch1 = new Node;
        Node *ch2 = new Node;
        ch1->cnt = 1;
        ch2->cnt = 1;
        ch1->val[0] = ch->val[0];
        ch2->val[0] = ch->val[2];
        ch1->ch[0] = ch->ch[0];
        ch1->ch[1] = ch->ch[1];
        ch2->ch[0] = ch->ch[2];
        ch2->ch[1] = ch->ch[3];
        int middle = ch->val[1];
        delete ch;
        ++p->cnt;
        for (int i = p->cnt - 1; i >= ch_idx; i--)
            p->val[i] = p->val[i - 1];
        p->val[ch_idx] = middle;
        for (int i = p->cnt; i > ch_idx + 1; i--)
            p->ch[i] = p->ch[i - 1];
        p->ch[ch_idx] = ch1;
        p->ch[ch_idx + 1] = ch2;
        if (middle < x)
        {
            ++ch_idx;
            ch = ch2;
        }
        else
        {
            ch = ch1;
        }
    }
    p->ch[ch_idx] = insertr(ch, x);
    return p;
}

struct TwoThreeFourTree
{
    Node *root;

    TwoThreeFourTree()
    {
        root = nullptr;
    }
    bool find(int x)
    {
        return findr(root, x);
    }
    void sort(vector<int> &v)
    {
        sortr(root, v);
    }
    void insert(int x)
    {
        root = insertr(root, x);
    }
};

// /usr/bin/clang++ --std c++17 /Users/keiichi/go/src/github.com/algorithms/cpp/tree/twothreefour.cpp -o ./twothreefour -L/usr/local/lib -lgtest -lgtest_main
TEST(Regular, InsertFindErase)
{
    TwoThreeFourTree t;
    t.insert(7);
    t.insert(2);
    t.insert(5);
    t.insert(3);
    t.insert(13);
    t.insert(15);
    t.insert(6);
    EXPECT_TRUE(t.find(2));
    EXPECT_FALSE(t.find(12));
    EXPECT_TRUE(t.find(2));
    EXPECT_TRUE(t.find(15));
    EXPECT_TRUE(t.find(13));
    vector<int> expected{2, 3, 5, 6, 7, 13, 15};
    vector<int> got;
    t.sort(got);
    EXPECT_TRUE(got == expected);
}