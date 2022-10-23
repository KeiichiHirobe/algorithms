#include <bits/stdc++.h>

// このクラスは要素型に依存しない
struct node_base {
    node_base() = default;
    node_base(const node_base &) = delete;
    node_base(node_base &&x) noexcept : next(x.next) {
        x.next = nullptr;
    }

    node_base &operator=(const node_base &) = delete;
    node_base &operator=(node_base &&x) {
        // ここで正しくdeleteする方法がない
        // このクラスではnextのメモリ管理は責務外としていそう
        // list_baseはmove assignができないので実質的には問題なさそうではある
        // delete next;
        next = x.next;
        x.next = nullptr;
        return *this;
    }
    // 自分以降をreverse
    void reverse_after() {
        node_base *cur = nullptr;
        node_base *suc = next;
        while (suc != nullptr) {
            node_base *t = suc->next;
            suc->next = cur;
            cur = suc;
            suc = t;
        }
        next = cur;
    }
    // 他のリストのbeginの次からendを取ってきて、自分のリストの先頭につける
    node_base *transfer_after(node_base *begin, node_base *end) {
        node_base *t = begin->next;
        if (end != nullptr) {
            begin->next = end->next;
            end->next = next;
        } else {
            begin->next = nullptr;
        }
        next = t;
        return end;
    }

    node_base *next = nullptr;
};

template <typename T>
struct node : public node_base {
    node() = default;
    // defaultのcopy constructorは基底クラスのcopy constructorを呼ぶ。
    // deleteされている場合は、defaultのコピーコンストラクは作られない
    // copy constructorを定義し、基底クラスを明示的に呼ばない場合は基底クラスのdefault constructorが呼ばれる
    // copy assignment も同様。ただし、暗黙的に基底クラスのdefault constructorが呼ばれることはない
    // nodeクラスはcopy constructor/copy operatorが存在しない

    // T x
    // のように書くと、Tのデフォルトコンストラクタが呼ばれてしまう
    // メモリアロケートのみさせるために std::aligned_storage　を利用
    // https://cpprefjp.github.io/reference/type_traits/aligned_storage.html
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
    T *value() {
        return static_cast<T *>(static_cast<void *>(&storage));
    }
    const T *value() const {
        return static_cast<const T *>(static_cast<const void *>(&storage));
    }
};

template <typename T>
struct list_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using iterator_category = std::forward_iterator_tag;

    // 外からアクセスできるのは良くないが、gccの実装も同様だった
    node_base *x;

    list_iterator() : x(nullptr) {
    }
    list_iterator(node_base *x) : x(x) {
    }

    list_iterator &operator++() {
        x = x->next;
        return *this;
    }
    list_iterator operator++(int) {
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
        return *static_cast<node<T> *>(x)->value();
    }
};

template <typename T>
struct const_list_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = const T &;
    using pointer = const T *;
    using iterator_category = std::forward_iterator_tag;

    const node_base *x;

    const_list_iterator() : x(nullptr) {
    }
    const_list_iterator(const node_base *x) : x(x) {
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
        return *static_cast<const node<T> *>(x)->value();
    }
};

template <typename T, typename Alloc>
struct list_base {
protected:
    // メモリ割り当てはTに対してではなく、node<T> に対して行う
    // https://cpprefjp.github.io/reference/memory/allocator_traits.html
    // https://cpprefjp.github.io/lang/cpp11/alias_templates.html
    using allocator_type = typename std::allocator_traits<Alloc>::template rebind_alloc<node<T>>;
    using allocator_traits = std::allocator_traits<allocator_type>;

    // list_base,list_impl共にコピー禁止
    // move assign もできない
    struct list_impl : public allocator_type {
        // headはTの構築は不要
        // headはbefore_beginに該当する
        // endはnullptr
        // size = 0の時、begin == end になる
        node_base head;
        list_impl() = default;
        list_impl(list_impl &&) = default;
        list_impl(list_impl &&li, allocator_type &&a) : allocator_type(std::move(a)), head(std::move(li.head)) {
        }
        list_impl(allocator_type &&a) : allocator_type(std::move(a)), head() {
        }
    };

    list_impl impl;

public:
    using iterator = list_iterator<T>;
    using const_iterator = const_list_iterator<T>;
    using Node = node<T>;

