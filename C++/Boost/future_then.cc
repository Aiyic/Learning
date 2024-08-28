// -lboost_thread

#include <iostream>
#include <string>

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

using boost::async;
using boost::future;

int main() {
  future<int> f1 = async([]() {
    std::cout << "f1" << std::endl; // here .get() won't block
    return 123;
  });

  future<std::string> f2 = f1.then([](future<int> f) {
    std::cout << "f2" << std::endl;    // here .get() won't block
    std::cout << f.get() << std::endl; // here .get() won't block
    return std::string("sgfsdfs");
  });

  std::cout << f2.get() << std::endl; // here .get() won't block
  return 0;
}