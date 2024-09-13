#include <bits/stdc++.h>
#include <functional>
#include <vector>

using namespace std;

int main() {
  int n,m;
  cin >> n >> m;
  vector<int> c(m);
  vector<int> have(m,0);
  for(int i=0; i<m; ++i){
    cin >> c[i];
  }

  int res;
  int abty;
  
  vector<vector<int>> hero_abty(n,vector<int>(3,0));
  vector<vector<int>> hero_idx(n,vector<int>(3,0));


  for(int i=0; i<n; ++i){
    int a1,a2,a3;
    int b1,b2,b3;
    cin >> a1 >> a2 >> a3;
    cin >> b1 >> b2 >> b3;
    hero_abty[i][0] = a1;
    hero_abty[i][1] = a2;
    hero_abty[i][2] = a3;
    hero_idx[i][0] = b1;
    hero_idx[i][1] = b2;
    hero_idx[i][2] = b3;
  }

  function<void(int,int)> func_back = [&](int deep, int idx){
    if(deep>=n || idx>2){
        res = max(res, abty); 
        return ;
    }
    abty += hero_abty[deep][idx];
    have[hero_idx[deep][idx]-1] += 1;

    if(have[hero_idx[deep][idx]]==3){
        abty += c[hero_idx[deep][idx]];
    }

    func_back(deep+1,0);

    abty-=hero_abty[deep][idx];
    have[hero_idx[deep][idx]] -= 1;

    if(have[hero_idx[deep][idx]]==2){
        abty -= c[hero_idx[deep][idx]];
    }
    func_back(deep,idx+1);
  };

  func_back(0,0);
  cout << res;
  return 0;
}

/*
4 13
0 1111 525 1031 55 0 0 722 0 430 1221 29 711
9 5 3
3 2 4
2 3 7
2 11 5
4 0 6
10 2 13
10 5 196
1 12 8

*/