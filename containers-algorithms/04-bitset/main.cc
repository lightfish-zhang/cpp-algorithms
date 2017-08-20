#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int
main(){
    // bitvec1 is smaller than the initializer
    bitset<16> bitvec1(0xffff);          // bits 0 ... 15 are set to 1
    // bitvec2 same size as initializer
    bitset<32> bitvec2(0xffff);          // bits 0 ... 15 are set to 1; 16 ... 31 are 0
    // on a 32-bit machine, bits 0 to 31 initialized from 0xffff
    bitset<128> bitvec3(0xffff);         // bits 32 through 127 initialized to zero

    string text("1100");        // reverse order, if bitset object 's value is from string object
    bitset<32> bitvec4(text);   // bits 0 1 are set to 0, bits 2 3 are set to 1

    // string 对象和 bitsets 对象之间是反向转化的：
    // string 对象的最右边字符（即下标最大的那个字符）用来初始化 bitset 对象的低阶位（即下标为 0 的位）。当用 string 对象初始化 bitset 对象时，记住这一差别很重要
    string str("1111111000000011001101");
    bitset<32> bitvec5(str, 5, 4); // bitvec5 的从 3 到 0 的二进制位置为 1100, 也就是字符串的str[5]到str[5+4], bitvec5的其他位为0
    bitset<32> bitvec6(str, str.size() - 4);     // use last 4 characters


    bitset<32> bitvec; // 32 bits, all zero
    bool is_set = bitvec.any();            // false, all bits are zero
    bool is_not_set = bitvec.none();       // true, all bits are zero

    size_t bits_set = bitvec.count(); // returns number of bits that are on(1) 该操作返回置为 1 的二进制位的个数
    size_t sz = bitvec.size(); // returns 32  返回 bitset 对象中二进制位的个数


    // assign 1 to even numbered bits  偶数下标的位都置为 1
    for (int index = 0; index != 32; index += 2)
        bitvec[index] = 1; // or `bitvec.set(index);`

    

    bitvec.reset(); // set all the bits to 0.
    bitvec.set();   // set all the bits to 1


    bitvec.flip(0);   // reverses value of first bit
    bitvec[0].flip(); // also reverses the first bit
    bitvec.flip();    // reverses value of all bits


    // to_ulong 操作返回一个 unsigned long 值，该值与 bitset 对象的位模式存储值相同。
    // 仅当 bitset 类型的长度小于或等于 unsigned long 的长度时，才可以使用 to_ulong 操作
    unsigned long ulong = bitvec3.to_ulong();
    cout << "ulong = " << ulong << endl;


    // 可以用输出操作符输出 bitset 对象中的位模式
    bitset<32> bitvec7(0xffff); // bits 0 ... 15 are set to 1; 16 ... 31 are 0
    cout << "bitvec7: " << bitvec7 << endl;
    // will print:
    // bitvec7: 00000000000000001111111111111111


    // bitset 类也支持内置的位操作符

}