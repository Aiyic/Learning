// Package log 提供基于 log/slog 的结构化日志封装。
//
// 用 slog 的 JSON handler 输出到 stdout，便于被日志采集器收集。
// trace_id 由调用方在 context 中注入，handler 自动提取并写入每条日志。
package log

import (
	"context"
	"log/slog"
	"os"
	"time"
)

type traceKey struct{}

// WithTrace 在 context 中注入 trace_id，串联一条代理链路两端的两跳日志。
func WithTrace(ctx context.Context, traceID string) context.Context {
	if traceID == "" {
		return ctx
	}
	return context.WithValue(ctx, traceKey{}, traceID)
}

// TraceFrom 从 context 取出 trace_id，没有则返回空串。
func TraceFrom(ctx context.Context) string {
	v, _ := ctx.Value(traceKey{}).(string)
	return v
}

// Init 初始化全局 slog logger。level 由环境变量 LOG_LEVEL 控制(debug/info/warn/error)。
func Init(level string) {
	var lv slog.Level
	switch level {
	case "debug":
		lv = slog.LevelDebug
	case "warn":
		lv = slog.LevelWarn
	case "error":
		lv = slog.LevelError
	default:
		lv = slog.LevelInfo
	}
	h := slog.NewJSONHandler(os.Stdout, &slog.HandlerOptions{
		Level: lv,
		ReplaceAttr: func(_ []string, a slog.Attr) slog.Attr {
			// 时间字段统一格式化为 UTC RFC3339nano，便于排序
			if a.Key == slog.TimeKey {
				if t, ok := a.Value.Any().(time.Time); ok {
					return slog.String(slog.TimeKey, t.UTC().Format(time.RFC3339Nano))
				}
			}
			return a
		},
	})
	l := slog.New(&traceHandler{h})
	slog.SetDefault(l)
}

// traceHandler 包一层，把 context 里的 trace_id 附加到每条日志。
type traceHandler struct{ slog.Handler }

func (h *traceHandler) Handle(ctx context.Context, r slog.Record) error {
	if tid := TraceFrom(ctx); tid != "" {
		r.AddAttrs(slog.String("trace_id", tid))
	}
	return h.Handler.Handle(ctx, r)
}

func (h *traceHandler) WithAttrs(attrs []slog.Attr) slog.Handler {
	return &traceHandler{h.Handler.WithAttrs(attrs)}
}
func (h *traceHandler) WithGroup(name string) slog.Handler {
	return &traceHandler{h.Handler.WithGroup(name)}
}
