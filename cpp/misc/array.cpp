#include <bits/stdc++.h>

template <typename Array>
struct array_iterator
{
    using difference_type = std::ptrdiff_t;
    using value_type = typename Array::value_type;
    using reference = typename Array::reference;
    using pointer = typename Array::pointer_type;
    using iterator_category = std::random_access_iterator_tag;

    Array &a;
    size_t i;

    array_iterator(Array &a, size_t i) : a(a), i(i) {}

    array_iterator &operator++()
    {
        ++i;
        return *this;
    }
    array_iterator &operator--()
    {
        --i;
        return *this;
    }
    array_iterator &operator++(int)
    {
        array_iterator copy = *this;
        ++*this;
        return copy;
    }
    array_iterator &operator--(int)
    {
        array_iterator copy = *this;
        --*this;
        return copy;
    }
    array_iterator &operator+=(std::size_t n)
    {
        i += n;
        return *this;
    }
    array_iterator &operator-=(std::size_t n)
    {
        i -= n;
        return *this;
    }
    array_iterator operator+(std::size_t n) const
    {
        auto copy = *this;
        copy += n;
        return copy;
    }
    array_iterator operator-(std::size_t n) const
    {
        auto copy = *this;
        copy -= n;
        return copy;
    }

    bool operator==(array_iterator const &right)
    {
        return i == right.i;
    }
    bool operator!=(array_iterator const &right)
    {
        return i != right.i;
    }
    bool operator<(array_iterator const &right)
    {
        return i < right.i;
    }
    bool operator>(array_iterator const &right)
    {
        return i > right.i;
    }
    bool operator<=(array_iterator const &right)
    {
        return i <= right.i;
    }
    bool operator>=(array_iterator const &right)
    {
        return i >= right.i;
    }

    reference operator*() const
    {
        return a[i];
    }
    reference operator[](size_t n) const
    {
        return *(*this + n);
    }
};

// array_iteratorの差異は
// * メンバのArrayがconst修飾されている
// * コンストラクタの引数のArrayもconst修飾されている
// * 変換コンストラクタがあること
// * *と[]がconst referenceを返すこと
template <typename Array>
struct array_const_iterator
{
    using difference_type = std::ptrdiff_t;
    using value_type = typename Array::value_type;
    /// const_referenceを返す必要があることに注意
    using reference = typename Array::const_reference;
    using pointer = typename Array::pointer_type;
    using iterator_category = std::random_access_iterator_tag;

    Array const &a;
    size_t i;

    array_const_iterator(Array const &a, size_t i) : a(a), i(i) {}
    array_const_iterator(array_iterator<Array> const &iter) : a(iter.a), i(iter.i) {}

    array_const_iterator &operator++()
    {
        ++i;
        return *this;
    }
    array_const_iterator &operator--()
    {
        --i;
        return *this;
    }
    array_const_iterator &operator++(int)
    {
        array_const_iterator copy = *this;
        ++*this;
        return copy;
    }
    array_const_iterator &operator--(int)
    {
        array_const_iterator copy = *this;
        --*this;
        return copy;
    }
    array_const_iterator &operator+=(std::size_t n)
    {
        i += n;
        return *this;
    }
    array_const_iterator &operator-=(std::size_t n)
    {
        i -= n;
        return *this;
    }
    array_const_iterator operator+(std::size_t n) const
    {
        auto copy = *this;
        copy += n;
        return copy;
    }
    array_const_iterator operator-(std::size_t n) const
    {
        auto copy = *this;
        copy -= n;
        return copy;
    }

    bool operator==(array_const_iterator const &right)
    {
        return i == right.i;
    }
    bool operator!=(array_const_iterator const &right)
    {
        return i != right.i;
    }
    bool operator<(array_const_iterator const &right)
    {
        return i < right.i;
    }
    bool operator>(array_const_iterator const &right)
    {
        return i > right.i;
    }
    bool operator<=(array_const_iterator const &right)
    {
        return i <= right.i;
    }
    bool operator>=(array_const_iterator const &right)
    {
        return i >= right.i;
    }

    reference operator*() const
    {
        return a[i];
    }
    reference operator[](size_t n)
    {
        return *(*this + n);
    }
};

template <typename T, size_t N>
struct array
{
    T storage[N];

    using value_type = T;
    using pointer_type = T *;
    using reference = T &;
    using const_reference = T const &;
    using iterator = array_iterator<array>;
    using const_iterator = array_const_iterator<array>;

    reference operator[](size_t i)
    {
        return storage[i];
    }

    const_reference operator[](size_t i) const
    {
        return storage[i];
    }

    iterator begin()
    {
        return array_iterator(*this, 0);
    }

    iterator end()
    {
        return array_iterator(*this, N);
    }
    const_iterator cbegin() const
    {
        return array_const_iterator(*this, 0);
    }
    const_iterator cend() const
    {
        return array_const_iterator(*this, N);
    }
    // const arrayの時にconst_iteratorを返す
    // const修飾されたインスタンスからはconstなメンバ関数しか呼び出すことができない。
    // constなメンバ関数はrefereceを返すのではなく、const referenceを返すべき
    const_iterator begin() const
    {
        return array_const_iterator(*this, 0);
    }
    // const arrayの時にconst_iteratorを返す
    const_iterator end() const
    {
        return array_const_iterator(*this, N);
    }
};

int main()
{
    const array<int, 5> b = {1, 2, 3, 4, 5};
    std::for_each(b.begin(), b.end(), [](auto x)
                  { std::cout << x; });

    std::reverse_iterator rfirst(b.end());
    rfirst++;
    std::cout << *rfirst << std::endl;

    array<int, 5> c = {1, 2, 3, 4, 5};
    array<int, 5>::iterator iter = c.begin();
    array<int, 5>::const_iterator citer = iter;
    std::cout << *citer;
    ++citer;
    std::cout << *citer;
}