#include <bits/stdc++.h>

using namespace std;

int main() {
  int p;
  int w;
  cin >> p >> w;

  vector<int> a(p);
  for (int i = 0; i < p; ++i) {
    cin >> a[i];
  }

  auto order = [](vector<int> &a) {
    int last = a[0];
    for (int i : a) {
      if (i < last) {
        return false;
      }
      last = i;
    }
    return true;
  };

  if (order(a)) {
    cout << 0 << endl;
  }
  vector<int> aa(a.begin(), a.end());
  stack<int> b;

  auto insert_b = [](stack<int> &b,int &w) {
    stack<int> tmp;
    while(!b.empty() && b.top()<w){
      tmp.push(b.top());
      b.pop();
    }
    swap(tmp.top(), w);
    while(!tmp.empty()){
      b.push(tmp.top());
      tmp.pop();
    }
  };

  while (!aa.empty()) {
    if (b.empty() || b.top() >= aa.back()) {
      b.push(aa.back());
      aa.pop_back();
    }
    else{
      if(aa.back() > w){
        cout << -1 << endl;
        break;
      }
      insert_b(b,w);
    }
  }

  int opt = 0;
  for(int i=0; i<p; ++i){
    if(a[i]!=b.top()){
      opt++;
    }
    b.pop();
  }
  cout << opt << endl;
}
/*

5 5
2 1 3 2 4

*/
