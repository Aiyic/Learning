#include <algorithm>
#include <iostream>
#include <vector>

void rearrangeArray(std::vector<int> &arr) {
  std::sort(arr.begin(), arr.end());
  std::vector<int> result;
  int n = arr.size();

  // 使用双指针分别从头和尾取元素
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    if (left == right) {
      result.push_back(arr[left]);
      break;
    }
    result.push_back(arr[left++]);
    result.push_back(arr[right--]);
  }

  // 输出重排后的数组
  for (int num : result) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> arr(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  rearrangeArray(arr);
  return 0;
}

/*

5
1 2 3 4 5
4
1 2 3 4 

*/