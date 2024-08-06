// 提供key2val和val2key的双向映射

#include <iostream>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/timer/timer.hpp>
using namespace boost;
using namespace boost::timer;

int main() {
  bimap<int, string> bm; //左右视图有序

  //左视图，代表 key 类型是int ， value 类型是string
  bm.left.insert(make_pair(1, "AAA"));
  bm.left.insert(make_pair(1, "AAAA")); //不能插入重复的key

  //右视图，代表 key 类型是string ， value 类型是int
  bm.right.insert(make_pair("BBB", 2));
  bm.right.insert(make_pair("BBB", 222)); //不能插入重复的key

  bm.left.insert(make_pair(4, "DDD"));
  bm.right.insert(make_pair("CCC", 3));

  cout << bm.size() << " , " << bm.left.size() << " , " << bm.right.size() << endl;

  //查找
  auto it = bm.left.find(2); //左视图的key为整形
  if (it != bm.left.end())
    cout << it->first << " ->" << it->second << endl;

  auto it2 = bm.right.find("CCC"); //右视图的key为字符串
  if (it2 != bm.right.end())
    cout << it2->first << " ->" << it2->second << endl;

  cout << "------------------------------------" << endl;

  //左视图的遍历
  for (auto it = bm.left.begin(); it != bm.left.end(); ++it) {
    cout << it->first << " ->" << it->second << endl;
  }

  cout << "------------------------------------" << endl;

  //右视图的遍历
  for (auto it = bm.right.begin(); it != bm.right.end(); ++it) {
    cout << it->first << " ->" << it->second << endl;
  }

  getchar();
  return 0;
}
