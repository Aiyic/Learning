#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, c0, d0;
    cin >> n >> m >> c0 >> d0;

    // 存储馅料信息
    vector<int> a(m), b(m), c(m), d(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    // dp数组，dp[j]表示用j克面粉能获得的最大价值
    vector<int> dp(n + 1, 0);

    // 处理不放馅料的粽子
    for (int i = c0; i <= n; ++i) {
        dp[i] = max(dp[i], dp[i - c0] + d0);
    }

    // 处理每种有馅料的粽子
    for (int i = 0; i < m; ++i) {
        int max_count = a[i] / b[i]; // 能用的最大馅料数量
        for (int j = n; j >= c[i]; --j) { // 遍历面粉
            for (int k = 1; k <= max_count; ++k) { // 遍历可以制作的个数
                if (j >= k * c[i] && a[i] >= k * b[i]) {
                    dp[j] = max(dp[j], dp[j - k * c[i]] + k * d[i]);
                }
            }
        }
    }

    // 输出最大价值
    cout << dp[n] << endl;

    return 0;
}

/*

端午节快到了，小强想要做点粽子挣点外快。
已知现在有n克面粉,m种不同的粽子馅料.第i种馅料有a[i]克，并且做第之种类型的粽子会消耗b[i],克馅料和c[i]克面粉，
出售后每个会得到d[i]的价值.当然粽子里面也可以不放馅料，对于这种类型的粽子每个会消耗c[0]克面粉，出售后每个会得到d[0]的价值。
现在小强请你帮他计算出如何做粽子能获得最大的价值?(假设粽子做出来以后，一定能卖出)

输入第一行包含四个整数n,m,c[0]和d[0]
接下来输入m行,每行输入四个整数a[i],b[i],c[i]和d[i]
输出描述
输出一个整数表示能获得的最大价值

示例 1
输入
10 2 1 1
6 3 2 50
8 2 1 10
输出
142
说明
做2个第一类型的粽子，获得100的价值,
做4个第二类型的粽子，获得40的价值;
剩余的做没有馅的粽子，获得2的价值。
总价值为100+40+2=142

*/