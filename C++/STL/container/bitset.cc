// bitmap
//
// c.size()      // 返回大小（位数）
// c.count()     // 返回1的个数
// c.any()       // 返回是否有1
// c.none()      // 返回是否没有1
// c.set()       // 全都变成1
// c.set(p)      // 将第p + 1位变成1
// c.set(p, x)   // 将第p + 1位变成x
// c.reset()     // 全都变成0
// c.reset(p)    // 将第p + 1位变成0
// c.flip()      // 全都取反
// c.flip(p)     // 将第p + 1位取反
// c.to_ulong()  // 返回它转换为unsigned long的结果，如果超出范围则报错
// c.to_ullong() // 返回它转换为unsigned long long的结果，如果超出范围则报错
// c.to_string() // 返回它转换为string的结果


#include <iostream>
#include <bitset>
 
using namespace std;

int main ()
{
    bitset<5> bs(4);
    bs[1] = 1;
    cout << bs << endl;
    cout << '\n';

    return 0;   
}
 