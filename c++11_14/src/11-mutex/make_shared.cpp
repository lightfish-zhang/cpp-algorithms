#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i)
{
    (*i)++;
}
int main()
{
    // 构造了一个 std::shared_ptr
    auto pointer = std::make_shared<int>(10);
    foo(pointer);
    std::cout << *pointer << std::endl;
}