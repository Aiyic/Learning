#include <mqueue.h>
#include <stdio.h>

int main() {
    mqd_t mq;
    char msg[] = "Hello, POSIX message queue!";
    unsigned int prio = 1;

    // 打开消息队列
    mq = mq_open("/my_queue", O_WRONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }

    // 发送消息
    if (mq_send(mq, msg, sizeof(msg), prio) == -1) {
        perror("mq_send");
        return -1;
    }

    // 关闭消息队列
    mq_close(mq);

    return 0;
}
