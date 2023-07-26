#include <bits/stdc++.h>

struct person {
    int *ptr;
    person(int id = 0) : ptr(new int(id)) {
    }
    person(const person &p) : ptr(new int(*p.ptr)) {
        if (ptr == nullptr) {
            std::cout << "copy constructor for person (nullptr)" << std::endl;
        } else {
            std::cout << "copy constructor for person (" << *ptr << ")" << std::endl;
        }
    }
    person(person &&p) : ptr(p.ptr) {
        if (p.ptr == nullptr) {
            std::cout << "get ownership for person (nullptr)" << std::endl;
        } else {
            std::cout << "get ownership for person (" << *ptr << ")" << std::endl;
        }
        p.ptr = nullptr;
    }
    ~person() {
        if (ptr == nullptr) {
            std::cout << "destructor person (nullptr)" << std::endl;
        } else {
            std::cout << "destructor person (" << *ptr << ")" << std::endl;
        }
        delete ptr;
    }
    person &operator=(const person &p) {
        std::cout << "copy assign" << std::endl;
        if (this != &p) {
            *ptr = *p.ptr;
        }
        return *this;
    }
    person &operator=(person &&p) {
        std::cout << "move assign" << std::endl;
        delete ptr;
        ptr = p.ptr;
        p.ptr = nullptr;
        return *this;
    }
    friend bool operator==(const person &a, const person &b) {
        return *a.ptr == *b.ptr;
    }
    friend bool operator<(const person &a, const person &b) {
        return *a.ptr < *b.ptr;
    }
    friend bool operator<=(const person &a, const person &b) {
        return *a.ptr <= *b.ptr;
    }
    friend bool operator>(const person &a, const person &b) {
        return *a.ptr > *b.ptr;
    }
    friend bool operator>=(const person &a, const person &b) {
        return *a.ptr >= *b.ptr;
    }
    friend std::ostream &operator<<(std::ostream &s, const person &v) {
        std::cout << *v.ptr << std::endl;
        return s;
    }
};

void hoge(person p1, person p2, person &p3, person &&p4, person &&p5, person p6) {
    std::cout << "hoge called" << std::endl;
    std::cout << *p6.ptr << std::endl;
}

int main() {
    person p1(1);
    person p2(2);
    person p3(3);
    person p4(4);
    hoge(p1, std::move(p2), p3, std::move(p4), person(5), person(6));
    std::cout << "hoge called finished" << std::endl;
}
