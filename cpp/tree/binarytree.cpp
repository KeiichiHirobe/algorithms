#include <iostream>
#include <assert.h>
#include <gtest/gtest.h>
using namespace std;

struct Node
{
    int val;
    Node *lch, *rch;
    Node(int val, Node *lch, Node *rch) : val(val), lch(lch), rch(rch) {}
};

bool findr(Node *p, int x)
{
    if (p == nullptr)
    {
        return false;
    }
    if (p->val == x)
    {
        return true;
    }
    else if (x < p->val)
    {
        return findr(p->lch, x);
    }
    else
    {
        return findr(p->rch, x);
    }
}

Node *insertr(Node *p, int x)
{
    if (p == nullptr)
    {
        return new Node(x, nullptr, nullptr);
    }
    else if (x < p->val)
    {
        p->lch = insertr(p->lch, x);
        return p;
    }
    else
    {
        p->rch = insertr(p->rch, x);
        return p;
    }
}

Node *eraser(Node *p, int x)
{
    assert(p != nullptr);
    if (x == p->val)
    {
        Node *lch = p->lch;
        Node *rch = p->rch;
        delete p;
        if (lch == nullptr)
        {
            return rch;
        }
        else if (lch->rch == nullptr)
        {
            lch->rch = p->rch;
            return lch;
        }
        Node *ell = lch;
        Node *el = lch->rch;
        while (el->rch != nullptr)
        {
            ell = el;
            el = el->rch;
        }
        ell->rch = el->lch;
        el->lch = lch;
        el->rch = rch;
        return el;
    }
    else if (x < p->val)
    {
        p->lch = eraser(p->lch, x);
        return p;
    }
    else
    {
        p->rch = eraser(p->rch, x);
        return p;
    }
}

struct BinaryTree
{
    Node *root;

    BinaryTree()
    {
        root = nullptr;
    }
    bool find(int x)
    {
        return findr(root, x);
    }

    void insert(int x)
    {
        root = insertr(root, x);
    }

    void erase(int x)
    {
        root = eraser(root, x);
    }
};

// /usr/bin/clang++ --std c++17 /Users/keiichi/go/src/github.com/algorithms/cpp/tree/binarytree.cpp -o ./binarytreetest  -L/usr/local/lib -lgtest -lgtest_main
TEST(Regular, InsertFindErase)
{
    BinaryTree t;
    t.insert(7);
    t.insert(2);
    t.insert(5);
    t.insert(3);
    t.insert(13);
    t.insert(15);
    t.insert(6);
    EXPECT_TRUE(t.find(2));
    EXPECT_FALSE(t.find(12));
    t.erase(2);
    EXPECT_FALSE(t.find(2));
    t.erase(15);
    EXPECT_FALSE(t.find(15));
    EXPECT_TRUE(t.find(13));
}