#include <algorithm>
#include <boost/signals2.hpp>
#include <iostream>
#include <numeric>
#include <vector>

using boost::signals2::signal;

// 组合器模板，用于迭代所有的返回值
// operator() 的返回值类型任意，不必和signal相同
template <typename T> class Combiner {
public:
  using result_type = std::pair<T, T>;
  explicit Combiner(T t = T()) : v_(t) {}

  // operator() 的参数为两个迭代器，存的是所有返回值
  template <typename InputIterator>
  result_type operator()(InputIterator begin, InputIterator end) const {
    if (begin == end) {
      return result_type();
    }
    std::vector<T> vec(begin, end);
    T sum = accumulate(vec.begin(), vec.end(), v_);
    T max = *max_element(vec.begin(), vec.end());
    return result_type(sum, max);
  }

private:
  T v_;
};

// 组合器模板，存储所有返回值
template <typename T> struct ReturnAll {
  using result_type = T;

  // 例如 T 为 vector，即为构造一个存储所有返回值的容器
  template <typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const {
    return T(first, last);
  }
};

int main() {

  std::cout << "示例一" << std::endl;
  signal<void()> s;
  // f = []{ std::cout << "Hello, world!\n"; };
  // 常规的 bing 和 lambda 表达式只能关联一个，signal 可以关联多个动作
  // 可以指定顺序，不指定默认按照添加顺序
  s.connect([] { std::cout << ", world!\n"; });
  s.connect(0, [] { std::cout << "Hello"; });

  // 对于左值可调用对象可以取消关联
  // s.disconnect(world);

  // num_slots() 返回关联函数的数量。如果没有关联函数，则 num_slots() 返回0。
  // empty() 告诉您事件处理程序是否已连接。
  std::cout << s.num_slots() << std::endl;
  if (!s.empty()) {
    s();
  }
  // disconnect_all_slots() 的作用与其名称完全相同：它释放所有现有关联。
  s.disconnect_all_slots();

  std::cout << "示例二" << std::endl;
  // 声明一个返回 int 的 signal
  // 函数签名必须相同。。。
  signal<int()> s2;
  s2.connect([] { return 1; });
  s2.connect([] { return 2; });
  // 只接受最后一个返回值
  std::cout << *s2() << std::endl;

  std::cout << "示例三" << std::endl;
  // 构造时可以传入组合器实例对象，否则使用默认构造
  signal<int(), Combiner<int>> s3(Combiner<int>(3));
  s3.connect([] { return 1; });
  s3.connect([] { return 2; });
  s3.connect([] { return 3; });
  std::cout << s3().first << ' ' << s3().second << '\n';

  std::cout << "示例四" << std::endl;
  signal<int(), ReturnAll<std::vector<int>>> s4;
  s4.connect([] { return 1; });
  s4.connect([] { return 2; });
  std::vector<int> v = s4();
  std::cout << *std::min_element(v.begin(), v.end()) << '\n';
}