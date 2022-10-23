#include <bits/stdc++.h>

/*
このクラスはstd::forward_list を自力で書いたもの
destructorや代入など実装していないものが多い
gccの実装を大体読んで書き換えたものが forward_list_gcc.cpp
そちらを読むこと

反省としては、

* Tのallocatorをnode<T> のallocatorに変換する方法(rebind_alloc)を知らなかったために、*Tをnodeに持たせてしまった
* before_begin/end のために2つ番兵ノードを作ってしまったが、endはnullptrで良かった
* nodeの要素を持たないクラスをsuper class(node_base)として定義した方が良い。番兵ノードのTのconstructorが呼ばれてしまうこともない
* propagate_on_container_copy_assignment/propagate_on_container_move_assignment/propagate_on_container_swap_assignment　の取り扱いは全くできていないと思われる

*/

#include "person.cpp"

template <typename T, typename Allocator = std::allocator<T>>
struct node {
    using allocator_type = Allocator;
    using traits = std::allocator_traits<allocator_type>;

    T *v;
    node *next;
    allocator_type alloc;

    node(const T &x, const allocator_type &alloc, node *next = nullptr) : next(next), alloc(alloc) {
        v = traits::allocate(this->alloc, 1);
        traits::construct(this->alloc, v, x);
    }
    node(T &&x, const allocator_type &alloc, node *next = nullptr) : next(next), alloc(alloc) {
        v = traits::allocate(this->alloc, 1);
        traits::construct(this->alloc, v, std::move(x));
    }

    template <typename... Args>
    node(const allocator_type &alloc, node *next, Args &&...args) : next(next), alloc(alloc) {
        v = traits::allocate(this->alloc, 1);
        traits::construct(this->alloc, v, std::forward<Args>(args)...);
    }

    ~node() {
        traits::destroy(alloc, v);
        traits::deallocate(alloc, v, 1);
    }
};

template <typename T>
struct list_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using iterator_category = std::forward_iterator_tag;

    // todo 外からアクセスできるのは良くない
    node<T> *x;

    list_iterator(node<T> *x) : x(x) {
    }
    list_iterator() : x(nullptr) {
    }

    list_iterator &operator++() {
        x = x->next;
        return *this;
    }
    list_iterator &operator++(int) {
        list_iterator copy = *this;
        ++*this;
        return copy;
    }

    bool operator==(list_iterator const &right) {
        return x == right.x;
    }
    bool operator!=(list_iterator const &right) {
        return !(*this == right);
    }
    reference operator*() const {
        return *(x->v);
    }
};

template <typename T>
struct const_list_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = const T &;
    using pointer = T *;
    using iterator_category = std::forward_iterator_tag;

    // todo constを外した
    node<T> *x;

    const_list_iterator() : x(nullptr) {
    }
    const_list_iterator(const node<T> *x) : x(x) {
    }
    const_list_iterator(list_iterator<T> const &itr) : x(itr.x) {
    }

    const_list_iterator &operator++() {
        x = x->next;
        return *this;
    }
    const_list_iterator &operator++(int) {
        const_list_iterator copy = *this;
        ++*this;
        return copy;
    }

    bool operator==(const_list_iterator const &right) {
        return x == right.x;
    }
    bool operator!=(const_list_iterator const &right) {
        return !(*this == right);
    }
    reference operator*() const {
        return *(x->v);
    }
};

template <typename T, typename Allocator = std::allocator<T>>
class forward_list {
public:
    using reference = T &;
    using const_reference = const T &;
    using iterator = list_iterator<T>;
    using const_iterator = const_list_iterator<T>;
    using size_type = std::size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    explicit forward_list(const allocator_type &alloc) : alloc(alloc) {
        head = new node(T(), alloc);
        last = new node(T(), alloc, head.x);
        head.x->next = last.x;
    }
    forward_list() : forward_list(allocator_type()) {
    }

    template <typename InputeIterator>
    forward_list(InputeIterator first, InputeIterator last, const allocator_type &alloc = allocator_type())
        : forward_list(alloc) {
        for (InputeIterator itr = first; itr != last; ++itr) {
            push_front(*itr);
        }
    }

    forward_list(std::initializer_list<value_type> init, const allocator_type &alloc = allocator_type())
        : forward_list(alloc, std::begin(init), std::end(init)) {
    }

    forward_list(const forward_list &x) {
    }

    ~forward_list() {
        while (not empty()) {
            erase_after(head);
        }
        delete head.x;
        delete last.x;
    }

    bool empty() const noexcept {
        return begin() == end();
    }

    iterator before_begin() noexcept {
        return head;
    }

    const_iterator before_begin() const noexcept {
        return head;
    }

    const_iterator cbefore_begin() const noexcept {
        return head;
    }

    iterator begin() noexcept {
        return std::next(head);
    }

    const_iterator begin() const noexcept {
        return std::next(head);
    }

    const_iterator cbegin() const noexcept {
        return std::next(head);
    }

    iterator end() noexcept {
        return last;
    }

    const_iterator end() const noexcept {
        return last;
    }

    const_iterator cend() const noexcept {
        return last;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    iterator insert_after(const_iterator position, const T &x) {
        auto prev = position.x;
        auto now = new node(x, alloc);
        now->next = prev->next;
        prev->next = now;
        return now;
    }

    iterator insert_after(iterator position, T &&x) {
        auto prev = position.x;
        auto now = new node(std::move(x), alloc);
        now->next = prev->next;
        prev->next = now;
        return now;
    }

    template <typename... Args>
    iterator emplace_after(const_iterator position, Args &&...args) {
        auto prev = position.x;
        auto now = new node(alloc, (node<T> *)nullptr, std::forward<Args>(args)...);
        now->next = prev->next;
        prev->next = now;
        return now;
    }

    iterator erase_after(const_iterator position) {
        auto prev = position.x;
        auto target = prev->next;
        prev->next = prev->next->next;
        delete target;
        return prev->next;
    }

    iterator push_front(const T &x) {
        return insert_after(head, x);
    }

    iterator push_front(T &&x) {
        return insert_after(head, std::move(x));
    }

private:
    list_iterator<T> head;
    list_iterator<T> last;
    allocator_type alloc;
};

int main() {
    {
        forward_list<person> ls;

        ls.push_front(person{3});
        std::cout << "------" << std::endl;
        ls.insert_after(ls.begin(), {1});
        person p1{0};
        ls.insert_after(ls.before_begin(), p1);
        ls.emplace_after(ls.before_begin(), 2);

        std::for_each(ls.cbegin(), ls.cend(), [](const person &x) { std::cout << x; });
        std::cout << "-------------" << std::endl;
        // before_beginとendは異なることが保証されている

        for (auto itr = ls.before_begin();;) {
            auto ni = std::next(itr);
            if (ni == ls.end())
                break;
            if (*ni == person{3}) {
                itr = ls.erase_after(itr);
            } else {
                ++itr;
            }
        }
        std::for_each(ls.cbegin(), ls.cend(), [](const person &x) { std::cout << x; });
    }

    /*
            std::cout << "-------------" << std::endl;
            forward_list<person> ls;
            std::forward_list ls2 = {person{1}, person{2}, person{3}, person{4}};
            ls.swap(ls2);
            ls.resize(6);
            ls.resize(8, person{100});
            std::for_each(ls.cbegin(), ls.cend(), [](const person &x)
                          { std::cout << x; });

            ls.clear();
    */
}