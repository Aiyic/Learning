// string 可能带来额外的复制开销
// string_view 减小了string的开销
// string_view 可传入char* 字面量 string进行隐式转换

#include <iostream>
#include <cstring>
 
using namespace std;

int main(){
    cout << sizeof(string) << endl; 

    string x = "sadwa3qwadsadawdasc sawdawdawDZDWADWdsadawdawdawDZDWADWdsadawdascawdawdawDZDWADWdsadawdaawdawdawDZDWADW";
    cout << sizeof(x) << endl; 
    cout << x.length() << endl;
    cout << x.size() << endl; 


    auto fun = [](string_view sv){
        cout << sv << endl;
    };
    auto t = "21124\0 sadda";
    fun(x);
    fun(x.c_str());
    fun("12312341 324asdadwa");
    fun(t);

}