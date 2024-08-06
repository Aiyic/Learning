/*
   C++11引入了using，可以轻松的定义别名，而不是使用繁琐的typedef。
   using 的别名语法覆盖了 typedef 的全部功能。
*/

#include<vector>

typedef std::vector<std::vector<int>> vvi; // before c++11
using vvi = std::vector<std::vector<int>>; // c++11


template<class T>
struct Alloc {};
template<class T>
using Vec = std::vector<Alloc<T>>; // 类型标识为 vector<Alloc<T>>
Vec<int> v; // Vec<int> 同 vector<Alloc<int>>


