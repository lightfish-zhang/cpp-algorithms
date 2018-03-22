# Lambda 表达式

- 基本语法

```
[捕获列表](参数列表) mutable(可选) 异常属性 -> 返回类型 {
    // 函数体
}
```

## 捕获列表

- 值捕获

与参数传值类似，值捕获的前期是变量可以拷贝，不同之处则在于，被捕获的变量在 lambda 表达式被创建时拷贝，而非调用时才拷贝：

```cpp
void learn_lambda_func_1() {
    int value_1 = 1;
    auto copy_value_1 = [value_1] {
        return value_1;
    };
    value_1 = 100;
    auto stored_value_1 = copy_value_1();
    // 这时, stored_value_1 == 1, 而 value_1 == 100.
    // 因为 copy_value_1 在创建时就保存了一份 value_1 的拷贝
}
```

- 引用捕获

```cpp
void learn_lambda_func_2() {
    int value_2 = 1;
    auto copy_value_2 = [&value_2] {
        return value_2;
    };
    value_2 = 100;
    auto stored_value_2 = copy_value_2();
    // 这时, stored_value_2 == 100, value_1 == 100.
    // 因为 copy_value_2 保存的是引用
}
```

- 隐式捕获

手动书写捕获列表有时候是非常复杂的，这种机械性的工作可以交给编译器来处理，这时候可以在捕获列表中写一个 & 或 = 向编译器声明采用 引用捕获或者值捕获.

总结一下，捕获提供了lambda 表达式对外部值进行使用的功能，捕获列表的最常用的四种形式可以是：

+ [] 空捕获列表
+ [name1, name2, ...] 捕获一系列变量
+ [&] 引用捕获, 让编译器自行推导捕获列表
+ [=] 值捕获, 让编译器执行推导应用列表


## 尾置返回类型

C++11 提供了一种新的书写返回值的方式，那就是将返回类型尾置。尾置的返回类型允许我们在参数列表之后申明返回的类型

```cpp
// 两者一样作用
int (*)[5]func(int value) {
}

auto func(int value) -> int (*)[5] {
}
```

```cpp
template <typename T>
auto &getItem(T begin, T end) -> decltype(*begin) {
    return *begin; // 返回序列中一个元素的引用
}
```


