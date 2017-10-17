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
class MyVector{
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T* pointer;
    typedef const T* const_pointer; // 非常量数据的常量指针
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    MyVector();
    MyVector(size_type n, T value = T());
    MyVector(iterator begin, iterator end);
    ~MyVector();

    // copy control
    MyVector(const MyVector&);
    MyVector& operator=(const MyVector&);

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

// static class member needed to be defined outside of class
template<typename T>
std::allocator<T> MyVector<T>::alloc;

template<typename T>
MyVector<T>::MyVector():start(NULL), finish(NULL), end_of_storage(NULL){}

template<typename T>
MyVector<T>::MyVector(size_type n, T value){
    start = alloc.allocate(n); // 数量，分配空间
    end_of_storage = finish = start + n;

    for(iterator i = start; i!=finish; i++){
        alloc.construct(i, value); // 构建
    }
}

template<typename T>
MyVector<T>::MyVector(iterator begin, iterator end){
    // 指针相减，获得两个指针之间的元素数目
    const size_type n = end - begin;
    start = alloc.allocate(n); // 分配空间
    finish = end_of_storage = start + n;
    std::uninitialized_copy(begin, end, start); // 构建 等同for (; begin != end; ++begin, (void) ++start) ...
}


#endif // MY_VECTOR_H
