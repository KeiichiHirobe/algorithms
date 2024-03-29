#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
// clang-format off
#define rep(i, s ,n) for(int i=s, i##_len=(n); i<i##_len; ++i)
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define SZ(x) ((int)(x).size())
using ll = long long;
// 2^60
const ll INF = 1LL << 60;
// lower_bound(ALL(a), 4)
#define ALL(a)  (a).begin(),(a).end()
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
using namespace std;
using Graph = vector<vector<int>>;
// clang-format on

// https://qiita.com/drken/items/1b7e6e459c24a83bb7fd
template <class VAL>
struct RBST {
    static const VAL SUM_UNITY = 0;  // to be set

    // xorshift
    // https://ja.wikipedia.org/wiki/Xorshift
    static unsigned int randInt() {
        static unsigned int tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
        unsigned int tt = (tx ^ (tx << 11));
        tx = ty;
        ty = tz;
        tz = tw;
        return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
    }

    // https://www.slideshare.net/iwiwi/2-12188757
    // にあるような反転のあるminimum range query を実装したいなど、集合ではなくただの順序をもつ列を管理したい場合
    // val にはただのindexが入る
    // 列の値やminは別のフィールドを用意する必要がある

    struct NODE {
        NODE *left, *right;
        VAL val;   // the value of the node
        int size;  // the size of the subtree
        VAL sum;   // the value-sum of the subtree

        NODE() : val(SUM_UNITY), size(1), sum(SUM_UNITY) {
            left = right = NULL;
        }

        NODE(VAL v) : val(v), size(1), sum(v) {
            left = right = NULL;
        }

        /* additional update */
        void update() {
        }

        /* additional lazy-propagation */
        void push() {
            /* ex: reverse */
            /*
            if (this->rev) {
            swap(this->left, this->right);
            if (this->left) this->left->rev ^= true;
            if (this->right) this->right->rev ^= true;
            this->rev = false;
            }
            */
        }
    };

    ///////////////////////
    // root
    ///////////////////////

    NODE *root;
    RBST() : root(NULL) {
    }
    RBST(NODE *node) : root(node) {
    }

    ///////////////////////
    // basic operations
    ///////////////////////

    /* size */
    static int size(NODE *node) {
        return !node ? 0 : node->size;
    }
    int size() {
        return this->size(this->root);
    }

    /* sum */
    static VAL sum(NODE *node) {
        return !node ? SUM_UNITY : node->sum;
    }
    VAL sum() {
        return this->sum(this->root);
    }

    /* update, push */
    static NODE *update(NODE *node) {
        node->size = size(node->left) + size(node->right) + 1;
        node->sum = sum(node->left) + sum(node->right) + node->val;
        node->update();
        return node;
    }

    static void push(NODE *node) {
        if (!node)
            return;
        node->push();
    }

    /* lower_bound */
    static int lowerBound(NODE *node, VAL val) {
        push(node);
        if (!node)
            return 0;
        if (val <= node->val)
            return lowerBound(node->left, val);
        else
            return size(node->left) + lowerBound(node->right, val) + 1;
    }
    int lowerBound(VAL val) {
        return this->lowerBound(this->root, val);
    }

    /* upper_bound */
    static int upperBound(NODE *node, VAL val) {
        push(node);
        if (!node)
            return 0;
        if (val >= node->val)
            return size(node->left) + upperBound(node->right, val) + 1;
        else
            return upperBound(node->left, val);
    }
    int upperBound(VAL val) {
        return this->upperBound(this->root, val);
    }

    /* count */
    int count(VAL val) {
        return upperBound(val) - lowerBound(val);
    }

    /* get --- k: 0-index */
    static VAL get(NODE *node, int k) {
        push(node);
        if (!node)
            return -1;
        if (k == size(node->left))
            return node->val;
        if (k < size(node->left))
            return get(node->left, k);
        else
            return get(node->right, k - size(node->left) - 1);
    }
    VAL get(int k) {
        return get(this->root, k);
    }

    ///////////////////////
    // merge-split
    ///////////////////////
    // rightの任意の要素はleftの任意の要素より大きいか等しいことを前提としている
    static NODE *merge(NODE *left, NODE *right) {
        push(left);
        push(right);
        if (!left || !right) {
            if (left)
                return left;
            else
                return right;
        }
        if (randInt() % (left->size + right->size) < left->size) {
            left->right = merge(left->right, right);
            return update(left);
        } else {
            right->left = merge(left, right->left);
            return update(right);
        }
    }
    void merge(RBST add) {
        this->root = this->merge(this->root, add.root);
    }
    static pair<NODE *, NODE *> split(NODE *node, int k) {  // [0, k), [k, n)
        push(node);
        if (!node)
            return make_pair(node, node);
        if (k <= size(node->left)) {
            pair<NODE *, NODE *> sub = split(node->left, k);
            node->left = sub.second;
            return make_pair(sub.first, update(node));
        } else {
            pair<NODE *, NODE *> sub = split(node->right, k - size(node->left) - 1);
            node->right = sub.first;
            return make_pair(update(node), sub.second);
        }
    }
    RBST split(int k) {
        pair<NODE *, NODE *> sub = split(this->root, k);
        this->root = sub.first;
        return RBST(sub.second);
    }

    ///////////////////////
    // insert-erase
    ///////////////////////

    void insert(const VAL val) {
        pair<NODE *, NODE *> sub = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(this->merge(sub.first, new NODE(val)), sub.second);
    }

    void erase(const VAL val) {
        if (!this->count(val))
            return;
        pair<NODE *, NODE *> sub = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(sub.first, this->split(sub.second, 1).second);
    }

    ///////////////////////
    // debug
    ///////////////////////

    void print(NODE *node) {
        if (!node)
            return;
        push(node);
        print(node->left);
        cout << node->val << " ";
        print(node->right);
    }
    void print() {
        cout << "{";
        print(this->root);
        cout << "}" << endl;
    }
};

int main() {
    RBST<long long> S;
    int Q, K;
    cin >> Q >> K;
    for (int i = 0; i < Q; ++i) {
        int T;
        cin >> T;
        if (T == 1) {
            long long val;
            cin >> val;
            S.insert(val);
        } else {
            if (S.size() < K) {
                cout << -1 << endl;
                continue;
            }
            // K番目に大きい値を取得して削除
            long long res = S.get(K - 1);
            cout << res << endl;
            S.erase(res);
        }
        // S.print();
    }
}
