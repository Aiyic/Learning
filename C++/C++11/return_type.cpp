#include<iostream>

auto fun(int x) -> double{
    return 1.2;
}

int main(){
    std::cout << fun(1) << std::endl;
}