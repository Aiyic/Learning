#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; ++i) {
    string s;
    getline(cin, s);
    if("" != s){
        if(s.find(' ')==-1){
            cout << s << endl;
            continue;
        }
        vector<string> res;
        while (s.find(' ' )!= -1) {
            string ss(s,0,s.find(' '));
            s = string(s,s.find(' ')+1);
            res.push_back(ss);
        }
        res.push_back(s);
        reverse(res.begin(), res.end());
        for(const auto& x : res){
            cout << x << ' ';
        }
        cout << endl;
        s="";
    }
  }
  return 0;
}

/*

4
1112
1912
1892
1234

*/