/**
 * @file Buffer.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include <memory>
#include <vector>
#include "common.h"

class Buffer {
 public:
  DISALLOW_COPY_AND_MOVE(Buffer);
  Buffer() = default;
  ~Buffer() = default;

  [[nodiscard]] const std::string &GetBuf() const;
  [[nodiscard]] const char *CStr() const;
  void SetBuf(const char *buf);

  [[nodiscard]] size_t Size() const;
  void Append(const char *_str, int _size);
  void Clear();

 private:
  std::string buf_;
};
