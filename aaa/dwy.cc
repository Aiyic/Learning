#include <iostream>
#include <vector>

using namespace std;

vector<int> fun(int n) {
  vector<bool> dp(n + 1, false);
  for (int i = n; i >= 1; --i) {
    if ((i + 1 <= n && !dp[i + 1]) 
        || (i + 2 <= n && !dp[i + 2]) 
        || (i + 3 <= n && !dp[i + 3])) {
      dp[i] = true;
    }
  }
  vector<int> nuns;
  for (int i = 1; i < n; ++i) {
    if (dp[i]) {
      nuns.push_back(i);
    }
  }
  return nuns;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    int n;
    cin >> n;
    vector<int> results = fun(n); 
    for (int num : results) {
      cout << num << " ";
    }
    cout << endl;
  }
  return 0;
}