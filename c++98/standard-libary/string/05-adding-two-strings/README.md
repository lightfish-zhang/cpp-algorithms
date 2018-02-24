- 当进行 string 对象和字符串字面值混合连接操作时，+ 操作符的左右操作数必须至少有一个是 string 类型的：

```cpp
string s1 = "hello";   // no punctuation
string s2 = "world";
string s3 = s1 + ", ";           // ok: adding a string and a literal
string s4 = "hello" + ", ";      // error: no string operand
string s5 = s1 + ", " + "world"; // ok: each + has string operand
string s6 = "hello" + ", " + s2; // error: can't add string literals
```