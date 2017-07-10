#include <string>
#include <iostream>
#include <cctype>

using namespace std;

// using std::string;
// using std::cin;
// using std::cout;
// using std::endl;
// using std::isdigit;

int 
main()
{
    string str;
    cin >> str;
    string::size_type size = str.size();
    for (string::size_type ix = 0; ix != size; ++ix)
        cout 
            << str[ix] 
            << " is" << (isalnum(str[ix]) ? "" : " not") << " a letter or a digit.\n"
        ;
}