// if (init; condition) 初始化语句可以限定在if作用域内

#include <iostream>

using namespace std;

int main() {

    // if (init; condition)
    if (int a = 100; a < 101) {
        cout << a;
    }

}