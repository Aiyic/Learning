#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    cin >> n >> x;
    int people;
    vector<unordered_set<string>> MCN(n);
    for (int i = 0; i < n; ++i) {
      cin >> people;
      for (int j = 0; j < people; ++j) {
        string s;
        cin >> s;
        MCN[i].insert(s);
      }
    }

    bool flag = false;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        if(i==j) continue;

        unordered_set<string> sum;
        sum.insert(MCN[i].begin(), MCN[i].end());
        sum.insert(MCN[j].begin(), MCN[j].end());
        if(sum.size() == x){
          flag = true;
          cout << "YES" << endl;
          cout << i+1 <<" " << j+1 << endl;
          break;
        }
      }
      if(flag) break;
    }
    if(!flag) cout << "NO" << endl;
  }

  return 0;
}

/*

2
3 4
3 17 20 30
4 17 20 30 23
4 18 18 18 17
2 2
1 33Abc
3 32Def 45G 19h

*/