    allocator_type &get_allocator() {
        return impl;
    }
    const allocator_type &get_allocator() const {
        return impl;
    }
    list_base() = default;
    list_base(allocator_type &&a) : impl(std::move(a)) {
    }
    list_base(list_base &&) = default;
    ~list_base() {
        base_erase_after(&impl.head, nullptr);
    }

protected:
    //メモリ確保のみ
    Node *get_node() {
        return allocator_traits::allocate(get_allocator(), 1);
    }
    // メモリ破棄のみ
    void put_node(Node *p) {
        allocator_traits::deallocate(get_allocator(), p, 1);
    }
    // メモリ確保と構築
    template <typename... Args>
    Node *create_node(Args &&...args) {
        Node *node = get_node();
        // newプレイスメント
        new ((void *)node) Node();
        allocator_traits::construct(get_allocator(), node->value(), std::forward<Args>(args)...);
        return node;
    }

    template <typename... Args>
    node_base *base_insert_after(const_iterator pos, Args &&...args) {
        node_base *prev = const_cast<node_base *>(pos.x);
        Node *x = create_node(std::forward<Args>(args)...);
        x->next = prev->next;
        prev->next = x;
        return x;
    }

    // pos->nextはnullptrではないことを前提
    node_base *base_erase_after(node_base *pos) {
        Node *cur = static_cast<Node *>(pos->next);
        pos->next = cur->next;
        allocator_traits::destroy(get_allocator(), cur->value());
        cur->~Node();
        put_node(cur);
        return pos->next;
    }

    node_base *base_erase_after(node_base *pos, node_base *last) {
        node_base *cur = pos;
        while (cur != last && pos->next != nullptr) {
            cur = base_erase_after(pos);
        }
        pos->next = last;
        return last;
    }
};

// private継承であることに注意
template <typename T, typename Alloc = std::allocator<T>>
class forward_list : private list_base<T, Alloc> {
private:
    using Base = list_base<T, Alloc>;
    using Node = typename Base::Node;
    using Node_alloc_type = typename Base::allocator_type;
    using Node_alloc_traits = typename Base::allocator_traits;

public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = typename Base::iterator;
    using const_iterator = typename Base::const_iterator;
    using size_type = std::size_t;
    using difference_type = ptrdiff_t;
    using allocator_type = Alloc;
    using pointer = typename std::allocator_traits<Alloc>::pointer;
    using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;

    forward_list() = default;

    explicit forward_list(const allocator_type &alloc) : Base(Node_alloc_type(alloc)) {
    }

    forward_list(const forward_list &x)
        : Base(Node_alloc_traits::select_on_container_copy_construction(x.get_allocator())) {
        range_initialize(x.begin(), x.end());
    }
    forward_list(forward_list &&x) = default;
    forward_list(std::initializer_list<T> il, const allocator_type &alloc = allocator_type())
        : Base(Node_alloc_type(alloc)) {
        range_initialize(il.begin(), il.end());
    }

    ~forward_list() {
    }

    forward_list &operator=(const forward_list &x) {
        if (this == &x)
            return *this;

        if (Node_alloc_traits::propagate_on_container_copy_assignment::value) {
            auto &this_alloc = this->get_allocator();
            auto &that_alloc = x.get_allocator();
            if (!Node_alloc_traits::is_always_equal::value && this_alloc != that_alloc) {
                // allocatorを変更すると既存のリソースのfreeが正しくできなくなってしまう
                clear();
            }
            this_alloc = that_alloc;
        }
        assign(x.begin(), x.end());
        return *this;
    }

    forward_list &operator=(forward_list &&x) {
        constexpr bool move_storage =
            // move代入の時にpropagateするか
            Node_alloc_traits::propagate_on_container_move_assignment::value ||
            // 型が同じ場合は常に等価か
            Node_alloc_traits::is_always_equal::value;
        move_assign_helper(std::move(x), std::bool_constant<move_storage>{});
        return *this;
    }

