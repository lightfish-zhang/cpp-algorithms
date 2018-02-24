## 标准库 vector 类型

### 本例代码执行如下

```shell
➜  ./main.out
# input
first
second
third
# press `Ctrl+d` to end the stdin
# then output
firstsecondthird

```

### 定义

- 使用前的声明

```cpp
#include <vector>
using std::vector;
```

- vector 是同一种类型的对象的集合，每个对象都有一个对应的整数索引值。和 string 对象一样，标准库将负责管理与存储元素相关的内存。我们把 vector 称为容器，是因为它可以包含其他对象。
- vector 是一个类模板（class template）。使用模板可以编写一个类定义或函数定义，而用于多个不同的数据类型。因此，我们可以定义保存 string 对象的 vector，或保存 int 值的 vector，又或是保存自定义的类类型对象（如 Sales_items 对象）的 vector。
- vector 不是一种数据类型，而只是一个类模板，可用来定义任意多种数据类型。vector 类型的每一种都指定了其保存元素的类型。因此，`vector<int>` 和 `vector<string>` 都是数据类型。

### 关键概念

- vector 对象（以及其他标准库容器对象）的重要属性就在于可以在运行时高效地添加元素。因为 vector 增长的效率高，在元素值已知的情况下，最好是动态地添加元素。

### Ways to Initialize a vector

```cpp
vector<T> v1;           //vector 保存类型为 T 对象。默认构造函数 v1 为空。
vector<T> v2(v1);       //v2 是 v1 的一个副本。
vector<T> v3(n, i);     //v3 包含 n 个值为 i 的元素。
vector<T> v4(n);        //v4 含有值初始化的元素的 n 个副本。
```

### 创建确定个数的元素

- 若要创建非空的 vector 对象，必须给出初始化元素的值。当把一个 vector 对象复制到另一个 vector 对象时，新复制的 vector 中每一个元素都初始化为原 vectors 中相应元素的副本。但这两个 vector 对象必须保存同一种元素类型

```cpp
vector<int> ivec1;           // ivec1 holds objects of type int
vector<int> ivec2(ivec1);    // ok: copy elements of ivec1 into ivec2
vector<string> svec(ivec1);  // error: svec holds strings, not ints
```

- 可以用元素个数和元素值对 vector 对象进行初始化。构造函数用元素个数来决定 vector 对象保存元素的个数，元素值指定每个元素的初始值

```cpp
vector<int> ivec4(10, -1);       // 10 elements, each initialized to -1
vector<string> svec(10, "hi!");  // 10 strings, each initialized to "hi!"
```