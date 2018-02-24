#include <map>
#include <iostream>

using namespace std;

int main(){
    // 插入
     // count number of times each word occurs in the input
     map<string, int> word_count; // empty map from string to int
     string word;
     while (cin >> word) {
         // inserts element with key equal to word and value 1;
         // if word already in word_count, insert does nothing
         pair<map<string, int>::iterator, bool> ret = word_count.insert(make_pair(word, 1));
         if (!ret.second)          // word already in word_count
             ++ret.first->second;  // increment counter
     }

    // 删除
    string removal_word("a");
         // erase of a key returns number of elements removed
    if (word_count.erase(removal_word))
        cout << "ok: " << removal_word << " removed\n";
    else 
        cout << "oops: " << removal_word << " not found!\n";

    //遍历
    map<string, int>::const_iterator map_it = word_count.begin();
     // for each element in the map
    while (map_it != word_count.end()) {
        // print the element key, value pairs
        cout << map_it->first << " occurs "
            << map_it->second << " times" << endl;
        ++map_it; // increment iterator to denote the next element
    }

    // 查找
    // find two times
    if (word_count.count("b"))
        cout << "b occurs "
            << word_count["b"] << " times" << endl;
    

    // find one times, suggest!
    map<string,int>::iterator it = word_count.find("c");
    if (it != word_count.end())
        cout << "c occurs "
            << it->second << " times" << endl;


}
