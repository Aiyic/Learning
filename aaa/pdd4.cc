#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  int num0 = 0;
  int num1 = 0;
  while (n--) {
    char c;
    cin >> c;
    if (c == '1') {
      num1++;
    } else {
      num0++;
    }
  }
  if (num0 > num1 + 1) {
    cout << 2 * num1 + 1 << endl;
  } else {
    cout << 2 * num0 - 1 << endl;
  }
}
/*

5
10010

*/
