#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> left(n);
  vector<int> right(n);
  vector<int> a(n);
  set<int> nodes;

  for (int i = 0; i < n; ++i) {
    cin >> left[i] >> right[i] >> a[i];
    nodes.insert(left[i]);
    nodes.insert(right[i]);
  }
  unordered_map<int, int> left_idx;
  unordered_map<int, int> right_idx;
  set<int> left_set;
  set<int> right_set;
  for (int i = 0; i < n; ++i) {
    left_idx.insert({left[i],i});
    right_idx.insert({right[i],i});
    left_set.insert(left[i]);
    right_set.insert(right[i]);
  }
  unordered_set<int> index;
  for(int node: nodes){
 
    
  }

  cout << endl;
  return 0;
}

/*

3
1 2 3
2 3 4
1 3 1

7


6
1 3 7
2 5 4
2 6 8
1 2 2
4 6 9
1 6 7

15




*/