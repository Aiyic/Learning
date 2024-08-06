#include "shm.h"

int main(int argc, char **argv)
{
    struct Shared *ptr;
    struct stat buf;
    sem_t *mutex;
    int fd;
    int nloop;
    int i;

    fd = shm_open(SHM_FILE, O_RDWR, 0);    //读写方式打开shm fd
    fstat(fd, &buf);    //获取shm fd信息
    /*
        struct stat     //shm仅下列4个信息有效
        {
            mode_t st_mode;  //用户访问权限
            uid_t  st_uid;   //user id of owner
            gid_t  st_gid;   //group id of owner
            off_t  st_size;  //文件大小
        };
    
    */
    ptr = (struct Shared*)mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    mutex = sem_open(SEM_PATH, 0);  //0是标志位，不是信号量值！！！

    for (i = 0; i < 100000; i++)
    {
        sem_wait(mutex);     //不使用信号量同步会造成竟态
        printf("pid %d: %d\n", getpid(), ptr->count++);
        sem_post(mutex);
    }
    // 使用./#Build/shm_client & ./#Build/shm_client & ./#Build/shm_client同时调试程序
    return 0;
}