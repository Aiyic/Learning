#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc,char* argv[])
{
	pid_t pid;
	
	int fd[2];//定义管道的读、写端文件描述符
	int ret;
	
	char* str = "hello pipe\n";//指定写数据
	char buf[1024];//定义接收缓冲区
	
	ret = pipe(fd);//调用pipe()函数就已将管道打开
	
	if(ret == -1)
	{
		perror("pipe error");
		exit(1);
	}
	
	pid = fork();
	
	if(pid > 0)//父进程
	{
		close(fd[0]);
		write(fd[1],str,strlen(str));//写到管道中
		close(fd[1]);
	}
	else if(pid == 0)//子进程
	{
		close(fd[1]);
		ret = read(fd[0],buf,sizeof(buf));//从管道中的读，返回读到的字节数
		write(STDOUT_FILENO,buf,ret);//写到标准输出
		close(fd[0]);
	}
	
	return 0;
}
