#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll kMod = 1000000007;

ll sum(ll a, ll b, ll c) {
  ll res = a % kMod;
  res = (res * (b % kMod)) % kMod;
  res = (res * (c % kMod)) % kMod;
  return res;
}
ll maxp(ll a, ll b, ll c, ll k) {
  ll nums[] = {a, b, c};
  sort(nums, nums + 3);

  if (nums[1] - nums[0] >= k) {
    return sum(nums[0] + k, nums[1], nums[2]);
  }

  k -= nums[1] - nums[0];
  nums[0] = nums[1];

  if ((nums[2] - nums[1]) >= k / 2) {
    nums[1] += k / 2;
    nums[0] += k - k / 2;
    return sum(nums[0], nums[1], nums[2]);
  }

  k -= nums[2] - nums[0];
  k -= nums[2] - nums[1];
  nums[2] += k / 3;
  return sum(nums[2] + k % 3, nums[2], nums[2]);
}
int main() {
  ll a, b, c, k;
  cin >> a >> b >> c >> k;
  cout << maxp(a, b, c, k) << endl;
  return 0;
}

/*

1 2 3 1


*/