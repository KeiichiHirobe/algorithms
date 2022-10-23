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
        if (ptr == nullptr) {
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
        if (this != &p) {
            *ptr = *p.ptr;
        }
        return *this;
    }
    person &operator=(person &&p) {
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

