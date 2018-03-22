// C++11 提供了 constexpr 让用户显式的声明函数或对象构造函数在编译器会成为常数
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}

// 从 C++14 开始，constexptr 函数可以在内部使用局部变量、循环和分支等简单语句，例如下面的代码在 C++11 的标准下是不能够通过编译的：
constexpr int fibonacci2(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}