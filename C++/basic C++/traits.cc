#include<iostream>

// 自定义测试类型
class testA{
public:
    testA(){
        std::cout << "testA constructor" << std::endl;
    }
};

template <class T, class... Args>
class my_vector {
public:
    // 迭代器的声明，嵌套类
    class iterator {
    public:
        typedef T value_type;
        // ...
    };
// ...
};

// 萃取类模板
template<class IterT>
struct my_iterator_traits {
    typedef typename IterT::value_type value_type;
};

int main(){
    my_iterator_traits<my_vector<testA>::iterator>::value_type val;
    testA val2;
}