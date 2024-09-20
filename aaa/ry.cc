#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> a;
  vector<int> b;
  int r;
  auto getcin = [](vector<int> &aa) {
    char c = ',';
    string tmp;
    getline(cin, tmp, '{');
    while (c != '}') {
      int x;
      cin >> x;
      aa.push_back(x);
      cin >> c;
    }
  };
  getcin(a);
  getcin(b);
  string tmp;
  getline(cin, tmp, '=');
  cin >> r;

  for (int x : a) {
    auto left = lower_bound(b.begin(), b.end(), x);
    if (left == b.end()) {
      continue;
    }
    auto right = upper_bound(b.begin(), b.end(), x+r);
    if(left == right && right!=b.end()){
        cout << '(' << x << ',' << *left << ')';
        continue;
    }
    for(auto it = left; it!=right; ++it){
        cout << '(' << x << ',' << *it << ')';
    }
  }

  return 0;
}

/*


A={1,3,5},B={2,4,6},R=1


*/