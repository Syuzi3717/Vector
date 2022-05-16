#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <initializer_list>

template <typename T>
class Vector{
public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T >{
    public:
        iterator() = default;
        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator(iterator&&) = default;
        iterator &operator=(const iterator&) = default;
        iterator(T* ptr) : m_ptr { ptr }{};
    public:
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
        bool operator<(const iterator&);
        bool operator<=(const iterator&);
        bool operator>(const iterator&);
        bool operator>=(const iterator&);
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        T &operator*();
        const T &operator*() const;
    private:
        T * m_ptr;
    };
    Vector();
    Vector(const Vector<T>&);
    Vector(Vector<T>&&);
    Vector(const std::initializer_list<T> &);
    Vector& operator=(const Vector<T>&);
    Vector& operator=(Vector<T>&&);
    ~Vector();
    void copy(T*);
public:

    void push_back(T);
    void pop_back();
    void push_front(T);
    void pop_front();
    void clear();
    void reserve(const int);
    T& at(size_t);
    bool empty() const;
    size_t size();
    size_t capacity();
    const T& operator[](size_t) const;
    T& operator[](size_t);
public:
    iterator find(iterator, iterator, const T& );
    iterator begin();
    iterator end();
private:
    T* m_array;
    size_t m_size;
    size_t m_cap;
};
template <>
class Vector<bool>{
public:
    class iterator{
    public:
        iterator() = default;
        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator(iterator&&) = default;
        iterator &operator=(const iterator&) = default;
        iterator(bool* ptr) : m_ptr { ptr }{};
    public:
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
        bool operator<(const iterator&);
        bool operator<=(const iterator&);
        bool operator>(const iterator&);
        bool operator>=(const iterator&);
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator*();
        const bool operator*() const;
    private:
        bool * m_ptr;
    };

    class Proxy {
    public:
        Proxy() = delete;
        ~Proxy() = default;
        Proxy(char* _p, size_t _sh)
        {
            ptr = _p;
            shift = _sh ;
        }
    public:
        operator bool() const
        {
            return (bool)( (*ptr) & (1 << shift) );
        }
        Proxy operator=(bool value)
        {
            if( value )
            {
               (*ptr) |= (1 << shift);
            }
            else
            {
                (*ptr) &= ~(1 << shift);
            }
            return *this;
        }
    private:
        char* ptr{};
        size_t shift{};
    };

public:
    Vector();
    Vector(const Vector<bool>&);
    Vector(Vector<bool>&&);
    Vector(const std::initializer_list<bool> &);
    Vector& operator=(const Vector<bool>&);
    Vector& operator=(Vector<bool>&&);
    ~Vector();
public:
    void push_back(bool);
    void pop_back();
    void push_front(bool);
    void pop_front();
    void clear();
    void reserve(const int);
    bool at(size_t);
    bool empty() const;
    size_t size();
    size_t capacity();
    const bool operator[](size_t) const;
    bool operator[](size_t);
public:
    iterator begin();
    iterator end();
private:
    bool* m_array{};
    size_t m_size{};
    size_t m_cap{};
};

#include "vec.hpp"

#endif 
