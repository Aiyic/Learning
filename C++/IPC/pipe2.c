// pipe2.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
 
#define SIZE 64
 
int main(){
 
	int ret=-1;
	int fds[2];
	char buf[SIZE];
	pid_t pid=-1;
 
	
	//创建无名管道
	ret=pipe(fds);
	if(-1==ret){
		perror("pipe");
		return 1;
	}
 
 
	//创建子进程
	pid=fork();
	if(-1 == pid){
		perror("fork");
		return 1;
	}	
 
 
	//子进程读管道
	if(0==pid){
		close(fds[1]);//关闭写端
		
		memset(buf,0,SIZE);
		ret=read(fds[0],buf,SIZE);
		if(ret<0){
			perror("read");
			exit(-1);
		}		
 
		printf("read: %s\n",buf);
 
		close(fds[0]);//关闭读端
		exit(0);//子进程退出
	}
 
 
 
	//父进程写管道
	close(fds[0]);//关闭读端
	ret=write(fds[1],"abc123",6);
	if(ret<0){
		perror("write");
		return 1;
	}
 
	printf("write:%s\n","abc123");
 
 
	close(fds[1]);//关闭写端
 
	return 0;
 
}
 
// 编译 gcc pipe2.c -o pipe2
// 运行 ./pipe2 结果如下
//