/* 从有名管道中，读数据 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//两个独立的进程，一个写进程另一个读进程
//写进程，创建FIFO，写入数据，退出
//读进程，读出数据，显示数据
int main()
{
    int fd;
    char buf[15];
    fd = open("./myfifo", O_RDONLY);     //打开fifo文件
    read(fd, buf, 11);                   //读数据
    printf("read: %s.\n",buf);
    close(fd);                           //关闭fifo文件 
    unlink("./myfifo");                  //删除管道 
    return 0;
}