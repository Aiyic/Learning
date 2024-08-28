#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  hash<string> hs;
  for (int line = 0; line < n; ++line) {
    string full;
    cin >> full;
    string ab;
    getchar();
    getline(cin, ab);
    int idx = ab.find(' ');
    ab[idx] = '/';
    if(hs(full)!=hs(ab)){
        cout << 0 << endl;
    }
    else{
        cout << ((full==ab)?1:0) << endl;
    }
  }
  return 0;
}

/*

4
assets/a/b/c assets/a b/c
assets/a/b/c assets/a/b c
assets/b/c assets/b d
assets/b/c/d asset/b/c d

*/