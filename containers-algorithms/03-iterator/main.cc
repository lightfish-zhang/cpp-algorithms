#include <iostream>
#include <string>
#include <vector>

using namespace std;

int
main()
{
    string word;
    vector<string> text;    // empty vector
    while (cin >> word) {
        text.push_back(word);     // append word to text
    }
    vector<int>::size_type size = text.size();
    for (vector<int>::size_type ix = 0; ix != size; ++ix)
        cout << text[ix];
    cout << endl;

     // equivalent loop using iterators to reset all the elements in ivec to 0
    for (vector<string>::iterator iter = text.begin(); iter != text.end(); ++iter)
        *iter = "xxx"; // write and read

    for (vector<string>::const_iterator iter = text.begin(); iter != text.end(); ++iter)
        cout << *iter; // only readly, it's const_iterator
    cout << endl;
}