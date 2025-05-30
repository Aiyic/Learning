
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static vector<int> getRow(int rowIndex) {
    if (rowIndex == 0) {
      vector<int> res = {1};
      return res;
    }
    auto back = getRow(rowIndex - 1);
    vector<int> newline;
    int last = 0;
    for (auto i : back) {
      newline.push_back(last + i);
      last = i;
    }
    newline.push_back(1);
    return newline;
  }
};

int main() {

  auto a = Solution::getRow(3);
  cout << 1;
  return 0;
}
