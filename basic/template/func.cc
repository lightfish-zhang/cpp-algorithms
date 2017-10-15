#include<iostream>

using namespace std;

template<typename T> class A{
public:
    T g(T a,T b);
    A();
};

template<typename T> A<T>::A(){}

template<typename T> T A<T>::g(T a,T b){
    return a+b;
}

int main(void){
    A<int> a;
    cout<<a.g(2,3)<<endl;
    return 0;
}