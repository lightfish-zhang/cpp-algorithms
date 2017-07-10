#define _GLIBCXX_USE_CXX11_ABI 1

#include <string>
#include <iostream>
// using declarations states our intent to use these names from the namespace std
using std::cin;
using std::string;
int main()
{
    string s;       // ok: string is now a synonym for std::string
    cin >> s;       // ok: cin is now a synonym for std::cin
//    cout << s;      // error: no using declaration; we must use full name
    std::cout << s; // ok: explicitly use cout from namepsace std
}
