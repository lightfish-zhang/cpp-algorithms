## nullptr与constexpr

### nullptr

- `nullptr`出现的目的是替代`NULL`
- 传统 C++ 会把 NULL、0 视为同一种东西，这取决于编译器如何定义 NULL，有些编译器会将 NULL 定义为 ((void*)0)，有些则会直接将其定义为 0。
- 这些问题将导致`C++`重载特性发生混乱，如：

```cpp
void foo(char *);
void foo(int);
```

- 如果 NULL 又被定义为了 0 那么 foo(NULL); 这个语句将会去调用 foo(int)，从而导致代码违反直观


### constexpr

- `constexpr`的作用类似宏定义，可以让编译器在编译期间就把该函数计算出常量，替换所在的代码位置

- C++ 本身已经具备了常数表达式的概念，比如 1+2, 3*4 这种表达式总是会产生相同的下结果并且没有任何副作用。如果编译器能够在编译时就把这些表达式直接优化并植入到程序运行时，将能增加程序的性能。

```cpp
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}
```