#include <bits/stdc++.h>

using namespace std;

vector<int> findRightMinGreater(const vector<int> &nums) {
  set<int> dp;
  vector<int> res(nums.size());
  for (int i = nums.size() - 1; i >= 0; --i) {
    if (dp.empty() || nums[i] >= *dp.rbegin()) {
      res[i] = -1;
    } else {
      auto it = dp.upper_bound(nums[i]);
      if (it != dp.end()) {
        res[i] = *it;
      } else {
        res[i] = *dp.begin();
      }
    }
    dp.insert(nums[i]);
  }
  return res;
}

// 测试代码
int main() {
  vector<int> nums = {11, 13, 13,13};
  vector<int> res = findRightMinGreater(nums);
  for_each(res.begin(), res.end(), [&](int i) { cout << i << ' '; });
  return 0;
}