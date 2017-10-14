#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <algorithm>
#include <memory>
#include <iostream>

template<typename T>
void destory(T * pointer){
    pointer->~T();
}

template<typename Tp>
void destory(Tp first, Tp last){
    for(Tp it = first; it != last; it++){
        destory(it);
    }
}

template<typename T>
class myVector{
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T* pointer;
    typedef const T* const_pointer; // 非常量数据的常量指针
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    myVector();
    myVector(size_type n, T value = T());
    myVector(iterator begin, iterator end);
    ~myVector();

    // copy control
    myVector(const myVector&);
    myVector& operator=(const myVector&);

    // 任何不会修改数据成员的函数都应该声明为const 类型。
    // 如果在编写const 成员函数时，不慎修改了数据成员，或者调用了其它非const 成员函数，编译器将指出错误，这无疑会提高程序的健壮性。
    inline bool empty() const { return begin() == end(); }
    inline size_type size() const { return (size_type)(finish - start); }
    inline size_type capacity() const { return (size_type)(end_of_storage - start); }

    inline iterator begin() { return start; }
    inline iterator end() { return finish; }
    
    inline reference operator[](size_type i){ return *(start + i); }

    void insert(iterator position, size_type n, const T& value);
    void push_back(const T& value);
    void pop_back();

    void erase(iterator first, iterator last);
    void clear();

    void reserve(size_type n);

protected:
    iterator start;
    iterator finish;
    iterator end_of_storage;

private:
    static std::allocator<T> alloc;
};

#endif // MY_VECTOR_H
