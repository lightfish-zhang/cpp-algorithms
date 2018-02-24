#ifndef MY_VECTOR_H
#define MY_VECTOR_H


#include <iostream>

// 各种常用方法，如 std::max() 
#include <algorithm>

/*
STL的内存分配

根据C++的标准，STL的allocator，把对象的申请和释放分成了4步：
    第1步：申请内存空间，对应函数是allocator::allocate()
    第2步：执行构造函数，对应函数是allocator::construct()
    第3步：执行析构函数，对应函数是allocator::destroy()
    第4步：释放内存空间，对应函数是allocator::deallocate()
STL崇尚拷贝，你往容器里放东西或者从容器里取东西，都是要调用拷贝构造函数的。比如，你有一个对象a要插入到map里，过程是这样的：
map先申请一个结点的空间
调用拷贝构造函数初始化该结点
把新结点插入到map的红黑树中
*/
#include <memory>

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
    typedef T value_type; // 起别名
    typedef T* iterator; // 迭代器，指针类型
    typedef const T* const_iterator; // 指针指向的变量地址不能改，变量的值可以改
    typedef T* pointer; // 指针
    typedef const T* const_pointer; // 指针指向的变量地址不能改，变量的值可以改    

    /*
    引用的好处之一就是在函数调用时在内存中不会生成副本。

（1）在引用的使用中，单纯给某个变量取个别名是毫无意义的，引用的目的主要用于在函数参数传递中，解决大块数据或对象的传递效率和空间不如意的问题。

（2）用引用传递函数的参数，能保证参数传递中不产生副本，提高传递的效率，且通过const的使用，保证了引用传递的安全性。

（3）引用与指针的区别是，指针通过某个指针变量指向一个对象后，对它所指向的变量间接操作。程序中使用指针，程序的可读性差；而引用本身就是目标变量的别名，对引用的操作就是对目标变量的操作。

（4）使用引用的时机。流操作符<<和>>、赋值操作符=的返回值、拷贝构造函数的参数、赋值操作符=的参数、其它情况都推荐使用引用。
    */
    typedef T& reference;
    typedef const T& const_reference;

    // int普遍32位，size_t视平台而定，主流平台是64位
    typedef size_t size_type;

    MyVector();
    MyVector(size_type n, T value = T());
    MyVector(iterator begin, iterator end);
    ~MyVector();

    // copy control
    MyVector(const MyVector&);
    MyVector& operator=(const MyVector&);


    /*
     函数后面加const
        - 任何不会修改数据成员的函数都应该声明为const 类型。
        - 如果在编写const 成员函数时，不慎修改了数据成员，或者调用了其它非const 成员函数，编译器将指出错误，这无疑会提高程序的健壮性。
    */
    inline bool empty() const { return begin() == end(); }
    inline size_type size() const { return (size_type)(finish - start); }
    inline size_type capacity() const { return (size_type)(end_of_storage - start); }

    inline iterator begin() { return start; }
    inline iterator end() { return finish; }
    
    /* 重载[]，该对象本就不是一个数组指针，需要重载[]操作符，返回真正的元素地址 */
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
    static std::allocator<T> alloc; // object to get raw memory
};

// static class member needed to be defined outside of class
// 静态方法，内存分配器
template<typename T>
std::allocator<T> MyVector<T>::alloc;

// default constructor
template<typename T>
MyVector<T>::MyVector():start(NULL), finish(NULL), end_of_storage(NULL){}

template<typename T>
MyVector<T>::MyVector(size_type n, T value){
    start = alloc.allocate(n); // 申请一定数量的内存空间，返回首地址，start记录首地址
    end_of_storage = finish = start + n;

    // 在新空间上遍历
    for(iterator i = start; i!=finish; i++){
        alloc.construct(i, value); // 在i地址上执行一个变量的构建函数
    }
}

template<typename T>
MyVector<T>::MyVector(iterator begin, iterator end){
    // 指针相减，获得两个指针之间的元素数目
    const size_type n = end - begin;
    start = alloc.allocate(n); // 分配空间
    finish = end_of_storage = start + n;
    // 复制元素在未初始化过的地址上, 要执行构建函数，相当于 for(; begin != end; ++begin, (void) ++start) ::new (static_cast<void*>(std::addressof(*start))) Value(*begin);
    std::uninitialized_copy(begin, end, start);
}

template<typename T>
MyVector<T>::~MyVector(){
    ::destory(start, finish); // 执行析构函数

    alloc.deallocate(start, end_of_storage - start); // 释放内存空间
}

// copy
template<typename T>
MyVector<T>::MyVector(const MyVector& v){
    // 分配新的空间地址
    start = alloc.allocate(v.capacity());
    std::uninitialized_copy(v.start, v.finish, start);
    finish = start + (v.finish - v.start);
    end_of_storage = start + (v.end_of_storage - v.start);
}

// 同上
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
            std::uninitialized_copy(finish-n, finish, finish); // 复制元素在未初始化过的地址上，需要执行构建函数
            std::copy(position, finish - n, position+n); // 这里的复制更像是往后移动，被复制的内存地址是初始化过的
            std::fill_n(position, n, value); // std::fill_n函数的作用是：在[fist, fist + count)范围内填充指定值。
        }else{
            std::uninitialized_fill_n(finish, n - (finish - position), value);
            std::uninitialized_copy(position, finish, position + n);
            std::fill(position, finish, value); // std::fill函数的作用是：将一个区间的元素都赋予指定的值，即在[first, last)范围内填充指定值。
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

        // 把输入iterator所给出的一个内存范围内的对象数组的每个元素，逐个拷贝"构造"到前向的目标iterator所指的内存上。
        std::uninitialized_copy(start, finish, new_start);

        // "析构" 堆中的旧的对象
        ::destory(start, finish);
        // delete 旧的指针
        alloc.deallocate(start, size());

        // 刷新vector私有数据
        const size_type old_size = finish - start;
        start = new_start;
        finish = new_start + old_size;
        end_of_storage = new_start + n;
    }
}

#endif // MY_VECTOR_H
