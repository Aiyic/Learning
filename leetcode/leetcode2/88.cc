
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    for(int idx=0; idx<n; ++idx){
      nums1[idx+m]=nums2[idx];
    }
    
    ranges::sort(nums1);
  }
};

int main() {
  Solution s;
  vector<int> nums1 = {1,2,3,0,0,0};
  vector<int> nums2 = {2,5,6};

  s.merge(nums1, 3, nums2 ,3);
  cout << 1;
  return 0;
}
