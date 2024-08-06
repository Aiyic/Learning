#include<iostream>



/*定义和声明一个多参数模板函数，递归方式展开*/
void Show1(){}   //定义零个参数函数，递归调用到零个参数函数时。调用该函数，然后终止继续递归
template<typename T,typename ... Args>  //Args是一个模板参数包
void Show1(const T &value,const Args &... args)     //args是一个函数参数包
{
    std::cout<<"Show1 value=="<<value<<std::endl;
    Show1(args...);  //递归调用，依次展开每个参数。不能用args[2]方式调用，只能依次展开
}
 


/*定义和声明一个多参数模板函数，非递归方式展开*/
template<typename T>
int Print(T arg)
{
    std::cout<<"Show2 value=="<<arg<<std::endl;
    return 1;
}
template<typename ... Args>
void Show2(Args ... args)
{
    int arr[] = {(0, Print(args))...};
    std::cout <<  1;
}

 
int main()
{
    Show1(1,2.0,"33","string");
    Show2(66,8888.0,"dsd","sd545sd2s");
}