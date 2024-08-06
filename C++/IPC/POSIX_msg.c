#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>

// mqd_t mq_open(const char *name,int oflag,mode_t mode,struct mq_attr *attr);
/*

struct mq_attr{
    long mq_flags;      //阻塞标志， 0或O_NONBLOCK
    long mq_maxmsg;     //最大消息数
    long mq_msgsize;    //每个消息最大大小
    long mq_curmsgs;    //当前消息数
};

*/
#if 1

int main() {
    mqd_t mq;
    struct mq_attr attr;

    // 设置消息队列属性
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    // 创建消息队列
    mq = mq_open("/my_queue", O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return -1;
    }

    // 关闭消息队列
    mq_close(mq);

    return 0;
}

#else

int main() {
    mqd_t mq;

    // 删除消息队列
    mq = mq_unlink("/my_queue");
    if (mq == (mqd_t)-1) {
        perror("mq_del");
        return -1;
    }

    return 0;
}

#endif
