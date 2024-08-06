#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <iostream>

int main() {
  boost::interprocess::managed_shared_memory managed_shm(
      boost::interprocess::open_or_create, "shm", 1024);
  int *i = managed_shm.find_or_construct<int>("Integer")();

  //  命名对象由操作系统管理，所以它们不存储在共享内存上，它们可以被应用程序通过名称访问。
  //  每个知道此名称的应用程序能够访问这同一个对象。
  //  为了获得对位于共享内存中数据的访问，应用程序需要通过调用 lock()
  //  函数获得互斥对象的拥有关系。
  boost::interprocess::named_mutex named_mtx(
      boost::interprocess::open_or_create, "mtx");
  named_mtx.lock();
  ++(*i);
  std::cout << *i << std::endl;
  named_mtx.unlock();
}