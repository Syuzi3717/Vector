#include <iostream>
#include <exception>
#include "vec.h"
#include <iterator>

template <typename T>
Vector<T>::Vector()
{
    m_size = 0;
    m_cap = 0;
    m_array = new T[m_cap];
}

template <typename T>
Vector<T>::~Vector()
{
    if(m_array != nullptr)
    {
        delete[] m_array;
        m_array = nullptr;
    }
}

template <typename T>
void Vector<T>::copy(T* ptr){
    if(ptr==nullptr){
        ptr=new T[m_cap];
        for(int i=0; i<m_size; ++i){
            ptr[i]=m_array[i];
        }
        delete[] m_array;
        m_array=ptr;
    }
    else{
        m_array=new T[m_cap];
        for(int i=0; i<m_size; ++i){
            m_array[i]=ptr[i];
        }
    }
}
template <typename T>
Vector<T>::Vector(const Vector<T>& oth)
{
    m_size = oth.m_size;
    m_cap = oth.m_cap;
    delete[] m_array;
    m_array = nullptr;
    copy(oth.m_array);
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& oth)
{
    m_size = oth.size();
    m_array = new T[m_cap];
    for(int i = 0; i < m_size; ++i)
    {
        m_array[i] = oth.begin()[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& oth)
{
    m_size = oth.m_size;
    m_cap = oth.m_cap;
    m_array = nullptr;
    m_array = oth.m_array;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &oth)
{
    if(this == &oth)
    {
        return *this;
    }
    m_size = oth.m_size;
    m_cap = oth.m_cap;
    delete[] m_array;
    copy(oth.m_array);
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T>&& oth)
{
    if (this == &oth)
    {
        return *this;
    }
    m_size = oth.m_size;
    m_cap = oth.m_cap;
    m_array = oth.m_array;
    return *this;
}

template <typename T>
const T& Vector<T>::operator[](size_t pos) const
{
    return m_array[pos];
}

template <typename T>
T& Vector<T>::operator[](size_t  pos)
{
    return m_array[pos];
}

template <typename T>
void Vector<T>::push_back(T elem)
{
    if(m_size == m_cap)
    {
        m_cap = m_cap == 0 ? 2 : m_cap * 2;
        copy(nullptr);
    }
    m_array[m_size] = elem;
    ++m_size;  
}

template <typename T>
void Vector<T>::pop_back()
{   
    if(!m_size) return ;
    if(m_size <= (m_cap / 2 ) ) 
    {
        m_cap = (m_cap / 2) + (m_cap % 2);
        copy(nullptr);
    }
    --m_size;
}

template <typename T>
void Vector<T>::push_front(T elem)
{
    if(m_size == m_cap)
    {
        m_cap = m_cap == 0 ? 2 : m_cap * 2;
        T *tmp = new T[m_cap];
        for(int i = 1; i <= m_size; ++i)
        {
            tmp[i] = m_array[i-1];
        }
        delete[] m_array;
        m_array = tmp;
    }
    else
    {
        for(int i = m_size - 1; i >= 0; --i)
        {
            m_array[i+1] = m_array[i];
        }
    }
    m_array[0] = elem;
    ++m_size;
}

template <typename T>
void Vector<T>::pop_front()
{   
    if(!m_size) return ;
    for(int i = 0 ; i < m_size - 1; ++i)
    {
        m_array[i] = m_array[i+1];
    }
    if(m_size <= m_cap / 2){
        m_cap = (m_cap / 2) + (m_cap % 2);
        copy(nullptr);
    }
    --m_size;
}

template <typename T>
void Vector<T>::clear()
{
    if(m_array != nullptr)
    {
        delete[] m_array;
    }
    m_size = 0;
    m_cap = 0;
}

template <typename T>
void Vector<T>::reserve(const int size)
{
    m_cap=size;
    copy();
}

template <typename T>
bool Vector<T>::empty() const
{
    return !m_size;
}

template <typename T>
size_t Vector<T>::size()
{
    return m_size;
}

template <typename T>
size_t Vector<T>::capacity()
{
    return m_cap;
}

template <typename T>
T& Vector<T>::at(size_t pos)
{
    try
    {
        return m_array[pos];
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

template <typename T>
bool Vector<T>::iterator::operator==(const Vector<T>::iterator& oth)
{
    return m_ptr == oth.m_ptr;
}

template <typename T>
bool Vector<T>::iterator::operator!=(const Vector<T>::iterator& oth)
{
    return m_ptr != oth.m_ptr;
}

template <typename T>
bool Vector<T>::iterator::operator>=(const Vector<T>::iterator& oth)
{
    return m_ptr >= oth.m_ptr;
}

template <typename T>
bool Vector<T>::iterator::operator>(const Vector<T>::iterator& oth)
{
    return m_ptr > oth.m_ptr;
}

template <typename T>
bool Vector<T>::iterator::operator<=(const Vector<T>::iterator& oth)
{
    return m_ptr <= oth.m_ptr;
}

template <typename T>
bool Vector<T>::iterator::operator<(const Vector<T>::iterator& oth)
{
    return m_ptr < oth.m_ptr;
}

template <typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator++()
{
    m_ptr += 1;
    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int)
{
    auto tmp = m_ptr;
    tmp += 1;
    return tmp;
}

template <typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator--()
{
    m_ptr -= 1;
    return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator--(int)
{
    auto tmp = m_ptr;
    tmp -= 1;
    return tmp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::find(Vector<T>::iterator beg, Vector<T>::iterator end, const T& value)
{
    while(beg != end){
        if( *beg == value )
        {
            return beg;
        }
        ++beg;
    }
    return end;
}

template <typename T>
T& Vector<T>::iterator::operator*()
{
    return *m_ptr;
}

template <typename T>
const T &Vector<T>::iterator::operator*() const
{
    return *m_ptr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return m_array;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return m_array + m_size;
}