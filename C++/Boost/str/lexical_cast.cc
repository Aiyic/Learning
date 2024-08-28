// 数值之间的转换

#include <iostream>

using namespace std;

//包含头文件
#include <boost/lexical_cast.hpp>

int main() {
  using boost::bad_lexical_cast;
  using boost::lexical_cast; //声明，省略boost名字空间前缀
  try {
    //字符串 转 整型
    // int  a = lexical_cast<int>("123");
    int a = lexical_cast<int>("123efd", 3);
    cout << a << endl;

    //字符串 转 浮点型
    float b = lexical_cast<float>("1.23456");
    cout << b << endl;

    //浮点数 转 为字符串
    string c = lexical_cast<string>(1.23456);
    cout << c << endl;

    //整数转为字符串
    string d = lexical_cast<string>(666);
    cout << d << endl;
  }
  // catch (const std::exception&  e)
  catch (const bad_lexical_cast &e) {
    cout << e.what() << endl;
  }

  return 0;
}
