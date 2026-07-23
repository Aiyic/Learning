# proxy-asio

基于 **C++20 协程 + standalone Asio** 重写的两级网络代理服务器，与同目录下
`proxy`（muduo 回调版）、`proxy-go`（Go goroutine 版）并排，用于对比三种并发模型
处理同一代理问题的差异。

聚焦学习 C++ 协程，实现到「接入/出口两级 + 标准代理协议 + 鉴权 + 空闲超时保活」
为止（不含负载均衡、metrics 等可选项）。

## 架构

```
用户 ──HTTPS:12345/HTTP:12346──> proxy_client(接入层) ──内部隧道协议──> proxy_serve(出口层) ──> 目标服务器
```

- `src/server/main.cpp` 出口层：接收隧道连接，拨号目标后双向转发。
- `src/client/main.cpp` 接入层：面向用户，标准 HTTP/HTTPS 代理 + `Proxy-Authorization: Basic` 鉴权。

## 关键设计与并发模型对比

| 关注点 | muduo（回调） | Go（goroutine） | Asio（协程，本版） |
|---|---|---|---|
| 并发单元 | one-loop-per-thread + 回调 | goroutine-per-conn | `awaitable<void>` 协程 + `co_spawn(detached)` |
| 上下文生命周期 | `shared_ptr/weak_ptr` | goroutine 局部 | 协程帧 + `shared_ptr` 捕获，结束即析构 |
| 双向转发 | 两条回调链 | 两个 `io.Copy` goroutine | `awaitable_operators::operator||` 两个 copy 协程 |
| 空闲超时 | `circular_buffer` 时间轮 | idle reaper / `AfterFunc` | `asio::cancel_after(idle, use_awaitable)` per-op 超时 |
| 死连接检测 | 应用层 `Heartbeat\r\n` | TCP keepalive | TCP keepalive socket 选项 |
| 缓冲/读头 | `Buffer` 手动 retrieve | `bufio.Reader` | `asio::streambuf` + `async_read_until` |
| 线程安全 | 跨线程 `runInLoop` | channel / 单 goroutine 局部 | 每连接 `asio::make_strand` 串行化 |

### 协程化双向转发（tunnel/pipe.hpp）

```cpp
awaitable<void> copy_dir(tcp::socket& from, tcp::socket& to,
                         std::atomic<int64_t>& cnt, std::chrono::seconds idle) {
  std::array<char, 16384> buf;
  try {
    while (true) {
      size_t n = co_await from.async_read_some(asio::buffer(buf),
          asio::cancel_after(idle, asio::use_awaitable));   // 无活动超时即取消
      if (n == 0) co_return;
      co_await asio::async_write(to, asio::buffer(buf, n),
          asio::cancel_after(idle, asio::use_awaitable));
      cnt.fetch_add(n, std::memory_order_relaxed);
    }
  } catch (const std::system_error&) { /* EOF/取消/超时：正常结束 */ }
}

awaitable<void> pipe(tcp::socket& a, tcp::socket& b, ...) {
  using namespace asio::experimental::awaitable_operators;
  co_await (copy_dir(a,b,up,idle) || copy_dir(b,a,down,idle)); // 任一结束即整体结束
  a.close(); b.close();
}
```

`||` 让两个方向并发、任一结束自动取消另一侧；`cancel_after` 把每个 async 操作
绑定一个空闲计时器，无活动超时即抛 `operation_aborted` 被捕获拆除连接——这是 Asio
惯用的「每连接 per-op 超时」，替代时间轮 / 全局 reaper。

### 线程模型

`io_context` 由多线程 `run()` 驱动（线程数 = `hardware_concurrency`）；每条连接用
`asio::make_strand(ioc)` 创建独立 strand，accept 时把 socket 绑到 strand 上，
`co_spawn(strand, handle, detached)`。strand 保证同一连接的两个 copy 协程不会真正
并发执行，避免对同一 socket 的并发访问竞态。

## 目录结构

```
CMakeLists.txt
src/
  server/main.cpp        # proxy_serve
  client/main.cpp        # proxy_client
  lib/
    log/log.hpp          # spdlog 异步日志
    config/config.hpp    # 环境变量配置
    net.hpp              # 地址拆分 / 异步+同步解析
    proto/frame.hpp      # 隧道帧协议(协程化读写)
    auth/auth.hpp        # Basic 鉴权 + base64
    proxy/proxy.hpp      # HTTP/CONNECT 解析 + 响应构造
    tunnel/pipe.hpp      # 协程化双向转发
```

内部 lib 为 header-only（`inline`），两个 main 直接 include。

