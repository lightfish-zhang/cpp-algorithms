# 顺序容器

## 定义

- 头文件

```cpp
#include <vector>
#include <list>
#include <deque>
```

- 所有的容器都是类模板（第 3.3 节）。要定义某种特殊的容器，必须在容器名后加一对尖括号，尖括号里面提供容器中存放的元素的类型

```cpp
vector<string>    svec;       // empty vector that can hold strings
list<int>         ilist;      // empty list that can hold ints
deque<double>     items;      // empty deque that holds Sales_items
```

- 所有容器类型都定义了默认构造函数，用于创建指定类型的空容器对象。默认构造函数不带参数。
- 为了使程序更清晰、简短，容器类型最常用的构造函数是默认构造函数。在大多数的程序中，使用默认构造函数能达到最佳运行时性能，并且使容器更容易使用。

## 容器元素的初始化

- 容器构造函数

```cpp
C<T> c;     //创建一个名为 c 的空容器。C 是容器类型名，如 vector，T 是元素类型，如 int 或 string 适用于所有容器。
C c(c2);    //创建容器 c2 的副本 c；c 和 c2 必须具有相同的容器类型，并存放相同类型的元素。适用于所有容器。
C c(b, e);  //用 n 个值为 t 的元素创建容器 c，其中值 t 必须是容器类型 C 的元素类型的值，或者是可转换为该类型的值。`只适用于顺序容器!`
C c(n);     //创建有 n 个值初始化（value-initialized）元素的容器 c。`只适用于顺序容器!`
```

## 将一个容器初始化为另一个容器的副本

- 当不使用默认构造函数，而是用其他构造函数初始化顺序容器时，必须指出该容器有多少个元素，并提供这些元素的初值。同时指定元素个数和初值的一个方法是将新创建的容器初始化为一个同类型的已存在容器的副本
- 将一个容器复制给另一个容器时，类型必须匹配：容器类型和元素类型都必须相同。

```cpp
vector<int>     ivec;
vector<int>     ivec2(ivec);   // ok: ivec is vector<int>
list<int>       ilist(ivec);   // error: ivec is not list<int>
vector<double>  dvec(ivec); // error: ivec holds int not double
```

## 初始化为一段元素的副本

- 尽管不能直接将一种容器内的元素复制给另一种容器，但系统允许通过传递一对迭代器间接实现该实现该功能。使用迭代器时，不要求容器类型相同。容器内的元素类型也可以不相同，只要它们相互兼容，能够将要复制的元素转换为所构建的新容器的元素类型，即可实现复制。
- 迭代器标记了要复制的元素范围，这些元素用于初始化新容器的元素。迭代器标记出要复制的第一个元素和最后一个元素。采用这种初始化形式可复制不能直接复制的容器。更重要的是，可以实现复制其他容器的一个子序列

```cpp
// initialize slist with copy of each element of svec
vector<string>    svec;
list<string> slist(svec.begin(), svec.end());

// find midpoint in the vector
vector<string>::iterator mid = svec.begin() + svec.size()/2;

// initialize front with first half of svec: The elements up to but not including *mid
deque<string> front(svec.begin(), mid);
// initialize back with second half of svec: The elements *mid through end of svec
deque<string> back(mid, svec.end());
```

- 回顾一下指针，我们知道指针就是迭代器，因此允许通过使用内置数组中的一对指针初始化容器也就不奇怪了

```cpp
char *words[] = {"stately", "plump", "buck", "mulligan"};

// calculate how many elements in words
size_t words_size = sizeof(words)/sizeof(char *);

// use entire array to initialize words2
list<string> words2(words, words + words_size);
```

- 这里，使用 sizeof计算数组的长度。将数组长度加到指向第一个元素的指针上就可以得到指向超出数组末端的下一位置的指针。通过指向第一个元素的指针`words`和指向数组中最后一个元素的下一位置的指针，实现了`words2`的初始化。其中第二个指针提供停止复制的条件，其所指向的位置上存放的元素并没有复制。

## 分配和初始化指定数目的元素

- 创建顺序容器时，可显式指定容器大小和一个（可选的）元素初始化式。容器大小可以是常量或非常量表达式，元素初始化则必须是可用于初始化其元素类型的对象的值

```cpp
const list<int>::size_type list_size = 64;
list<string> slist(list_size, "element"); // 64 strings, each is "element"
```

- 创建容器时，除了指定元素个数，还可选择是否提供元素初始化式。我们也可以只指定容器大小

```cpp
list<int> ilist(list_size); // 64 elements, each initialized to 0
// svec has as many elements as the return value from get_word_count
extern unsigned get_word_count(const string &file_name);
vector<string> svec(get_word_count("Chimera"));
```

- 不提供元素初始化式时，标准库将为该容器实现值初始化。采用这种类型的初始化，元素类型必须是内置或复合类型，或者是提供了默认构造函数的类类型。如果元素类型没有默认构造函数，则必须显式指定其元素初始化式。
- 接受容器大小做形参的构造函数只适用于顺序容器，而关联容器不支持这种初始化。


## 容器的容器

- 因为容器受容器元素类型的约束，所以可定义元素是容器类型的容器。例如，可以定义 vector 类型的容器 lines，其元素为 string 类型的 vector 对象：

```cpp
// note spacing: use ">>" not ">>" when specifying a container element type
vector< vector<string> > lines; // vector of vectors
```

- 注意，在指定容器元素为容器类型时，必须如下使用空格

```cpp
vector< vector<string> > lines; // ok: space required between close >
vector< vector<string>> lines; // error: >> treated as shift operator
```

- 必须用空格隔开两个相邻的 > 符号，以示这是两个分开的符号，否则，系统会认为 >> 是单个符号，为右移操作符，并导致编译时错误。

