#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int 
main()
{
    string str("some string");
    string::size_type size = str.size();
    for (string::size_type ix = 0; ix != size; ++ix)
        cout << str[ix] << endl;

    for (string::size_type ix = 0; ix != size; ++ix)
        str[ix] = '*';
    cout << str << endl;
}