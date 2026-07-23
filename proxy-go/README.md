# proxy-go

基于 Go 重写的两级网络代理服务器，对应同目录下基于 muduo 的 C++ 版本。
项目聚焦学习目的，实现到「接入/出口两级 + 标准代理协议 + 鉴权 + 超时保活 + 可观测性」为止
（不含负载均衡及后续可选项）。

## 架构

```
用户 ──HTTPS:12345/HTTP:12346──> proxy_client(接入层) ──内部隧道协议──> proxy_serve(出口层) ──> 目标服务器
                                      鉴权 / 解析 CONNECT/Host          DNS+拨号 / 双向转发
                                      / 零拷贝转发 / idle 回收           / 零拷贝转发 / idle 回收
```

- `cmd/client` 接入层：面向用户，标准 HTTP/HTTPS 代理协议，`Proxy-Authorization: Basic` 鉴权。
- `cmd/server` 出口层：接收隧道连接，解析目标后拨号真实服务器并双向转发。

## 关键设计与 muduo 版的对比

| 关注点 | muduo 版 | Go 版(本仓库) |
|---|---|---|
| 并发模型 | one-loop-per-thread + 回调 + weak_ptr 解耦 | goroutine-per-conn，状态天然局部，无循环引用问题 |
| 零拷贝转发 | `Buffer::retrieveAllAsString` 拷贝 | `FlowConn.WriteTo` 委派 `(*TCPConn).WriteTo` 走 `sendfile` |
| 流量统计 | 手动 `AllConnDataFlowsMap` + 析构聚合 | `WriteTo` 内原子计数 + Prometheus counter |
| 心跳保活 | 应用层 `Heartbeat\r\n` 往返 | TCP keepalive，内核态探活，零应用开销 |
| 空闲回收 | `boost::circular_buffer` 时间轮 + `ConnEntry` 析构 shutdown | 基于活动时间戳的 idle reaper，周期扫描超时即 Close |
| 代理协议 | 自定义 `User:` 头 | 标准 `CONNECT`/绝对 URI + `Proxy-Authorization` |
| 日志 | muduo `AsyncLogging` | `log/slog` 结构化 JSON + trace_id |
| 监控 | 无 | Prometheus `/metrics` |

### 零拷贝 + 流量统计如何兼得

`FlowConn` 包装 `*net.TCPConn` 并实现 `io.WriterTo`：其 `WriteTo` 解包对端 `FlowConn`
拿到底层 `*TCPConn`，再调用 `(*TCPConn).WriteTo(dst)` —— 当两端都是 `*TCPConn` 时内核走
`sendfile` 零拷贝；返回后在 `WriteTo` 内原子累加字节数并刷新活跃时间。
`io.Copy` 优先调用 `src.WriteTo`，因此双向 `Pipe` 的两个方向都命中零拷贝且统计完整。

少量控制向写入(200 响应、HTTP 转发头)经 `Write` 走，方向与主数据流相反，**不计入字节统计**，
仅刷新活跃时间，避免标签错位；这部分字节数量级远小于业务流量。

## 目录结构

```
cmd/
  client/main.go   # 接入层入口
  server/main.go   # 出口层入口
internal/
  proto/    # 两级间隧道帧协议(CONNECT 握手帧 + 状态响应)
  auth/     # Proxy-Authorization: Basic 鉴权
  proxy/    # HTTP/HTTPS 代理请求解析(CONNECT/绝对 URI/Host)
  conn/     # FlowConn：零拷贝 + 计数 + 活跃度 + keepalive
  idle/     # idle reaper：基于活动时间戳的空闲连接回收
  tunnel/   # 双向 Pipe
  metrics/  # Prometheus 指标
  log/      # slog 封装 + trace_id
  config/   # 环境变量配置
```

## 构建与运行

```bash
go build -o bin/proxy_serve ./cmd/server
go build -o bin/proxy_client ./cmd/client
```

启动(两个进程)：

```bash
# 出口层
SERVER_TUNNEL_ADDR=127.0.0.1:23456 SERVER_METRICS_ADDR=127.0.0.1:9090 ./bin/proxy_serve

# 接入层(免鉴权)
CLIENT_HTTPS_ADDR=127.0.0.1:12345 CLIENT_HTTP_ADDR=127.0.0.1:12346 \
CLIENT_SERVER_ADDR=127.0.0.1:23456 CLIENT_METRICS_ADDR=127.0.0.1:9091 ./bin/proxy_client

# 接入层(带鉴权)
CLIENT_USERS="alice:secret,bob:pw" CLIENT_HTTP_ADDR=127.0.0.1:12348 ... ./bin/proxy_client
```

PowerShell 下设置环境变量用 `$env:CLIENT_USERS="alice:secret"`。

## 配置项(环境变量)

| 变量 | 默认 | 说明 |
|---|---|---|
| `LOG_LEVEL` | `info` | debug/info/warn/error |
| `CLIENT_HTTPS_ADDR` | `:12345` | HTTPS(CONNECT) 代理监听 |
| `CLIENT_HTTP_ADDR` | `:12346` | HTTP 代理监听 |
| `CLIENT_SERVER_ADDR` | `127.0.0.1:23456` | 上游 proxy_serve 地址 |
| `CLIENT_METRICS_ADDR` | `:9091` | 接入层 metrics |
| `CLIENT_USERS` | 空(免鉴权) | `user:pass,user:pass` |
| `CLIENT_DIAL_TIMEOUT` | `5s` | 拨号 proxy_serve 超时 |
| `CLIENT_IDLE_TIMEOUT` | `120s` | 空闲连接超时 |
| `CLIENT_KEEPALIVE` | `30s` | TCP keepalive 周期 |
| `CLIENT_MAX_CONNS` | `1000000` | 最大并发连接 |
| `SERVER_TUNNEL_ADDR` | `:23456` | 隧道监听 |
| `SERVER_METRICS_ADDR` | `:9090` | 出口层 metrics |
| `SERVER_DIAL_TIMEOUT` | `5s` | 拨号目标超时 |
| `SERVER_IDLE_TIMEOUT` | `120s` | 空闲连接超时 |
| `SERVER_KEEPALIVE` | `30s` | TCP keepalive 周期 |
| `SERVER_MAX_CONNS` | `1000000` | 最大并发连接 |

## 使用

```bash
# HTTP 代理
curl -x http://127.0.0.1:12346 http://example.com/

# HTTPS 代理(CONNECT 隧道)
curl -x http://127.0.0.1:12345 https://example.com/

# 带鉴权
curl -x http://alice:secret@127.0.0.1:12348 http://example.com/
```

## 指标

`GET http://<metrics_addr>/metrics`：

- `proxy_active_connections{layer}` 活跃连接数
- `proxy_bytes_total{layer,user,dir}` 累计转发字节(up/down)
- `proxy_requests_total{layer,user,proto,result}` 请求计数
- `proxy_conn_duration_seconds{layer,proto}` 连接时长直方图

## 验证情况

已通过端到端冒烟测试：
- HTTP 代理路径(`-x http://...:12346`) → 200
- CONNECT 隧道路径(`curl -p -x http://...:12345`) → 200
- 鉴权：无/错凭据 → 407，正确凭据 → 200
- metrics 字节计数与请求计数标签正确
