// 封装版的shm

#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 

int main() 
{ 
  boost::interprocess::shared_memory_object::remove("Highscore"); 
  boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 

// 如果对象已存在，创建失败 construct() 返回值是0，还有 find_or_construct() 版本
// 容量不够会抛出异常
// int *i = managed_shm.construct<int>("Integer")(99); 
  int *i = managed_shm.construct<int>("Integer")[10](99); 
  std::cout << *i << std::endl; 
  std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
  if (p.first != nullptr) 
  { 
    // 找到的第一个对象为指针地址
    std::cout << *p.first << std::endl; 
    // 第二个为长度，主要提供给数组使用
    std::cout << p.second << std::endl; 
  } 
} 