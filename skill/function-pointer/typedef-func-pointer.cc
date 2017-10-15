#include <iostream>

static int add(int x, int y){
    return (x+y);
}

int
main()
{
    typedef int (*pfun)(int x, int y);
    pfun p = add;
    int ret = p(1,2);
    std::cout << ret << std::endl;
    return 0;
}

/*
函数名就是函数指针？
*/