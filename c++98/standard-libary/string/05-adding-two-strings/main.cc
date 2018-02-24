#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int 
main()
{
     string s1("hello, ");
     string s2("world");
     string s3 = s1 + s2;   // s3 is hello, world
     cout << s3 << endl;
}