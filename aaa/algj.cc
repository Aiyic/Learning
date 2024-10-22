#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<bool> is_prime(1e7 + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= 1e7; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j <= 1e7; j += i) {
        is_prime[j] = false;
      }
    }
  }
  unordered_set<int> primes;
  for (int i = 2; i <= 1e7; ++i) {
    if (is_prime[i]) {
      primes.insert(i);
    }
  }
  auto judge_prime = [&](int i) { return primes.find(i) != primes.end(); };
  vector<bool> apple_is_prime(n);
  for (int i = 0; i < n; ++i) {
    int weight;
    cin >> weight;
    apple_is_prime[i] = judge_prime(weight);
  }
  vector<unordered_set<int>> edges(n);
  for (int i = 0; i < n - 1; ++i) {
    int u;
    int v;
    cin >> u >> v;
    if (u > v) {
      swap(u, v);
    }
    u--;
    v--;
    edges[u].insert(v);
  }
  unordered_map<int, pair<int, int>> dp;
  function<pair<int, int>(int)> get_pair = [&](int i) {
    if (dp.find(i) == dp.end()) {
      int x = apple_is_prime[i] ? 1 : 0;
      int y = 1;
      for (int j : edges[i]) {
        auto [a, b] = get_pair(j);
        x += a;
        y += b;
      }
      dp[i] = {x, y};
    }
    return dp[i];
  };
  int sum = 0;
  auto [root1, root2] = get_pair(0);
  for (int i = 0; i < n; ++i) {
    if (edges[i].empty()) {
      continue;
    }
    for (int j : edges[i]) {
      auto [a, b] = get_pair(j);
      sum += ((root1 - a) * (root2 - b) + a * b);
    }
  }
  cout << sum << endl;
  return 0;
}

/*

4
7 2 5 2
1 2
4 2
3 1

4
7 2 5 4
1 2
4 2
3 1


1*2+2*2 = 6
0*1+3*3 = 9
1*1+2*3 = 7



*/