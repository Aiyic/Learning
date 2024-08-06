/* 创建有名管道，写数据 */
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
    int ret = mkfifo("./myfifo", 0777);       //创建fifo文件
    int fd = open("./myfifo", O_WRONLY);    //打开fifo文件
    ret = write(fd, "hello fifo", 11);    //写入数据
    close(fd);//关闭fifo文件   
    return 0;     
}