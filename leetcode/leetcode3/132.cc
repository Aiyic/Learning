// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
public:
  static int minCut(string s) {
    int n = s.length();
    vector<vector<int>> dp(n,vector<int>(n+1));

    dp[0][0] = 1;
    dp[0][1] = 1;

    for(int i=1;i<n;++i){
      int m = dp[i-1][0];
      
    }


  }
};

int main() {
  auto x = Solution::minCut("aaabaa");
  cout << 1;
  return 0;
}

/*

dp[i] s[0..i]回文子串数

dp[i+1] 

aa b a
aba bb a
aa aba a
dp[i][j] s[0..i]的第j个回文子串的长度



*/