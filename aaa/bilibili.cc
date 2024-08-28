#include <bits/stdc++.h>

using namespace std;

int main() {
  float x;
  cin >> x;
  float y = 0;
  if (x >= 0 && x < 5) {
    y = x + 2.5;
  } else if (x >= 5 && x < 10) {
    y = 2 - 1.5 * pow(x - 3, 2);
  } else if (x >= 10 && x < 20) {
    y = x / 2 - 1.5;
  }
  cout << fixed << setprecision(3) << y << endl;
}