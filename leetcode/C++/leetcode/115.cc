
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
#if 0
  static int numDistinct(const string &s, const string &t) {
    int n = s.size();
    int m = t.size();
    const int mod = 1e9 + 7;
    // vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    unordered_map<char, vector<int>> rec;
    auto find_all_char = [&](char ch) {
      if (rec.find(ch) == rec.end()) {
        vector<int> res;
        int idx = 0;
        for (int i = 0; i < n; ++i) {
          if (s[i] == ch) {
            res.push_back(i);
          }
        }
        rec[ch] = res;
      }
      return rec[ch];
    };
    for (int i = 0; i <= n; ++i) {
      // dp[i][0] = 1;
      dp[0][i] = 1;
    }
    for (int j = 0; j < m; ++j) {
      auto set = find_all_char(t[j]);
      if (set.empty()) {
        return 0;
      }
      int res = 0;
      int now = *set.begin() + 1;
      auto it_r = set.begin();
      while (now <= n) {
        if (it_r != set.end() && now - 1 >= *it_r) {
          // res += dp[now - 1][j];
          res += dp[j][now - 1];
          res %= mod;
          // dp[now][j + 1] = (dp[now - 1][j + 1] + dp[now - 1][j]) % mod;
          it_r++;
        }
        // else {
        //   dp[now][j + 1] = dp[now - 1][j + 1];
        // }
        // dp[now][j + 1] = res;
        dp[j + 1][now] = res;
        now++;
      }
    }
    return dp[m][n];
  }
#else
  static int numDistinct(const string &s, const string &t) {
    int n = s.size();
    int m = t.size();
    const int mod = 1e9 + 7;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
      dp[0][i] = 1;
    }
    for (int j = 0; j < m; ++j) {
      for(int i = 1; i<=n; ++i){
        if (t[j] == s[i-1]) {
          dp[j + 1][i] = (dp[j + 1][i - 1] + dp[j][i - 1]) % mod;
        }
        else {
          dp[j + 1][i] = dp[j + 1][i - 1];
        }
      }
    }
    return dp[m][n];
  }
#endif
};

int main() {
  auto x = Solution::numDistinct("aacaacca", "ca");        // 5
  auto xx = Solution::numDistinct("babgbag", "bag");       // 5
  auto xxx = Solution::numDistinct("aabb", "ab");          // 4
  auto xxxx = Solution::numDistinct("b", "a");             // 0
  auto xxxxx = Solution::numDistinct("rabbbit", "rabbit"); // 3
  string s1 =
      "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeu"
      "qnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqk"
      "pabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggl"
      "eiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsz"
      "tuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneeh"
      "dwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykg"
      "scxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsx"
      "zylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhj"
      "cslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwy"
      "iglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjx"
      "vhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvef"
      "ugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlc"
      "ntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaie"
      "hlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo";
  string s2 = "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys";
  auto xxxxxx = Solution::numDistinct(s1, s2); // 543744000
  string s3 =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  string s4 =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  auto xxxxxxx = Solution::numDistinct(s3, s4); // 0
  cout << (10^9+7);
  return 0;
}

/*
s[0 .. i] =_= t[0 .. j]
dp[i][j] = {end, .. }
dp[i][j-1] = {end, .. }  find(t[j]) = { x, .. }

dp[i][j] =


aabb
a b
 ab
a  b
 a b
*/
