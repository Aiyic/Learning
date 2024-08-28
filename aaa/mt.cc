#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    ll a;
    ll b;
    ll c;
    ll d;
    ll n;
    cin >> a >> b >> c >> d >> n;
    vector<ll> point(n);
    ll mindes=INT_MAX;
    ll minidx=-1;
    for(int i=0;i<n;i++){
        ll x;
        ll y;
        cin >> x >> y;
        ll des = abs(x-a)+abs(y-b);
        if(des<mindes){
            mindes=des;
            minidx=i;
        }
        point[i] = abs(x-c)+abs(y-d);
    }
    ll  res = mindes + point[minidx];
    point.erase(point.begin()+minidx);
    for_each(point.begin(), point.end(), [&res](ll i){res += 2L*i;});
    cout << res << endl;
}

/*

0 0 0 0
3
1 0
2 2
2 4


*/