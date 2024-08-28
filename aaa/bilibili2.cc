#include <bits/stdc++.h>
#include <stack>

using namespace std;

int main() {
  int line;
  cin >> line;
  while ((line--) > 0) {
    string s;
    cin >> s;
    stack<char> bk;
    int change = 0;
    for (char c : s) {
      if (c == '{' || c == '[') {
        bk.push(c);
      } else {
        if ((c == ']' && bk.top() == '[') || (c == '}' && bk.top() == '{')) {;}
        else {
          change++;
        }
        bk.pop();
      }
    }
    cout << change << endl;
  }
}

/*

2
{[][}}
[][]{{]]

*/