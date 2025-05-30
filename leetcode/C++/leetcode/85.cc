
#include <bits/stdc++.h>
#include <vector>

using namespace std;

// matex[i][j] =
// left_has_one_num[i][j]
// upper_has_one_num[i][j]

class Solution {
public:
  int maximalRectangle(vector<vector<char>> &matrix) {
    int x = matrix.size();
    int y = matrix[0].size();
    vector<vector<int>> upper_has_one_num(x , vector<int>(y));

    for (int j = 0; j < y; ++j) {
      upper_has_one_num[0][j] = (matrix[0][j] - '0');
      for (int i = 1; i < x; ++i) {
        if (matrix[i][j] == '0') {
          upper_has_one_num[i][j] = 0;
        } else {
          upper_has_one_num[i][j] = upper_has_one_num[i - 1][j] + 1;
        }
      }
    }

    int max_size = 0;
    for (int i = 0; i < x; ++i) {
      for (int j = 0; j < y; ++j) {
        if (matrix[i][j] == '1') {
          int height = upper_has_one_num[i][j];
          int left = 0;
          int right = 0;
          while (j - left - 1 >= 0 &&
                 upper_has_one_num[i][j - left - 1] >= height) {
            left++;
          }
          while (j + right + 1 < y &&
                 upper_has_one_num[i][j + right + 1] >= height) {
            right++;
          }

          max_size = max(max_size, height * (left + right + 1));
        }
      }
    }
    return max_size;
  }
};

int main() {
  Solution s;
  vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                 {'1', '0', '1', '1', '1'},
                                 {'1', '1', '1', '1', '1'},
                                 {'1', '0', '0', '1', '0'}};

  auto a = s.maximalRectangle(matrix);
  cout << 1;
  return 0;
}
