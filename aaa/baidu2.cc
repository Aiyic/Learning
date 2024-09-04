#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Element {
  int value;
  int count;
  int firstIndex;
};

// 自定义比较函数
bool compare(const Element &a, const Element &b) {
  if (a.count != b.count) {
    return a.count > b.count; // 按频率降序
  }
  return a.firstIndex < b.firstIndex; // 按第一次出现的顺序升序
}

vector<int> sortByFrequency(const vector<int> &arr) {
  unordered_map<int, int> freq_map;
  vector<Element> elements;

  // 统计频率和第一次出现的索引
  for (int i = 0; i < arr.size(); ++i) {
    if (freq_map.find(arr[i]) == freq_map.end()) {
      freq_map[arr[i]] = 1;
      elements.push_back({arr[i], 1, i}); // 新元素，保存值、频率和索引
    } else {
      freq_map[arr[i]]++;
      // 更新频率
      
    }
  }

  // 排序
  sort(elements.begin(), elements.end(), compare);

  // 提取结果
  vector<int> result;
  //   result.reserve(elements.size()); // 不能省
  for (const auto &elem : elements) {
    result.push_back(elem.value);
  }

  return result;
}

int main() {
  vector<int> input1 = {1, 3, 5, 2, 4, 6};
  vector<int> output1 = sortByFrequency(input1);

  cout << "Output 1: ";
  for (int num : output1) {
    cout << num << " ";
  }
  cout << endl;

  vector<int> input2 = {1, 1, 2, 2, 2};
  vector<int> output2 = sortByFrequency(input2);

  cout << "Output 2: ";
  for (int num : output2) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}