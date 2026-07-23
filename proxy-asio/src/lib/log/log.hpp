// spdlog 异步日志封装。
//
// 单后台线程落盘，避免日志 IO 阻塞 io_context 的工作线程。
// 级别由 LOG_LEVEL 环境变量控制。
#pragma once

#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string_view>

namespace proxy::log {

inline void init(std::string_view level = "info") {
  spdlog::init_thread_pool(8192, 1);
  auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto logger = std::make_shared<spdlog::async_logger>(
      "proxy", sink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);

  if (level == "debug")      logger->set_level(spdlog::level::debug);
  else if (level == "warn")  logger->set_level(spdlog::level::warn);
  else if (level == "error") logger->set_level(spdlog::level::err);
  else                       logger->set_level(spdlog::level::info);

  logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
  spdlog::set_default_logger(std::move(logger));
}

} // namespace proxy::log
