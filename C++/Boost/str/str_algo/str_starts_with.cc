
// 判断式：
// starts_with：检测一个字符串是否是另亠个的前缀
// ends_with：  检测、个字符串是否是另一个的后缀
// contains：   检测、个字符串是否被另一个包含
// equals：     检测两个字符串是否相等
// lexicographical_compare：    根据字典序检测一个字符串是否小于另一个
// all：        检测一个字符串中的所有元素是否满足指定的判断式
//      除此所有算法都有另一个i前缀的版本（忽略大小写）

// 判断式（函数对象）:
// string_algo增强了标准库中的 equal_to<>和less<>函数对象，允许对不同类型的参数进行比较，并提供大小写无关的形。
// is_equal：   类似 equals算法，比较两个对象是否相等
// is_less：    比较两个对象是否具有小关系
// is_not_greater：     比较两个对象是否具有不大于关系

// 判断类型：
// is_space：   字符是否为空格
// is_alnum：   字符是否为字母和数字字符
// is_alpha：   字符是否为字母
// is_cntrl：   字符是否为控制字符
// is_digit：   宇符是否为十进制数字
// is_lower：   字符是否为小写字符
// is_punct：   字符是否为标点符号字符
// is_upper：   字符是否为大写字符
// is_xdigit：  字符是否为十六进制数字
// is_anyof：   字符是否是参数字符序列中的任意字符

#include<iostream>
using namespace  std;

//string_algo库的头文件
#include<boost/algorithm/string.hpp>
using  namespace  boost;//名字空间

int main()
{
   //判断式，返回bool
   cout << "判断式" << endl;
   cout << starts_with("Hello World", "He") << endl;//大小写敏感
   cout << starts_with("Hello World", "he") << endl;
   cout << istarts_with("Hello World", "he") << endl;//i忽略大小写

   cout << ends_with("Hello World", "ld") << endl;//大小写敏感 
   cout << iends_with("Hello World", "Ld") << endl;//i忽略大小写

   cout << contains("Hello World", "llo") << endl;//大小写敏感 
   cout << icontains("Hello World", "LLo") << endl;//i忽略大小写

   cout << equals("abc", "abc") << endl;//内容是否相等
   cout << iequals("abc", "Abc") << endl;//内容是否相等,i忽略大小写

   cout << all("Hello", is_lower()) << endl;//判断每一个字符是否全部是小写
   cout << all("hello", is_lower()) << endl;//判断每一个字符是否全部是小写

   cout <<  lexicographical_compare("zabc","xyz")<< endl;//字典次序第一个是否小于第二个

   cout << "判断式，函数对象" << endl;
   cout << is_equal()("abc", "abc") << endl;//内容是否相等,i忽略大小写
   is_equal  eq; 
   cout << eq("abc", "abc")<< endl;//等价于上面的写法

   cout << is_less()("abc", "zbc") << endl;//内容是否小于
   cout << is_not_greater()("abc", "zbc") << endl;//内容是否不大于


   cout << "分类" << endl;
   cout << is_alnum()('1') << endl;//判断是否是字母或数字
   cout << is_alnum()('a') << endl;
   cout << is_alnum()(',') << endl;

   cout << is_alpha()('A') << endl;//是否字母
   cout << is_digit()('1') << endl;//是否数字
   cout << is_cntrl()('\n') << endl;//是否控制字符
   cout << is_any_of("ABCDE")( 'F' ) << endl;//是否是ABCDE里面的任何一个
   cout << is_xdigit()('Q') << endl;//是否16进制的字符
   cout << is_lower()('a') << endl;//是否小写字符

   return 0;
}
