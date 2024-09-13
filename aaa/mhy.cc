#include <bits/stdc++.h>

using namespace std;

int main() {
  int n,m;
  cin >> n >> m;

  auto getnum = [](int x){
    int res=0;
    while(x>0){
        int c = x%10;
        x/=10;
        if(c == 4 || c == 6){
            res++;
        }
    }
    return res;
  };
  int max_count = 0;
  int max_idx = n;
  for(int i=n; i<=m; ++i){
    int count  = getnum(i);
    if(count >= max_count){
        max_count = count;
        max_idx = i;
    }
  }
  cout << max_idx << endl;
  return 0;
}

/*


*/