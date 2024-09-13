#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static bool fun(vector<int> &prices, int people) {
    sort(prices.begin(), prices.end());
    multiset<int> sets;
    int total = 0;
    for (int p : prices) {
      sets.insert(p);
      total += p;
    }
    if (total % people != 0) {
      return false;
    }

    function<vector<int>(int x)> fun2 = [&](int x) {
      vector<int> res;
      auto it = sets.lower_bound(x); 
      if (it != sets.end() && *it == x) {
        sets.erase(it); 
        res.push_back(x);
        return res;
      }
      if (it == sets.begin()) { 
        return res;
      }
      it = prev(it);
      sets.erase(it);
      res = fun2(x - *it);
      if (res.empty()) {
        return res;
      }
      res.push_back(*it);
    };

    for(int i=0; i<people; ++i){
        if(fun2(total / people).empty()){
            return false;
        }
    }
    return true;
  }
};

int main() {
  vector<int> nums = {5,4,1, 3, 2, 3, 2};
  auto a = Solution::fun(nums, 4);
  cout << a;
  return 0;
}

/*


*/