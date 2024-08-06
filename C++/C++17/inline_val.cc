// 内联变量允许我们在头文件中定义变量，而无需担心多重定义错误。

#include <iostream>
#include "inline_val.hpp"

extern inline int myVariable;  // 外部声明

int main() {
    std::cout << myVariable << std::endl;  // 输出: 42
    return 0;
}