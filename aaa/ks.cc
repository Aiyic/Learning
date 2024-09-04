#include <bits/stdc++.h>
using namespace std;

vector<int> zfunc(vector<vector<int>> &mt) {
  vector<int> res;
  int size = mt.size();
  int start_x;
  int start_y;
  int count;
  for (int line=0; line < 2 * size - 1; ++line) {
    if ((line % 2) == 0) {
      if (line < size) {
        count = line;
        start_x = line;
        start_y = 0;
      } else {
        count = 2 * (size-1)- line;
        start_x = size-1;
        start_y = size-count-1;
      }
      for(int i=0;i<=count;++i){
        res.push_back(mt[start_x-i][start_y+i]);
      }
    }
    else{
      if (line <= size) {
        count = line;
        start_x = 0;
        start_y = line;
      } else {
        count = 2 * (size-1)- line;
        start_x = line - size + 1;
        start_y = size - 1;
      }
      for(int i=0;i<=count;++i){
        res.push_back(mt[start_x+i][start_y-i]);
      }
    }
  }
  return res;
}

int main() {
  vector<vector<int>> src = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  auto res = zfunc(src);
  ranges::for_each(res, [](int i) { cout << i << ' '; });
  return 0;
}
/*
{1, 2, 3, 4},
{5, 6, 7, 8},
{9, 10, 11, 12},
{13, 14, 15, 16}};
*/