#include <iostream>
#include <cstring>
#include <errno.h>
 
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
using namespace std;
 
#define SHM_FILE    "shm_file"
#define SEM_PATH    "sem_mmap"

struct Shared
{
    int count;
};
