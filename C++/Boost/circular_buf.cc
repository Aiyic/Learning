// 循环缓冲器

#include <exception>
#include <iostream>
using namespace std;

#include <boost/circular_buffer.hpp>
using namespace boost;

int main() {

  //环形缓存（特别像队列）
  try {
    circular_buffer<int> cb(3); //容量为3

    cb.push_back(1); //从尾部插入
    cb.push_back(2); //
    cb.push_back(3); //容量已满

    // cb.push_front(1);//从头插入
    // cb.push_front(2);//
    // cb.push_front(3);//容量已满

    auto print_cb = [&cb]() {
      for (auto &elm : cb) {
        cout << elm << " ";
      }
      cout << endl;
    };

    print_cb();

    //容量已满，尾部插入，踢出头部元素
    cb.push_back(4);
    print_cb();

    //容量已满，头部插入，踢出尾部元素
    cb.push_front(5);
    print_cb();

    cb.pop_back(); //删除尾部的元素
    print_cb();

    cb.pop_front(); //删除头部的元素
    print_cb();

  } catch (boost::exception &e) {
    //
  }
  return 0;
}
