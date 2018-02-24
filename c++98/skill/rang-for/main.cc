#include <iostream>
#include <vector>

using namespace std;

int main(){
    int arr[] = {0,1,2,3,4,5};

    vector<int> a(arr, arr+6);

    for(auto i:a)
        cout << i;
    cout << endl;
    // 01234

    vector<int *> b;

    for(auto i:a)
        b.push_back(&i);

    for(auto i:b)
        cout << *i;   
    cout << endl;
    // 44444

    return 0;
}