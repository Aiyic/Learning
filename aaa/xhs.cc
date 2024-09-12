#include <bits/stdc++.h>
using namespace std;

long long cacl_sum(const vector<int> &arr) {
  long long totalSum = 0;
  int n = arr.size();
  for (int i = 0; i < n; ++i) {
    // 计算 arr[i] 在所有子区间中出现的次数
    long long contribution = (i + 1L) * (n - i);
    totalSum += arr[i] * contribution;
  }
  return totalSum;
}
int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }
  sort(nums.begin(), nums.end());
  vector<int> arr(n);
  // 使用双指针分别从头和尾取元素
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    if (left == right) {
      arr[left] = nums.back();
      nums.pop_back();
      break;
    }
    arr[left++] = nums.back();
    nums.pop_back();
    arr[right--] = nums.back();
    nums.pop_back();
  }
  cout << cacl_sum(arr) << endl;
  return 0;
}

/*

3
1 2 3

6
1 1 4 5 1 4

*/