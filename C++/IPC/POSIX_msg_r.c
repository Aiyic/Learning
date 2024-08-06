#include <mqueue.h>
#include <stdio.h>

int main() {
    mqd_t mq;
    char msg[1024];
    unsigned int prio;
    ssize_t bytes_read;

    // 打开消息队列
    mq = mq_open("/my_queue", O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }

    // 接收消息
    bytes_read = mq_receive(mq, msg, sizeof(msg), &prio);
    if (bytes_read == -1) {
        perror("mq_receive");
        return -1;
    }

    // 打印接收到的消息
    printf("Received message: %s\n", msg);

    // 关闭消息队列
    mq_close(mq);

    return 0;
}
