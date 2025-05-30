#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int minimumTotal(vector<vector<int>>& triangle) {
      vector<int> *value = nullptr;
      for(auto& level : triangle){
        if(level == triangle.front()){
          value = &level;
        }
        else {
          level.front() += value->front();
          level.back() += value->back();
          for(int i=1; i<level.size()-1; ++i){
            level[i] += min((*value)[i-1],(*value)[i]);
          }
          value = &level;
        }
      }
      return *ranges::min_element(triangle.back());
    }
};

int main() {
  vector<vector<int>> triangle ={
    {2},
    {3,4},
    {6,5,7},
    {4,1,8,3}
  };
  auto a = Solution::minimumTotal(triangle);
  cout << 1;
  return 0;
}
