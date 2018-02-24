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
}