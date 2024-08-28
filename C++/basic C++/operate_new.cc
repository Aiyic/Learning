/*

A p = (A)::operator new(sizeof(A));

::operator new(sizeof(A)) 调用全局作用域下的 operator new 函数，该函数用于动态分配内存。sizeof(A) 表示要分配的内存大小，这里是类型 A 的大小。
(A*) 将分配的内存强制转换为指向类型 A 的指针。
最终，p 是一个指向类型 A 的指针，指向动态分配的内存块。
new(p) A();

这是使用定位 new 运算符在预分配的内存上构造对象。
new(p) 表示在地址 p 指向的内存上构造对象。这是所谓的 "定位 new"，它不会分配新的内存，而是在预先分配的内存上构造对象。
A() 是调用 A 类的默认构造函数来初始化对象。

*/

#include <iostream>  
class A {  
public:  
    A() {  
        std::cout<<"call A constructor"<<std::endl;  
    }  
  
    ~A() {  
        std::cout<<"call A destructor"<<std::endl;  
    }  
        
    void* operator new(size_t size) {  
        std::cout<<"call A::operator new"<<std::endl;  
        return malloc(size);  
    } 
};  
int main() {  

    A* p = (A*)::operator new(sizeof(A)); //分配  
    ::new(p) A(); //构造  
    p->~A(); //析构  
    ::operator delete(p); //释放  
  
    std::cout<<"****************"<<std::endl;  

    A* p2 = new A();  
    delete p2; 

    return 0;  
} 
