#include <cstdlib>
#include <iostream>
#include <string>

template <typename T, int MAXSIZE> class Stack { // MAXSIZE由用户创建对象时自行设置
private:
  T elems[MAXSIZE]; // 包含元素的数组
  int numElems;     // 元素的当前总个数
public:
  Stack();              //构造函数
  void push(T const &); //压入元素
  void pop();           //弹出元素
  T top() const;        //返回栈顶元素
  bool empty() const {  // 返回栈是否为空
    return numElems == 0;
  }
  bool full() const { // 返回栈是否已满
    return numElems == MAXSIZE;
  }
};

template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack() : numElems(0) { // 初始时栈不含元素
  // 不做任何事情
}

template <typename T, int MAXSIZE> void Stack<T, MAXSIZE>::push(T const &elem) {
  if (numElems == MAXSIZE) {
    throw std::out_of_range("Stack<>::push(): stack is full");
  }
  elems[numElems] = elem; // 附加元素
  ++numElems;             // 增加元素的个数
}

template <typename T, int MAXSIZE> void Stack<T, MAXSIZE>::pop() {
  if (numElems <= 0) {
    throw std::out_of_range("Stack<>::pop(): empty stack");
  }
  --numElems; // 减少元素的个数
}

template <typename T, int MAXSIZE> T Stack<T, MAXSIZE>::top() const {
  if (numElems <= 0) {
    throw std::out_of_range("Stack<>::top(): empty stack");
  }
  return elems[numElems - 1]; // 返回最后一个元素
}

int main() {
  try {
    Stack<int, 20> int20Stack;          // 可以存储20个int元素的栈
    Stack<int, 40> int40Stack;          // 可以存储40个int元素的栈
    Stack<std::string, 40> stringStack; // 可存储40个string元素的栈

    // 使用可存储20个int元素的栈
    int20Stack.push(7);
    std::cout << int20Stack.top() << std::endl; // 7
    int20Stack.pop();

    // 使用可存储40个string的栈
    stringStack.push("hello");
    std::cout << stringStack.top() << std::endl; // hello
    stringStack.pop();
    stringStack.pop(); // Exception: Stack<>::pop<>: empty stack
    return 0;
  } catch (std::exception const &ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
    return EXIT_FAILURE; // 退出程序且有ERROR标记
  }
}