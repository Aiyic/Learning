#include <iostream>
#include <memory>
 
using namespace std;
 
class A : public enable_shared_from_this<A>
{
public:
    A(){}
    void set(){
        conn = this->shared_from_this();
    }
    int a;
    weak_ptr<A> conn;
};


int main(){
    std::shared_ptr<A> ptr = std::make_shared<A>();
    cout << ptr.use_count() << endl;  // 1
    std::shared_ptr<A> ptr1 = ptr->conn.lock();
 
    if (!ptr1)
    {
        std::cout << "null\n";        // null
    }
 
    ptr->set();
    cout << ptr.use_count() << endl;  // 1
 
    ptr1 = ptr->conn.lock();
 
    cout << ptr.use_count() << endl;  // 2
}