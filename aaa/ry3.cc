#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  multimap<int, string> ex_set, ex_set2, good_set, bad_set;
  while (getline(cin, s)) {
    int it = s.find(':');
    string name = string(s, 0, it);
    s = string(s, it + 1);
    vector<int> day;
    while (!s.empty()) {
      int it = s.find(' ');
      if (it == string::npos)
        break;
      day.push_back(stoi(string(s, 0, it)));
      s = string(s, it + 1);
    }
    day.push_back(stoi(s));

    auto judge_ex = [&]() {
      int count = 0;
      int step = 0;
      for (int i = 0; i < day.size(); i++) {
        if (day[i] >= 30000) {
          count++;
          i += 3;
        }
      }
      return count >= 4;
    };
    auto judge_ex2 = [&]() {
      int count = 0;
      for (int i : day) {
        if (i >= 10000) {
          count++;
        }
      }
      return count > 15;
    };
    auto judge_good = [&]() {
      int count = 0;
      for (int i : day) {
        if (i < 10000 && i >= 5000) {
          count++;
        }
      }
      return count > 15;
    };
    auto judge_bad = [&]() {
      int count = 22;
      for (int i : day) {
        if (i < 5000) {
          count--;
        }
      }
      return count > 18;
    };

    int sum = 0;
    for (int i : day) {
      sum += i;
    }
    if (judge_ex()) {
      s = name + ":excellent " + to_string(sum);
      ex_set.insert({sum, s});
    } else if (judge_ex2()) {
      s = name + ":excellent " + to_string(sum);
      ex_set2.insert({sum, s});
    } else if (judge_good()) {
      s = name + ":good " + to_string(sum);
      good_set.insert({sum, s});
    } else if (judge_bad()) {
      s = name + ":bad " + to_string(sum);
      bad_set.insert({sum, s});
    }
  }

  auto print = [](const multimap<int, string> &sets, const string &sss) {
    if (sets.empty()) {
      cout << sss << " is null" << endl;
    } else {
      for (auto it = sets.rbegin(); it!=sets.rend();++it) {
        auto &[k, v] = *it;
        cout << v << endl;
      }
    }
  };
  if (ex_set.empty() && ex_set2.empty() && good_set.empty() &&
      bad_set.empty()) {
    cout << "There is not data" << endl;
  } else {
    if (ex_set.empty() && ex_set2.empty()) {
      cout << "excellent is null" << endl;
    } else {
      for (auto it = ex_set.rbegin(); it!=ex_set.rend();++it) {
        auto &[k, v] = *it;
        cout << v << endl;
      }      
      for (auto it = ex_set2.rbegin(); it!=ex_set2.rend();++it) {
        auto &[k, v] = *it;
        cout << v << endl;
      }
    }
    print(good_set, "good");
    print(bad_set, "bad");
  }

  return 0;
}

/*


Gsy:35000 0 0 0 0 36000 0 0 0 0 0 40000 0 0 0 0 32000
Wj:12000 12000 12000 12000 12000 12000 12000 0 12000 12000 12000 12000 0 12000
12000 12000 12000 12000 12000 Jww:2000 Zzc:6000 6000 6000 6000 0 6000 6000 6000
0 0 6000 6000 6000 6000 6000 6000 6000 6000 6000 6000 6000 6000 6000 Dbw:3000

Gsy:excellent 143000
Wj:excellent 204000
Zzc:good 120000
Dbw:bad 3000
Jww:bad 2000

*/