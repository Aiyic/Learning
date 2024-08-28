#include<iostream>
#include<functional>

class base{
public:
    int f1(int x){
        return 123;
    }
};

int f2(int x, double &y, bool z){
    y=2.2;
    return 123;
}

int main(){
    int x=1;
    double y=1.2;
    bool z=true;

    auto f1_bing = std::bind(&base::f1,std::placeholders::_1,x);
    auto f2_bing = std::bind(f2,std::placeholders::_1,std::ref(y),std::placeholders::_2);

    std::cout << f1_bing(base(),x) << std::endl;
    std::cout << f2_bing(x,z) << ' ' << y << std::endl;

}