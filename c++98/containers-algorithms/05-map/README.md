# map容器

## 定义

map 是键－值对的集合。map 类型通常可理解为关联数组（associative array）：可使用键作为下标来获取一个值，正如内置数组类型一样。而关联的本质在于元素的值与某个特定的键相关联，而并非通过元素在数组中的位置来获取。

- `map<k, v> m` 创建一个名为 m 的空 map 对象，其键和值的类型分别为 k 和 v
- `map<k, v> m(m2)` 创建 m2 的副本 m，m 与 m2 必须有相同的键类型和值类型
- `map<k, v> m(b, e)` 创建 map 类型的对象 m，存储迭代器 b 和 e 标记的范围内所有元素的副本。元素的类型必须能转换为 `pair<const k, v>`

## 了解pair类型

- `pair<T1, T2> p1` 创建一个空的 pair 对象，它的两个元素分别是 T1 和 T2 类型，采用值初始化
- `pair<T1, T2> p1(v1, v2)` 创建一个 pair 对象，它的两个元素分别是 T1 和 T2 ，其中 first 成员初始化为 v1，而 second 成员初始化为 v2
- `make_pair(v1, v2)` 以 v1 和 v2 值创建一个新 pair 对象，其元素类型分别是 v1 和 v2 的类型
- `p1 < p2` 两个 pair 对象之间的小于运算，其定义遵循字典次序：如果 p1.first < p2.first 或者 !(p2.first < p1.first) && p1.second < p2.second，则返回 true
- `p1 == p2` 如果两个 pair 对象的 first 和 second 成员依次相等，则这两个对象相等。该运算使用其元素的 == 操作符
- `p.first` 返回 p 中名为 first 的（公有）数据成员
- `p.second` 返回 p 的名为 second 的（公有）数据成员

## 使用下标访问 map 对象

- 如同其他下标操作符一样，map 的下标也使用索引（其实就是键）来获取该键所关联的值。
- 如果该键已在容器中，则 map 的下标运算与 vector 的下标运算行为相同：返回该键所关联的值。
- 只有在所查找的键不存在时，map 容器才为该键创建一个新的元素，并将它插入到此 map 对象中。此时，所关联的值采用值初始化：类类型的元素用默认构造函数初始化，而内置类型的元素初始化为 0。

实例:

```
     map <string, int> word_count; // empty map

     // insert default initialzed element with key Anna; then assign 1 to its value
     word_count["Anna"] = 1;

```

将发生一下步骤

- word_count is searched for the element whose key is Anna. The element is not found.
在 word_count 中查找键为 Anna 的元素，没有找到。
- 将一个新的键－值对插入到 word_count 中。它的键是 const string 类型的对象，保存 Anna。而它的值则采用值初始化，这就意味着在本例中值为 0。
- 将这个新的键－值对插入到 word_count 中。
- 读取新插入的元素，并将它的值赋为 1。 


## map::insert 的使用

- `m.insert(e)` e 是一个用在 m 上的 value_type 类型的值。如果键（e.first）不在 m 中，则插入一个值为 e.second 的新元素；如果该键在 m 中已存在，则保持 m 不变。该函数返回一个 pair 类型对象，包含指向键为 e.first 的元素的 map 迭代器，以及一个 bool 类型的对象，表示是否插入了该元素
- `m.insert(beg, end)` beg 和 end 是标记元素范围的迭代器，其中的元素必须为 m.value_type 类型的键－值对。对于该范围内的所有元素，如果它的键在 m 中不存在，则将该键及其关联的值插入到 m。返回 void 类型
- `m.insert(iter, e)` e 是一个用在 m 上的 value_type 类型的值。如果键（e.first）不在 m 中，则创建新元素，并以迭代器 iter 为起点搜索新元素存储的位置。返回一个迭代器，指向 m 中具有给定键的元素

example:

```cpp

word_count.insert(map<string, int>::value_type("Anna", 1)); 
word_count.insert(make_pair("Anna", 1));

```

## 遍历

```cpp
    map<string, int>::const_iterator map_it = word_count.begin();
     // for each element in the map
    while (map_it != word_count.end()) {
        // print the element key, value pairs
        cout << map_it->first << " occurs "
            << map_it->second << " times" << endl;
        ++map_it; // increment iterator to denote the next element
    }
```

## 删除

```cpp
    string removal_word("a");
         // erase of a key returns number of elements removed
    if (word_count.erase(removal_word))
        cout << "ok: " << removal_word << " removed\n";
    else 
        cout << "oops: " << removal_word << " not found!\n";
```

## 查找

```cpp
    // find two times
    if (word_count.count("b"))
        cout << "b occurs "
            << word_count["b"] << " times" << endl;
    
    // find one times, suggest!
    map<string,int>::iterator it = word_count.find("c");
    if (it != word_count.end())
        cout << "c occurs "
            << it->second << " times" << endl;
```