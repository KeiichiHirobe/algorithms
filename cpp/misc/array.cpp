#include <iostream>
#include <vector>
using namespace std;

template <typename Array>
struct array_iterator
{
    Array &a;
    size_t i;

    array_iterator(Array &a, size_t i) : a(a), i(i) {}

    array_iterator &operator--();

    typename Array::reference &operator*()
    {
        return a[i];
    }

    typename Array::reference operator [] (size_t n) {
        return a[i+n];
    }

    array_iterator &operator++();
};

template <typename Array>
array_iterator<Array> &  array_iterator<Array>::operator++()
    {
        ++i;
        return *this;
    }

template <typename T, size_t N>
struct array
{
    T storage[N];

    using reference = T &;
    using const_reference = T const &;
    using iterator = array_iterator<array>;

    reference operator[](size_t i)
    {
        return storage[i];
    }

    const_reference operator[](size_t i) const
    {
        return storage[i];
    }

    iterator
    begin()
    {
        return array_iterator(*this, 0);
    }
};

template < typename T>
struct iota_iterator {
    using different_typee = ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = input_iterator_tag;
    T e;

    iota_iterator(T e=0): e(e){}

    reference operator *(){
        return e;
    }

    iota_iterator operator ++() {
        e += 1;
        return *this;
    }

}
;

template <typename T>
bool operator !=(iota_iterator<T> const &l, iota_iterator<T> const &r )  {
    return l.e != r.e;
}

int main()
{
    /*
    ::array<int, 5> a = {1, 2, 3, 4, 5};
    auto iter = a.begin();
    *iter;
    ++iter;
    */

    iota_iterator iter(0);
    cout << *iter << endl;
    *++iter;
    *++iter;
    cout << *iter <<endl;

    iota_iterator first(0), last(10);

    for_each(first, last,
    [](auto i){cout<<i;});

    vector<int> v;
    copy(first, last,back_insert_iterator(v));

    for (auto i : v) {
        cout << i <<endl;
    }
}