    iterator before_begin() {
        return iterator(&this->impl.head);
    }
    const_iterator before_begin() const {
        return const_iterator(&this->impl.head);
    }
    iterator begin() {
        return iterator(this->impl.head.next);
    }
    const_iterator begin() const {
        return const_iterator(this->impl.head.next);
    }
    iterator end() {
        return iterator(nullptr);
    }
    const_iterator end() const {
        return const_iterator(nullptr);
    }
    const_iterator cbegin() const {
        return const_iterator(this->impl.head.next);
    }
    const_iterator cbefore_begin() const {
        return const_iterator(&this->impl.head);
    }
    const_iterator cend() const {
        return const_iterator(nullptr);
    }

    bool empty() const {
        return this->impl.head.next == nullptr;
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    iterator insert_after(const_iterator pos, const T &x) {
        return iterator(this->base_insert_after(pos, x));
    }

    iterator insert_after(const_iterator pos, T &&x) {
        return iterator(this->base_insert_after(pos, std::move(x)));
    }

    iterator insert_after(const_iterator pos, iterator first, iterator last) {
        while (first != last) {
            pos = insert_after(pos, *first);
            ++first;
        }
        return pos;
    }

    template <typename... Args>
    iterator emplace_after(const_iterator pos, Args &&...args) {
        return iterator(this->base_insert_after(pos, std::forward<Args>(args)...));
    }

    iterator push_front(const T &x) {
        return insert_after(cbefore_begin(), x);
    }

    iterator push_front(T &&x) {
        return insert_after(cbefore_begin(), std::move(x));
    }

    iterator erase_after(const_iterator pos) {
        return iterator(this->base_erase_after(const_cast<node_base *>(pos.x)));
    }

    iterator erase_after(const_iterator pos, const_iterator last) {
        return iterator(this->base_erase_after(const_cast<node_base *>(pos.x), const_cast<node_base *>(last.x)));
    }

    void clear() {
        this->base_erase_after(&this->impl.head, nullptr);
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        // 例えば is_assignable<T&, const T&>::value == true ならコピー代入可能であることを意味する
        assign_helper(first, last, std::is_assignable<T, decltype(*first)>());
    }

    void assign(std::initializer_list<T> il) {
        assign(il.begin(), il.end());
    }

    void swap(forward_list &x) {
        std::swap(this->impl.head.next, x.impl.head.next);
        if (Node_alloc_traits::propagate_on_container_swap::value) {
            using std::swap;
            swap(this->get_allocator(), x.get_allocator());
        }
    }

    // sort

private:
    template <typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last) {
        const_iterator cur = const_iterator(&this->impl.head);
        for (; first != last; ++first) {
            cur = this->base_insert_after(cur, *first);
        }
    }

    // allocatorがMoveAssignable
    void move_assign_helper(forward_list &&ls, std::true_type) {
        clear();
        // 以下のようにしたいとこだが、move assignmentが定義されてない
        // this->impl = std::move(ls.impl);
        this->impl.head.next = ls.impl.head.next;
        ls.impl.head.next = nullptr;
        this->get_allocator() = std::move(ls.get_allocator());
    }

    // allocatorがMoveAssignableではない
    void move_assign_helper(forward_list &&ls, std::false_type) {
        if (this->get_allocator() == ls.get_allocator()) {
            move_assign_helper(std::move(ls), std::true_type());
        } else {
            this->assign(std::make_move_iterator(ls.begin()), std::make_move_iterator(ls.end()));
        }
    }

    // TがAssignable
    template <typename InputIterator>
    void assign_helper(InputIterator first, InputIterator last, std::true_type) {
        auto prev = before_begin();
        auto cur = begin();
        auto end = end();
        while (cur != end && first != last) {
            *cur = *first;
            ++prev;
            ++cur;
            ++first;
        }
        if (first != last) {
            insert_after(prev, first, last);
        } else if (cur != end) {
            erase_after(prev, end);
        }
    }

    // TがAssignableではない
    template <typename InputIterator>
    void assign_helper(InputIterator first, InputIterator last, std::false_type) {
        clear();
        insert_after(cbefore_begin(), first, last);
    }
};

#include "person.cpp"

int main() {
    {
        forward_list<person> ls;

        ls.push_front(person{3});
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
    std::cout << "-------------" << std::endl;
    forward_list<person> ls;
    forward_list ls2 = {person{1}, person{2}, person{3}, person{4}};
    ls.swap(ls2);
    std::for_each(ls.cbegin(), ls.cend(), [](const person &x) { std::cout << x; });

    ls = std::move(ls2);

    ls.clear();
}