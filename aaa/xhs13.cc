#include <bits/stdc++.h>
#include <vector>
using namespace std;

  using ll =long long;

int getidx (ll m, int start, vector<int>& locs){
  int res;
  if(m%2==0){
    res = (locs[(start+m/2)%m] + locs[(start +m/2-1)%m]) / 2;
  }
  else{
    res = locs[(start+m/2)%m];
  }
  return res;
}
int main() {
  ll n,m;
  cin >> n >> m;

  vector<ll> locs(m);
  for(int i=0; i<m;++i){
    cin >> locs[i];
  }
  sort(locs.begin(),locs.end());

  ll maxdis = min(abs(locs.back()-locs.front()), abs(locs.front()+n-locs.back()));
  int start = 0;
  ll perdis = maxdis;
  int count = 1;

  for(int i=0; i<m-1; ++i){
    ll dis = min(abs(locs[i+1]-locs[i]), abs(locs[i]+n-locs[i+1]));
    if(perdis == dis) count++;

    perdis = dis;

    if(dis > maxdis){
      maxdis = dis;
      start = i+1;
    }  
  }
  if(count == m) {
    cout << locs[0] << endl;
    return 0;
  }

  int res = n;
  if(start == 0){
    res = getidx(m, 0, locs);
  }

  for(int i=0; i<m-1; ++i){
    ll dis = min(abs(locs[i+1]-locs[i]), abs(locs[i]+n-locs[i+1]));
    if(dis == maxdis){
      res = min(res, getidx(m, i+1, locs));
    }
  }

  cout << res << endl;
  return 0;
}

/*

4 3
1 4 3

*/