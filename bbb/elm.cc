#include <bits/stdc++.h>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// 函数：计算最大公因数
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 函数：计算可能的 i 和 j 之和
long long calculateSum(int n, int g) {
    long long totalSum = 0;

    // 遍历可能的 a 和 b
    for (int a = 1; a <= n / g; ++a) {
        for (int b = a + 1; b <= n / g; ++b) {
            if (gcd(a, b) == 1) { // 仅当 a 和 b 互质
                totalSum += g * (a + b); // 计算 i + j
            }
        }
    }

    return totalSum;
}

int main() {
  int n;
  cin >> n;

  int x;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    cout << calculateSum(x) << endl;
  }

  return 0;
}

/*

4
2
3
10
114514


1
3

*/