// 要理解的重要概念是引用只是对象的另一名字。
int ival = 1024;
int &refVal = ival; // ok: refVal refers to ival
int &refVal2;       // error: a reference must be initialized
int &refVal3 = 10;  // error: initializer must be an object

//可以在一个类型定义行中定义多个引用。必须在每个引用标识符前添加“&”符号：
int i = 1024, i2 = 2048;
int &r = i, r2 = i2;      // r is a reference, r2 is an int
int i3 = 1024, &ri = i3;  // defines one object, and one reference
int &r3 = i3, &r4 = i2;   // defines two references

//const 引用是指向 const 对象的引用：
const int ival = 1024;
const int &refVal = ival;      // ok: both reference and object are const
int &ref2 = ival;              // error: non const reference to a const object