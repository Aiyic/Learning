// 环境变量配置，与 Go 版环境变量同名以便对照运行。
#pragma once

#include <algorithm>
#include <cstdlib>
#include <string>
#include <string_view>
#include <unordered_map>

namespace proxy::config {

struct ClientConfig {
  std::string https_addr   = ":12345";
  std::string http_addr    = ":12346";
  std::string server_addr  = "127.0.0.1:23456";
  int dial_timeout_sec = 5;
  int idle_timeout_sec = 120;
  int keepalive_sec    = 30;
  int max_conns        = 1000000;
  std::unordered_map<std::string, std::string> users;
};

struct ServerConfig {
  std::string tunnel_addr = ":23456";
  int dial_timeout_sec = 5;
  int idle_timeout_sec = 120;
  int keepalive_sec    = 30;
  int max_conns        = 1000000;
};

struct Config {
  std::string log_level = "info";
  ClientConfig client;
  ServerConfig server;
};

inline std::string getenv_str(std::string_view key, std::string def) {
  const char* v = std::getenv(key.data());
  return (v && *v) ? std::string(v) : def;
}

inline int getenv_int(std::string_view key, int def) {
  const char* v = std::getenv(key.data());
  if (!v || !*v) return def;
  try { return std::stoi(v); } catch (...) { return def; }
}

inline std::unordered_map<std::string, std::string>
parse_users(std::string_view s) {
  std::unordered_map<std::string, std::string> m;
  size_t i = 0;
  while (i < s.size()) {
    size_t comma = s.find(',', i);
    std::string_view pair = s.substr(i, (comma == std::string_view::npos ? s.size() : comma) - i);
    if (auto colon = pair.find(':'); colon != std::string_view::npos) {
      auto trim = [](std::string_view x) {
        while (!x.empty() && std::isspace(static_cast<unsigned char>(x.front()))) x.remove_prefix(1);
        while (!x.empty() && std::isspace(static_cast<unsigned char>(x.back())))  x.remove_suffix(1);
        return std::string(x);
      };
      m[trim(pair.substr(0, colon))] = trim(pair.substr(colon + 1));
    }
    if (comma == std::string_view::npos) break;
    i = comma + 1;
  }
  return m;
}

inline Config from_env() {
  Config c;
  c.log_level = getenv_str("LOG_LEVEL", "info");

  c.client.https_addr   = getenv_str("CLIENT_HTTPS_ADDR", ":12345");
  c.client.http_addr    = getenv_str("CLIENT_HTTP_ADDR", ":12346");
  c.client.server_addr  = getenv_str("CLIENT_SERVER_ADDR", "127.0.0.1:23456");
  c.client.dial_timeout_sec = getenv_int("CLIENT_DIAL_TIMEOUT", 5);
  c.client.idle_timeout_sec = getenv_int("CLIENT_IDLE_TIMEOUT", 120);
  c.client.keepalive_sec    = getenv_int("CLIENT_KEEPALIVE", 30);
  c.client.max_conns        = getenv_int("CLIENT_MAX_CONNS", 1000000);
  c.client.users            = parse_users(getenv_str("CLIENT_USERS", ""));

  c.server.tunnel_addr      = getenv_str("SERVER_TUNNEL_ADDR", ":23456");
  c.server.dial_timeout_sec = getenv_int("SERVER_DIAL_TIMEOUT", 5);
  c.server.idle_timeout_sec = getenv_int("SERVER_IDLE_TIMEOUT", 120);
  c.server.keepalive_sec    = getenv_int("SERVER_KEEPALIVE", 30);
  c.server.max_conns        = getenv_int("SERVER_MAX_CONNS", 1000000);

  return c;
}

} // namespace proxy::config
