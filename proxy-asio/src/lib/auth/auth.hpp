// Proxy-Authorization: Basic 鉴权。
#pragma once

#include <cctype>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace proxy::auth {

inline constexpr const char* Anonymous = "anonymous";

namespace detail {

inline std::string trim(std::string_view s) {
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
  while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))  s.remove_suffix(1);
  return std::string(s);
}

inline int b64val(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a' + 26;
  if (c >= '0' && c <= '9') return c - '0' + 52;
  if (c == '+') return 62;
  if (c == '/') return 63;
  return -1;
}

inline std::string b64decode(std::string_view s) {
  std::string out;
  out.reserve((s.size() * 3) / 4);
  int val = 0, bits = 0;
  for (char c : s) {
    if (c == '=' || c == '\r' || c == '\n' || c == ' ') continue;
    int v = b64val(c);
    if (v < 0) return {};
    val = (val << 6) | v;
    bits += 6;
    if (bits >= 8) {
      bits -= 8;
      out.push_back(static_cast<char>((val >> bits) & 0xff));
    }
  }
  return out;
}

} // namespace detail

class Authenticator {
public:
  explicit Authenticator(std::unordered_map<std::string, std::string> users)
      : users_(std::move(users)) {}

  bool auth_required() const { return !users_.empty(); }

  // 校验 Proxy-Authorization 头值，返回用户名；失败返回 nullopt。
  std::optional<std::string> authenticate(std::string_view header) const {
    if (header.empty()) {
      if (users_.empty()) return std::string(Anonymous);
      return std::nullopt;
    }
    constexpr std::string_view prefix = "Basic ";
    if (header.size() < prefix.size() || header.substr(0, prefix.size()) != prefix)
      return std::nullopt;

    auto dec = detail::b64decode(detail::trim(header.substr(prefix.size())));
    if (dec.empty()) return std::nullopt;
    auto colon = dec.find(':');
    if (colon == std::string::npos) return std::nullopt;

    std::string user = dec.substr(0, colon);
    std::string pass = dec.substr(colon + 1);
    if (users_.empty()) return user; // 免鉴权但客户端带了凭据，接受其用户名
    auto it = users_.find(user);
    if (it == users_.end() || it->second != pass) return std::nullopt;
    return user;
  }

private:
  std::unordered_map<std::string, std::string> users_;
};

} // namespace proxy::auth
