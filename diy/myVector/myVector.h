#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <algorithm>
#include <memory>
#include <iostream>

// 主动执行析构函数
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

template<typename T>
MyVector<T>::~MyVector(){
    ::destory(start, finish);

    alloc.deallocate(start, end_of_storage - start);
}

// copy
template<typename T>
MyVector<T>::MyVector(const MyVector& v){
    start = alloc.allocate(v.capacity());
    std::uninitialized_copy(v.start, v.finish, start);
    finish = start + (v.finish - v.start);
    end_of_storage = start + (v.end_of_storage - v.start);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& v){
    start = alloc.allocate(v.capacity());
    std::uninitialized_copy(v.start, v.finish, start);
    finish = start + (v.finish - v.start);
    end_of_storage = start + (v.end_of_storage - v.start);
    return *this;
}

// 在 position 的位置上插入n个相同的值
template<typename T>
void MyVector<T>::insert(iterator position, size_type n, const T& value){
    // check whether is memory enough 
    if(n <= end_of_storage - finish){
        // memory enough, append
        if(n <= finish - position){
            std::uninitialized_copy(finish-n, finish, finish);
            std::copy(position, finish - n, position+n);
            std::fill_n(position, n, value);
        }else{
            std::uninitialized_fill_n(finish, n - (finish - position), value);
            std::uninitialized_copy(position, finish, position + n);
            std::fill(position, finish, value);
        }
    }else{
        // reallocate
        pointer new_start(NULL), new_finish(NULL);
        size_type old_size = end_of_storage - start;
        size_type new_size = old_size + std::max(old_size, n); //最小翻倍，如果新分配超出两倍，按新分配的大小
        new_start = alloc.allocate(new_size);

        // copy older data to new space
        new_finish = std::uninitialized_copy(start, position, new_start);
        std::uninitialized_fill_n(new_finish, n, value);
        new_finish += n;
        new_finish = std::uninitialized_copy(position, finish, new_finish);

        alloc.deallocate(start, end_of_storage - start);

        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + new_size;
    }
}

template<typename T>
void MyVector<T>::push_back(const T &value){
    insert(end(), 1, value);
}

template<typename T>
void MyVector<T>::pop_back(){
    // 主动执行析构函数, 这里不用回收内存
    alloc.destroy(--finish);
}

template<typename T>
void MyVector<T>::erase(iterator first, iterator last)
{
    iterator old_finish = finish;
    finish = std::copy(last, finish, first);

    // 主动执行析构函数
    ::destory(finish, old_finish);
}

template<typename T>
void MyVector<T>::clear()
{
    erase(start, finish);
}

template<typename T>
void MyVector<T>::reserve(size_type n)
{
    if(capacity() < n){
        iterator new_start = alloc.allocate(n);

        // 把输入iterator所给出的一个内存范围内的对象数组的每个元素，逐个拷贝构造到前向的目标iterator所指的内存上。
        std::uninitialized_copy(start, finish, new_start);

        // 析构
        ::destory(start, finish);
        alloc.deallocate(start, size());

        const size_type old_size = finish - start;
        start = new_start;
        finish = new_start + old_size;
        end_of_storage = new_start + n;
    }
}

#endif // MY_VECTOR_H
