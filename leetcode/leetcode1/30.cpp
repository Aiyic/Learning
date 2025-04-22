#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  vector<int> findSubstring(const string &s, vector<string> &words) {
    int count = words.size();
    int word_len = words[0].size();
    int n = s.length();
    vector<int> res;

    for (int pos = 0; pos < word_len; pos++) { // 0,1,2,3
      if (pos + word_len * count > n) {
        break;
      }
      unordered_map<string, int> words_map;
      words_map.clear();
      for (auto &word : words) {
        words_map[word]++;
      }

      int flag = 0; // flag = words_map.size() means all words are found
      for (int k = pos; k < pos + word_len * count;
           k += word_len) { // windows start
        string sub = string(s, k, word_len);
        if (words_map.contains(sub)) {
          words_map[sub]--;
          if (words_map[sub] == 0) {
            flag++;
          } else if (words_map[sub] == -1) {
            flag--;
          }
        }
      }

      int left = pos;
      int right = pos + (count * word_len);
      if (flag == words_map.size()) {
        res.push_back(left);
      }

      while (right <= n - word_len) {
        string left_word = string(s, left, word_len);
        string right_word = string(s, right, word_len);

        if (words_map.contains(left_word)) {
          if (words_map[left_word] == 0) {
            flag--;
          } else if (words_map[left_word] == -1) {
            flag++;
          }
          words_map[left_word]++;
        }
        if (words_map.contains(right_word)) {
          words_map[right_word]--;
          if (words_map[right_word] == 0) {
            flag++;
          } else if (words_map[right_word] == -1) {
            flag--;
          }
        }
        left += word_len;
        right += word_len;
        if (flag == words_map.size()) {
          res.push_back(left);
        }
      }
    }
    return res;
  }
};

int main() {
  Solution x;
  string s = "a";
  vector<string> words = {"a"};
  //   string s = "barfoofoobarthefoobarman";
  //   vector<string> words = {"bar", "foo", "the"};

  vector<int> a = x.findSubstring(s, words);
  return 0;
}
