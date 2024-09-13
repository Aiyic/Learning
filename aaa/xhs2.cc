#include <bits/stdc++.h>
using namespace std;
int f(int x) {
  int ans = 0;
  while (x > 0) {
    if (x % 2) {
      ans++;
    }
    x /= 2;
  }
  return ans;
}
int g(int x) {
  int fX = f(x);
  int ans = x + 1;
  while (f(ans) != fX) {
    ans++;
  }
  return ans;
}
int main() {
  vector<int> data = {1, 4, 2, 5, 3};
  sort(data.begin(), data.end());
  map<int, vector<int>> deviceData;
  for (auto &it : data) {
    int temp = f(it);
    deviceData[temp].push_back(it);
  }
  int ans = 0;
  for (auto &it : deviceData) {
    int tempAns = 1;
    for (int i = 0; i < it.second.size() - 1; i++) {
      if (it.second[i + 1] == g(it.second[i])) {
        tempAns++;
        ans = ans > tempAns ? ans : tempAns;
      } else {
        tempAns = 1;
      }
    }
  }
  cout << "ans: " << ans << endl;
  return 0;
}