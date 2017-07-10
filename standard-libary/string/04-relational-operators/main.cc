#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int 
main()
{
    string big = "big", small = "small";
    string s1 = big;    // s1 is a copy of big
    cout 
        << "`big == small` is " <<  (big == small ? "true" : "false") << '\n'
        << "`big > small` is " <<  (big > small ? "true" : "false") << '\n'
        << "`big < small` is " <<  (big < small ? "true" : "false") << '\n'
        << "`big <= s1` is " <<  (big <= s1 ? "true" : "false") << endl
    ;
}

//关系操作符比较两个 string 对象时采用了和（大小写敏感的）字典排序相同的策略：