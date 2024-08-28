#include<iostream>
using namespace  std;

//string_algo库的头文件
#include<boost/algorithm/string.hpp>
using  namespace  boost;//名字空间

int main()
{
   //大小写转换 
   cout << "大小写转换" << endl;
   string  str1 = "abc";
   to_upper(str1);//改变原字符串
   cout << str1 << endl;
  
   to_lower(str1);//改变原字符串
   cout << str1 << endl;
    
   string  str2=to_upper_copy(str1);//不改变原字符串
   cout << str1 << endl;
   cout << str2 << endl;

   return 0;
}
