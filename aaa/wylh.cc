
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> game(10, 0);
  while ((n--) != 0) {
    vector<int> p(10);
    int play_count = 0;
    int vol_count = 0;
    for (int i = 0; i < 10; ++i) {
      cin >> p[i];
      if (p[i] > 0) {
        play_count++;
        if (p[i] == 2) {
          vol_count++;
        }
      }
    }
    if (play_count < 3)
      continue;
    if (vol_count > play_count - 2 || vol_count > 5)
      continue;

    for (int i = 0; i < 10; ++i) {
      if (p[i] == 2) {
        game[i]++;
      }
    }
  }
  int maxit = *max_element(game.begin(), game.end());
  for (int i = 0; i < 10; ++i) {
    if (game[i] == maxit) {
      cout << i + 1 << ' ';
    }
  }
  return 0;
}

/*

4
0 1 2 1 0 1 0 1 2 0
0 0 1 2 0 0 0 2 0 0
0 1 1 1 1 1 0 2 2 0
0 1 2 1 0 1 0 2 1 0


4
0 1 2 1 0 1 0 1 2 0
0 0 1 2 0 0 0 2 0 0
1 1 1 1 2 2 2 2 2 2
0 1 2 1 0 1 0 2 1 0

*/