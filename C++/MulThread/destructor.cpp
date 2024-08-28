#include<bits/stdc++.h>

class Base{
public:
    void dosth(){
        std::cout << "Base doing" << std::endl;
    }  
    virtual void dosth2(){
        std::cout << "virtual Base doing" << std::endl;
    }
    ~Base()
    {
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base{
public:
    void dosth(){
        std::cout << "Derived doing" << std::endl;
    }    
    virtual void dosth2(){
        std::cout << "virtual Derived doing" << std::endl;
    }
    ~Derived()
    {
        std::cout << "Derived destructor" << std::endl;
    }
};

void virtual_destructor(){
    {
        std::cout << "--------------------" << std::endl;
        std::shared_ptr<Base> sharedA(new Derived);
        sharedA->dosth();
        sharedA->dosth2();
    }

    std::cout << "--------------------" << std::endl;
    Base * a = new Derived;
    a->dosth();
    a->dosth2();
    delete a;
}

int main(){
    virtual_destructor();
    return 0;
}
