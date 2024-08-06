#include"shm.h"

int main()
{
    struct Shared *ptr;
    sem_t *mutex;
    int fd;

    shm_unlink(SHM_FILE);   //清空同名shm
    fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);    //创建shm fd
    ftruncate(fd, sizeof(struct Shared));       //设置shm大小
    ptr = (struct Shared*)mmap(NULL, sizeof(struct Shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);     //mmap映射到当前进程空间
    close(fd);      //获取了ptr指针指向共享内存后，shm的fd不需要了

    sem_unlink(SEM_PATH);   //清空同名sem
    mutex = sem_open(SEM_PATH, O_CREAT, 0666, 1);   //创建sem，保护多个client同时访问(写)共享内存
    sem_close(mutex);       

    return 0;
}