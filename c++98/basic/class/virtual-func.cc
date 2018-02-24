#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/**
 *  定义动物类：Animal
 *  成员函数：eat()、move()
 */
class Animal
{
public:
    // 构造函数
    Animal(){cout << "Animal" << endl;}
    // 析构函数
	virtual ~Animal(){cout << "~Animal" << endl;}
    // 成员函数eat()
	virtual void eat(){cout << "Animal -- eat" << endl;}
    // 成员函数move()
	virtual void move(){cout << "Animal -- move" << endl;}
};

/**
 * 定义狗类：Dog
 * 此类公有继承动物类
 * 成员函数：父类中的成员函数
 */
class Dog : public Animal
{
public:
    // 构造函数
	Dog(){cout << "Dog" << endl;}
    // 析构函数
	virtual ~Dog(){cout << "~Dog" << endl;}
    // 成员函数eat()
	virtual void eat(){cout << "Dog -- eat" << endl;}
    // 成员函数move()
	virtual void move(){cout << "Dog -- move" << endl;}
};

int main(void)
{
    // 通过父类对象实例化狗类
    Animal *pDog = new Dog();

    // 由于没有数据成员，只打印出虚函数表指针的内存大小
    cout << sizeof(*pDog) << endl;

    // 调用成员函数
	pDog->eat();
    pDog->move();
    // 释放内存, new 需要手动 delete
    delete pDog;
    pDog = NULL;

    do{
        Dog dog;
        cout << sizeof(dog) << endl;
        // 调用成员函数
        dog.eat();
        dog.move();
    }while(0); // 作用域结束，自动回收对象，执行析构函数

    do{
        Animal a;
        cout << sizeof(a) << endl;
        // 调用成员函数
        a.eat();
        a.move();
    }while(0); // 作用域结束，自动回收对象，执行析构函数
    
	return 0;
}