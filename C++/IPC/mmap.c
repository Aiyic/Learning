/*

成功返回映射内存的起始地址，失败返回MAP_FAILED
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

addr    指定映射内存的起始地址，通常设为NULL，让内核自己决定起始地址
len     是被映射到调用进程地址空间中的字节数，它从被映射文件fd开头起第offset个字节处开始算，offset通常设为0，下图展示了这个映射关系
prot    指定对映射内存区的保护，通常设为PROT_READ | PROT_WRITE
flags   必须在MAP_SHARED和MAP_PRIVATE这两个标志中选择指定一个，进程间共享内存需要使用MAP_SHARED
可移植的代码应把addr设为NULL，并且flags不指定MAP_FIXED


默认情况下，内核采用虚拟内存算法保持内存映射文件与内存映射区的同步，前提是指定了MAP_SHARED标志，但这种同步可能不是立即生效的，而是在随后某个时间进行。
但有时候我们修改完数据并进行下一步操作之前，需要确认数据已经同步完成，这时可调用msync函数。

成功返回0，失败返回-1
int msync(void *addr, size_t len, int flags);

MS_ASYNC    执行异步写，msync立即返回
MS_SYNC     执行同步写，msync等同步完成才返回

*/
