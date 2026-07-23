// HTTP/HTTPS 代理请求解析与响应构造。
//
// 输入为已通过 async_read_until 读到的完整请求头(含尾部 \r\n\r\n)。
// HTTP 转发时剥除代理专有头(Proxy-Authorization/Proxy-Connection)并将绝对 URI
// 转为 origin-form。
#pragma once

#include <cctype>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace proxy::proxyx {

struct Request {
  std::string method;
  std::string target;      // host:port
  bool is_connect = false;
  std::string auth_header; // Proxy-Authorization 原始值
  std::string forward_head;// HTTP 转发头(CONNECT 为空)
};

// 解析请求头。失败返回 nullopt。
inline std::optional<Request> parse_request(std::string_view head) {
  // 切行
  std::vector<std::string_view> lines;
  std::string_view::size_type pos = 0;
  while (pos < head.size()) {
    auto nl = head.find("\r\n", pos);
    if (nl == std::string_view::npos) break;
    lines.push_back(head.substr(pos, nl - pos));
    pos = nl + 2;
  }
  if (lines.empty()) return std::nullopt;

  // 请求行
  std::string_view line0 = lines[0];
  auto sp1 = line0.find(' ');
  auto sp2 = (sp1 == std::string_view::npos) ? std::string_view::npos : line0.find(' ', sp1 + 1);
  if (sp1 == std::string_view::npos || sp2 == std::string_view::npos) return std::nullopt;
  std::string method(line0.substr(0, sp1));
  std::string uri(line0.substr(sp1 + 1, sp2 - sp1 - 1));
  std::string proto(line0.substr(sp2 + 1));

  Request req;
  req.method = std::move(method);

  std::string host;
  std::vector<std::string> kept;
  for (std::size_t i = 1; i < lines.size(); ++i) {
    std::string_view h = lines[i];
    if (h.empty()) continue;
    auto colon = h.find(':');
    if (colon == std::string_view::npos) continue;
    std::string name(h.substr(0, colon));
    std::string val;
    { // trim leading space of value
      std::string_view v = h.substr(colon + 1);
      while (!v.empty() && (v.front() == ' ' || v.front() == '\t')) v.remove_prefix(1);
      val = std::string(v);
    }
    // 小写比较头部名
    std::string lname = name;
    for (auto& ch : lname) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));

    if (lname == "host") {
      host = val;
      kept.push_back(name + ": " + val);
    } else if (lname == "proxy-authorization") {
      req.auth_header = val; // 不转发
    } else if (lname == "proxy-connection") {
      // 丢弃
    } else {
      kept.push_back(name + ": " + val);
    }
  }

  if (req.method == "CONNECT") {
    req.is_connect = true;
    req.target = uri; // CONNECT 的 URI 即 host:port
    return req;
  }

  // HTTP: 处理绝对 URI → origin-form
  std::string origin_uri = uri;
  if (uri.find("://") != std::string::npos) {
    auto scheme_end = uri.find("://");
    std::string after = uri.substr(scheme_end + 3);
    std::string authority;
    std::string path;
    auto slash = after.find('/');
    if (slash == std::string::npos) {
      authority = after;
      path = "/";
    } else {
      authority = after.substr(0, slash);
      path = after.substr(slash);
    }
    if (authority.empty()) return std::nullopt;
    req.target = authority;
    origin_uri = path;
    if (req.target.find(':') == std::string::npos) req.target += ":80";
  } else {
    if (host.empty()) return std::nullopt;
    req.target = host;
    if (req.target.find(':') == std::string::npos) req.target += ":80";
  }

  std::string out;
  out.reserve(128);
  out += req.method;
  out += ' ';
  out += origin_uri;
  out += ' ';
  out += proto;
  out += "\r\n";
  for (const auto& h : kept) { out += h; out += "\r\n"; }
  out += "\r\n";
  req.forward_head = std::move(out);
  return req;
}

// --- 面向用户的响应 ---

inline std::string connect_ok_response() {
  return "HTTP/1.1 200 Connection Established\r\n\r\n";
}

inline std::string auth_required_response(std::string_view realm = "proxy") {
  std::string body = "Proxy Authentication Required\n";
  std::string r(realm);
  std::string resp =
      "HTTP/1.1 407 Proxy Authentication Required\r\n"
      "Proxy-Authenticate: Basic realm=\"" + r + "\"\r\n"
      "Content-Type: text/plain; charset=utf-8\r\n"
      "Content-Length: " + std::to_string(body.size()) + "\r\n"
      "Connection: close\r\n\r\n" + body;
  return resp;
}

inline std::string bad_gateway_response() {
  std::string body = "Bad Gateway\n";
  std::string resp =
      "HTTP/1.1 502 Bad Gateway\r\n"
      "Content-Type: text/plain; charset=utf-8\r\n"
      "Content-Length: " + std::to_string(body.size()) + "\r\n"
      "Connection: close\r\n\r\n" + body;
  return resp;
}

} // namespace proxy::proxyx
