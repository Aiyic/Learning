#include <bits/stdc++.h>
using namespace std;

struct nvidia {
  int number;
  int ti;
  int freq;

  bool operator<(nvidia b) const {
    if (number != b.number) {
      return number > b.number;
    }
    if (ti != b.ti) {
      return ti > b.ti;
    }
    return freq > b.freq;
  }

  bool operator==(nvidia b) const {
    return number == b.number && ti == b.ti && freq == b.freq;
  }
};

int main() {
  multimap<nvidia, string> mp;
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    string num;
    int number = 0;
    while (ss >> num) {
      if (num.length() == 4 
          && num[0] >= '0' && num[0] <= '9'
          && num[1] == '0' 
          && num[2] >= '0' && num[2] <= '9'
          && num[3] == '0' ) {
        number = stoi(num);
        break;
      }
    }
    string ti;
    int tiflag = 0;
    ss >> ti;
    if (ti.length() == 2 && ti[0] == 'T' && ti[1] == 'i') {
      tiflag = 1;
    }
    string tmp;
    string freq;
    int frequent;
    getline(ss, tmp);
    while(tmp.find('@') != string::npos){
      tmp = tmp.substr(tmp.find('@')+1);
    }
    stringstream ss2(tmp);
    getline(ss2, freq);
    frequent = stoi(freq);

    mp.insert({{number, tiflag, frequent}, s});
  }

  cout << endl;
  nvidia best = mp.begin()->first;
  for (auto &[nv, str] : mp) {
    if (nv == best) {
      cout << str << endl;
    }
  }
  return 0;
}

/*

NVIDIA GeForce RTX 4090 Founders Edition @ 2520 MHz
NVIDIA GeForce RTX 4090 Founders Edition Rev. 2 @ 2520 MHz
NVIDIA GeForce RTX 4080 Founders Edition @ 2505 MHz
NVIDIA GeForce RTX 4070 Founders Edition @ 2475 MHz
NVIDIA GeForce RTX 4060 Ti Founders Edition @ 2535 MHz


My 3080 Ti Is Excellent @ 1000 MHz
RTX 9999 RTX 2080 Ti RTX @ 1000 MHZ
Ti Ti Ti 3080 (?) Ti Ti Ti @ 1000 MHZ
H@ppy H@cking 3080 Ti @ 1000 MHz


H@ppy H@cking 3080 Ti @ @ @ 1000 MHz


*/