#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;


int main()
{
    string st("The expense of spirit\n");
    cout 
        << "it is " << (st.empty() ? "empty" : "not empty") << '\n'
        << "The size of " << st << "is " << st.size()
        << " characters, including the newline" << endl
    ;
    return 0;
}