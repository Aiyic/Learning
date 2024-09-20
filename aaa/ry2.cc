#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  deque<string> str;
  while (s.find(',') != string::npos) {
    int id = s.find(',');
    str.emplace_back(s, 0, id);
    s = string(s, id + 1);
  }
  str.emplace_back(s);
  int size;
  cin >> size;
  while (!str.empty()) {
    deque<string> line;
    line.push_back(str.front());
    str.pop_front();
    int len = size - line.back().length();
    while (!str.empty() && str.front().length() + 1 <= len) {
      line.push_back(str.front());
      str.pop_front();
      len -= line.back().size() + 1;
    }
    s = line[0];
    if (str.empty()) {
      line.erase(line.begin());
      for (string &sss : line) {
        s += string(1, '*') + sss;
      }
    } else {
      if (line.size() != 1) {
        int step = size;
        for (string &sss : line) {
          step -= sss.length();
        }
        int remain = step % (line.size() - 1);
        step /= line.size() - 1;

        line.erase(line.begin());
        for (string &sss : line) {
          if (remain-- > 0)
            s += string(step + 1, '*') + sss;
          else
            s += string(step, '*') + sss;
        }
      }
    }
    s += string(size - s.size(), '*');
    cout << s << endl;
  }
  return 0;
}

/*


This,is,an,eggplant,oof,our,beautifull,sweety,baby
16


*/