/*

regex	表示有一个正则表达式类，比如：regex pattern("(.{3})(.{2})_(\d{4})!")

regex_match
全文匹配，要求整个字符串符合正则表达式的匹配规则。
用来判断一个字符串和一个正则表达式是否模式匹配，返回一个bool值，true为匹配，false为不匹配。
匹配的含义是目标字符串必须完全和正则表达式相匹配，不能有多余的字符，如果需要部分匹配则应使用regex_search

regex_search
搜索匹配，根据正则表达式来搜索字符串中是否存在符合规则的子字符串。
能和正则表达式相匹配就返回true

regex_replace
替换匹配，即可以将符合匹配规则的子字符串替换为其他字符串。
要求输入一个正则表达式，以及一个用于替换匹配子字符串的格式化字符串。
这个格式化字符串可以通过转义序列引用匹配子字符串中的部分内容



*/

#include <iostream>
#include <regex>

int main() {

  if (std::regex_match("subject", std::regex("(sub)(.*)"))) {
    std::cout << "string literal matched\n";
  }

  std::string s("subject");
  std::regex e("(sub)(.*)");
  if (std::regex_match(s, e)) {
    std::cout << "string object matched\n";
  }

  if (std::regex_match(s.begin(), s.end(), e)) {
    std::cout << "range matched\n";
  }

  std::cmatch cm; // same as std::match_results<const char*> cm;
  std::regex_match("subject", cm, e);
  std::cout << "string literal with " << cm.size() << " matches\n";

  std::smatch sm; // same as std::match_results<string::const_iterator> sm;
  std::regex_match(s, sm, e);
  std::cout << "string object with " << sm.size() << " matches\n";

  std::regex_match(s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";

  // using explicit flags:
  std::regex_match("subject", cm, e, std::regex_constants::match_default);

  std::cout << "the matches were: ";
  for (unsigned i = 0; i < sm.size(); ++i) {
    std::cout << "[" << sm[i] << "] ";
  }
}