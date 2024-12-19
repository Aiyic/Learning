#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;

  // 初始化数组
  vector<int> arr(n, 0);

  // 处理每次操作
  for (int i = 0; i < q; ++i) {
    int L, R, v;
    cin >> L >> R >> v;
    L--; // 转换为0-based索引
    R--;

    // 对于每个 vi 的倍数
    for (int j = v; j <= R + 1; j += v) {
      int index = j - 1; // j 是1-based，转为0-based
      if (index >= L && index <= R) {
        arr[index]++;
      }
    }
  }

  // 输出结果
  for (int i = 0; i < n; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}

/*

5 3
1 4 1
2 5 3
1 5 4
*/