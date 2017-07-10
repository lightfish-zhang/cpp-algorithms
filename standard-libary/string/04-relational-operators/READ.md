## The string Relational Operators 
>string 关系操作符

- string 类定义了几种关系操作符用来比较两个 string 值的大小。这些操作符实际上是比较每个 string
- == 操作符比较两个 string 对象，如果它们相等，则返回 true。两个 string 对象相等是指它们的长度相同，且含有相同的字符。标准库还定义了 != 操作符来测试两个 string 对象是否不等。
- 关系操作符 <，<=，>，>= 分别用于测试一个 string 对象是否小于、小于或等于、大于、大于或等于另一个 string 对象
- 关系操作符比较两个 string 对象时采用了和（大小写敏感的）字典排序相同的策略
    + 如果两个 string 对象长度不同，且短的 string 对象与长的 string 对象的前面部分相匹配，则短的 string 对象小于长的 string 对象。
    + 如果 string 对象的字符不同，则比较第一个不匹配的字符。