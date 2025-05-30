#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static int maxProfit(vector<int> &prices) {
    int earn = 0;
    int buy = -1;
    for(int sell : prices){
      if(buy == -1){
        buy = sell;
      }
      else{
        if(sell > buy){
          earn = max(earn, sell-buy);
        }
        else{
          buy = sell;
        }
      }
    }
    return earn;
  }
};

int main() {
  vector<int> prices = {2,1,2,1,0,1,2};
  auto a = Solution::maxProfit(prices);
  cout << 1;
  return 0;
}
