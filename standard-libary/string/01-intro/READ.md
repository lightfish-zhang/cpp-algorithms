## std::endl与\n的区别
- cout << endl，除了往输出流中插入一个'\n'还有刷新输出流的作用. 
- cout << endl， 等价于: cout << '\n' << flush;

> 在没有必要刷新输出流的时候应尽量使用cout << '\n', 过多的endl是影响程序执行效率低下的因素之一