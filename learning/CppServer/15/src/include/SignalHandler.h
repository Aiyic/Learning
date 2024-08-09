/**
 * @file Signal.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-07
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include <csignal>
#include <functional>
#include <map>

std::map<int, std::function<void()>> handlers;
void SignalHandler(int sig) { handlers[sig](); }

struct Signal {
  static void Setsignal(int sig, const std::function<void()> &handler) {
    handlers[sig] = handler;
    ::signal(sig, SignalHandler);
  }
};
