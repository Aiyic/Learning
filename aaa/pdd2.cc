#include <bits/stdc++.h>
#include <ostream>
#include <vector>

using namespace std;
using ll = long long;
int main() {
  int t;
  cin >> t;
  while ((t--) != 0) {
    int n;
    cin >> n;

    vector<ll> a;
    int num1=0;
    int num2=0;
    for (int i = 0; i < n; ++i) {
      ll x;
      cin >> x;
      if (x % 2 == 0) {
        a.push_back(x);
        ++num1;
      }
      else{
        ++num2;
      }
    }
    sort(a.begin(),a.end());
    if(num1<=num2) {
        cout << num1 << endl;
        continue;
    }
    a.erase(a.begin()+(num1-num2), a.end());
    int opt = 0;
    while (!a.empty()) {
      opt++;
      if (a.size() >= 2) {
        ll x = a.back();
        a.pop_back();
        x += a.back();
        a.pop_back();
        if (x % 2 == 0) {
          a.push_back(x);
        }
      } else {
        ll &x = a.back();
        x /= 2;
        if (x % 2 != 0) {
          a.pop_back();
        }
      }
    }
    cout << opt << endl;
  }
}
/*

2x 2(x+y)
2x(2y+1)=2x


1
1
1 3 4

*/
