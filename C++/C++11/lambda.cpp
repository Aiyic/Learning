#include<iostream>

int main(){
    auto lambda_f1=[](){return static_cast<double>(1);};
    std::cout << lambda_f1() << std::endl;
    
    int x=2;
    auto lambda_f2=[&](){ std::cout << ++x << std::endl;};
    // auto lambda_f2=[=](){ std::cout << ++x << std::endl;}; //值传递的捕获不能修改
    lambda_f2();
    std::cout << x << std::endl;
    
    int a = 123;
    auto lambda_f3 = [a]()mutable { std::cout << ++a << std::endl; }; 
    lambda_f3(); 
    std::cout << a << std::endl; 
}
    

