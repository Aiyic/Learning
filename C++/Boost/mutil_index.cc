// multi_index_container 
// 可以自定义容器类型，包括顺序容器，哈希容器
// 自定义是否自动排序
// 可以定义多个索引值，基于不同的索引进行查找

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <iostream>

struct Person {
  std::string name;
  int age;

  Person(std::string n, int a) : name(std::move(n)), age(a) {}

  // 供示例三使用
  std::string get_name() const { return name; }
  bool operator<(const Person &p) const { return age < p.age; }
};

//  示例一，构建一个可重复的哈希容器，并声明两种索引
//  multi_index_container 是一个模板类，你需要为它传递两个模板参数。
//  第一个参数是容器中储存的元素类型， 在例子中是 person；
//  而第二个参数指明了容器所提供的所有索引类型。
using person_multi = boost::multi_index::multi_index_container<
    // 存储的元素类型
    Person,
    // 索引的类型
    boost::multi_index::indexed_by<
        // 索引一，采用哈希值，且可以重复
        boost::multi_index::hashed_non_unique<
            // member类三个参数：实体的类型，索引的类型，索引对应的实体的成员
            boost::multi_index::member<Person, std::string, &Person::name>>,
        // 还有其他的索引类型，hashed_unique 唯一哈希
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<Person, int, &Person::age>>>>;

// 示例二，可随机访问的有序可重复容器
using person_multi2 = boost::multi_index::multi_index_container<
    Person,
    boost::multi_index::indexed_by<
        // sequenced 接口让我们可以像使用 std::list 一样的使用 MultiIndex。
        boost::multi_index::sequenced<>,
        // ordered_non_unique 有序可重复接口，容器中的对象会自动的排序。可以使用
        // lower/upper_bound 系列函数查找
        boost::multi_index::ordered_non_unique<
            // 接受一个 member 参数
            boost::multi_index::member<Person, int, &Person::age>>,
        // random_access， 可以像使用 std::vector 一样使用 MultiIndex 容器。支持
        // operator[] 和 at()
        boost::multi_index::random_access<>>>;

// 示例三，直接使用容器中的数据类型作为键值的有序容器，identity 需要类型可比
using person_multi3 = boost::multi_index::multi_index_container<
    Person,
    boost::multi_index::indexed_by<
        // ordered_unique 有序不可重复，容器中的对象会自动的排序。
        boost::multi_index::ordered_unique<
            // identity 可以使用容器中的数据类型作为键值，功能类似于 member。
            // 需要 person 类是可排序的， 因为它已经作为了接口ordered_unique
            // 的键值。 在示例里， 它是通过重载 operator<() 操作符来实现的。
            boost::multi_index::identity<Person>>,
        // 定义了一个哈希索引
        boost::multi_index::hashed_unique<
            // member 方法用于表示成员变量作为索引 (const_)mem_fun
            // 方法用于表示成员函数作为索引，const 表示返回值为常量。
            // 这里使用了 get_name 方法而不是 name 成员变量。
            // 还有全局函数 global_fun 和组合键 composite_key 方法
            boost::multi_index::const_mem_fun<Person, std::string,
                                              &Person::get_name>>>>;

int main() {
  person_multi persons;

  persons.insert(Person("Boris", 31));
  persons.insert(Person("Anton", 35));
  persons.insert(Person("Caesar", 25));

  auto it = persons.find("Boris");

  // 所有存储在 MultiIndex 中的元素都该是常量。
  // 为了避免删除或修改其中元素真正的值， Boost.MultiIndex
  // 提供了一些常用函数来操作其中的元素。 使用这些函数来操作 MultiIndex
  // 容器中的值并不会引起那些元素所指向的真正的对象改变， 所以更新动作是安全的。
  persons.modify(it, [](Person &p) { p.age = 100; });

  // 接口都是用从0开始的索引值来编号的。 想要访问第二个接口， 你需要调用 get()
  // 函数并且传入想要访问的接口的索引值。
  const person_multi::nth_index<1>::type &age_index = persons.get<1>();

  std::cout << age_index.count(25) << std::endl;

  auto it2 = age_index.find(35);
  std::cout << it2->name << ' ' << it2->age << std::endl;
}