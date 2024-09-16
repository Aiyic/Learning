#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  getchar();
  while (t--) {
    string s1, s2, s3, s4;
    getline(cin, s1, '/');
    getline(cin, s2, ' ');
    getline(cin, s3, '/');
    getline(cin, s4);
    unordered_map<char, int> chars;
    auto fun = [&chars](string ss1, string ss2, int add){
        int i = 0;
        int j = 0;
        while (i < ss1.length() && j < ss2.length()) {
        if (ss1[i] == ss2[j]) {
            i++;
            j++;
        } else {
            chars[ss1[i]]+=add;
            i++;
        }
        }
        if (j != ss2.length()) {
            cout << "NO" << endl;
            return false;
        }
        return true;
    };
    if(!fun(s1,s3,1)){
        continue;
    }
    if(!fun(s2,s4,-1)){
        continue;
    }
    bool flag = true;
    for (auto [k, v] : chars) {
      if (v != 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}

/*

4
114514/1919810 1454/91980
114514/1919810 454/9980
114514/1919810 114514/1919810
21/42 1/2

*/