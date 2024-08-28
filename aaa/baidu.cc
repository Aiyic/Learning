// vector<int>

// n_max 2

// 5 5 4 4 -- 4

//

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int max_2(const vector<int>& nums) {

  if (nums.size() < 2) {
    return -1;
  }
  int max = INT_MIN;
  int max2 = INT_MIN;

  for (int x : nums) {
    if (x > max) {
      max2 = max;
      max = x;
    } else if (x > max2 && x != max) {
      max2 = x;
    }
  }
  if (max2 == INT_MIN || max2 == max) {
    return -1;
  }
  return max2;
}

int main() {
    vector<int> num = {5, 5, 4, 4};
    vector<int> num2 = {1,2,3,4,5,6};
    cout << max_2(num) << endl;
    cout << max_2(num2) << endl;

}