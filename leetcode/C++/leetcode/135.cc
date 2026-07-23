// #include "../base/Node.h"
#include <bits/stdc++.h>

using namespace std;

/*
 * @lc app=leetcode.cn id=135 lang=cpp
 *
 * [135] 分发糖果
 */

// @lc code=start
class Solution {
public:
  static int candy(vector<int> &ratings) {
    // int left_rate = 0;
    // int left_candy = 0;
    // int total_candy = 0;
    // int down_len = 0;
    // for(auto x : ratings){
    //   if (x == left_rate){
    //     // 当前处于平坡
    //     left_candy = 1;
    //     down_len = 1;
    //     total_candy += left_candy;
    //   }
    //   else if (x > left_rate){
    //     // 当前处于递增序列
    //     left_candy += 1;
    //     down_len = 1;
    //     total_candy += left_candy;
    //   }
    //   else{
    //     // 当前处于递减序列
    //     left_candy = 1;
    //     down_len += 1;
    //     total_candy += down_len;
    //   }
    //   left_rate = x;
    // }
    // return total_candy;
  }

  static int candy1(vector<int> &ratings) {
    int n = ratings.size();
    auto candys = vector<int>(n, 1);

    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) {
        // 当前孩子的分数高于前一个孩子，多发一个糖果
        candys[i] = candys[i - 1] + 1;
      }
    }

    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        // 当前孩子的分数高于后一个孩子，多发一个糖果
        candys[i] = max(candys[i], candys[i + 1] + 1);
      }
    }

    return accumulate(candys.begin(), candys.end(), 0);
  }

  static int candy2(vector<int> &ratings) {
    int n = ratings.size();
    auto candys = vector<int>(n, 1);

    // 给前面孩子循环补糖
    auto add_candy = [&](int idx)->void {
      // 
      for(int i = idx-1; i >= 0; --i){
        if (ratings[i] > ratings[i+1] && candys[i] <= candys[i+1]){
          // 上一个孩子分更高，但是糖果数不够
          candys[i] = candys[i+1] + 1;
        }
        if (ratings[i] <= ratings[i+1]){
          // 上一个孩子分更低，不需要补糖
          break;
        }
      }
    };

    for (int i = 1; i < n; ++i) {
      if (ratings[i] <= ratings[i - 1]) {
        // 当前孩子的分数不高于前一个孩子
        if (candys[i - 1] == 1){
          // 如果上一个孩子只有一个糖，则当前孩子也只有一个糖，需要循环补给前面的孩子
          add_candy(i);
        }
      }
      else {
        // 当前孩子的分数高于前一个孩子，多发一个糖果
        candys[i] = candys[i - 1] + 1;
      }
    }

    return accumulate(candys.begin(), candys.end(), 0);
  }
};
// @lc code=end

int main() {
  vector<int> ratings = {1,3,2,2,1};

  auto a = Solution::candy(ratings);
  cout << 1;
  return 0;
}
/*

1 1 2 1
x 1 2 1

*/
