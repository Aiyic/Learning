// dynamic_cast会运行时检查该转换是否类型安全，只在多态类型时合法，即该类至少具有一个虚拟方法
// 实现原理：对象需要有虚表，类型信息存于虚表，转型时会检查虚表中的类型信息
//          如果是向上转型，直接转换，同static_cast
//          如果是向下转型，检查类型信息，安全时(比如基类指针实际指向子类，此时该基类指针可以转型为子类)才可以转型

#include <iostream>  
using namespace std;

class A{
private:
    /* data */
public:
    A()= default;
    virtual ~A(){};
    virtual void print(){ cout << "A" << endl; };
};

class B: public A{
private:
    /* data */
public:
    B(){};
    virtual ~B(){};
    virtual void print(){ cout << "B" << endl; };
};

int main() {  

    // 指针间转型
    A* a = new A();
    B* b = new B();
    A* p = dynamic_cast<A*>(b); // 向下转型成功
    p->print();
    B* p2 = dynamic_cast<B*>(a); // 向上转型失败
    if(p2) p2->print();
    else cout << "err" << endl;

    // 对象引用转型
    A aa;
    B bb;
    A bba = dynamic_cast<A&>(bb);
    bba.print();
    try{
        B aab = dynamic_cast<B&>(aa); // aa是基类对象的引用，无法向下转型
        aab.print();
    }
    catch(exception &e){
        cout << "err" << endl;
    }

    A &ab = bb; // ab是一个对子类的引用，但类型是基类(?)
    B bab = dynamic_cast<B&>(ab); // ab实际引用的是子类对象，可以安全转型
    bab.print();

    return 0;  
} 