## 构建

需要 C++20 协程支持的编译器（g++ ≥ 13 / clang ≥ 16 / MSVC ≥ 19.36）。
依赖（asio / spdlog）由 CMake `FetchContent` 自动拉取。

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
# 产物：build/proxy_serve  build/proxy_client
```

Windows + MinGW 示例（本仓库验证环境：g++ 15.2 / CMake / Unix Makefiles）：

```powershell
cmake -S . -B build -G "Unix Makefiles" `
  -DCMAKE_CXX_COMPILER=(Get-Command g++).Source `
  -DCMAKE_MAKE_PROGRAM=(Get-Command make).Source
cmake --build build -j
```

Windows 下自动链接 `ws2_32`/`mswsock`（Winsock）。

## 运行

环境变量与 `proxy-go` 同名，便于对照：

```bash
# 出口层
SERVER_TUNNEL_ADDR=127.0.0.1:23456 SERVER_IDLE_TIMEOUT=120 ./build/proxy_serve

# 接入层(免鉴权)
CLIENT_HTTPS_ADDR=127.0.0.1:12345 CLIENT_HTTP_ADDR=127.0.0.1:12346 \
CLIENT_SERVER_ADDR=127.0.0.1:23456 ./build/proxy_client

# 接入层(带鉴权)
CLIENT_USERS="alice:secret,bob:pw" CLIENT_HTTP_ADDR=127.0.0.1:12348 ./build/proxy_client
```

PowerShell 下用 `$env:CLIENT_USERS="alice:secret"` 设置环境变量。

## 配置项（环境变量）

| 变量 | 默认 | 说明 |
|---|---|---|
| `LOG_LEVEL` | `info` | debug/info/warn/error |
| `CLIENT_HTTPS_ADDR` | `:12345` | HTTPS(CONNECT) 代理监听 |
| `CLIENT_HTTP_ADDR` | `:12346` | HTTP 代理监听 |
| `CLIENT_SERVER_ADDR` | `127.0.0.1:23456` | 上游 proxy_serve |
| `CLIENT_USERS` | 空(免鉴权) | `user:pass,user:pass` |
| `CLIENT_DIAL_TIMEOUT` | `5` | 拨号 proxy_serve 超时(秒) |
| `CLIENT_IDLE_TIMEOUT` | `120` | 空闲连接超时(秒) |
| `CLIENT_KEEPALIVE` | `30` | TCP keepalive 周期(秒) |
| `CLIENT_MAX_CONNS` | `1000000` | 最大并发连接 |
| `SERVER_TUNNEL_ADDR` | `:23456` | 隧道监听 |
| `SERVER_DIAL_TIMEOUT` | `5` | 拨号目标超时(秒) |
| `SERVER_IDLE_TIMEOUT` | `120` | 空闲连接超时(秒) |
| `SERVER_KEEPALIVE` | `30` | TCP keepalive 周期(秒) |
| `SERVER_MAX_CONNS` | `1000000` | 最大并发连接 |

## 使用

```bash
curl -x http://127.0.0.1:12346 http://example.com/            # HTTP 代理
curl -x http://127.0.0.1:12345 https://example.com/           # HTTPS(CONNECT)
curl -x http://alice:secret@127.0.0.1:12348 http://example.com/ # 带鉴权
```

## 验证情况

已通过端到端冒烟测试（g++ 15.2 / Windows，本地 Go HTTP 目标）：
- HTTP 代理路径 → 200
- CONNECT 隧道路径（`curl -p`）→ 200
- 鉴权：无凭据 / 错凭据 → 407，正确凭据 → 200（HTTP 与 CONNECT 均验证）

## 学习要点

- **挂起点**：每个 `co_await` 是协作式让出，与 goroutine 抢占式调度不同；同 strand 上
  多协程靠 `co_await` 交错推进。
- **错误传播**：协程内 `try/catch` 捕获 `std::system_error`，比回调里层层 `error_code`
  检查清晰。
- **取消语义**：`operation_aborted` 是关闭/超时的统一信号；`||` + `cancel_after` 处理
  「任一方向结束即拆除」。
- **生命周期**：`ConnGuard`(RAII) 管理连接计数，协程帧天然持有局部状态，无需 muduo 的
  `weak_ptr` 解耦。
- **C++ 限制**：`catch` 块内不允许 `co_await`（标准约束），失败回写走同步 `asio::write`。

## 三版同构对比

`proxy/`(muduo) · `proxy-go/`(Go) · `proxy-asio/`(本版) 三套实现逻辑同构、协议兼容，
并排阅读是并发模型最直观的学习材料。
