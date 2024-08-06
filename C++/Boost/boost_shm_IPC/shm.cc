#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>

int main() {
  // 第一个参数为打开或创建
  // 第二个为shm名
  // 第三个为读写方式
  boost::interprocess::shared_memory_object shdmem(
      boost::interprocess::open_or_create, "Highscore",
      boost::interprocess::read_write);
  // 初始化shm大小
  shdmem.truncate(1024);

  // 映射到自己的地址空间
  boost::interprocess::mapped_region region(shdmem,
                                            boost::interprocess::read_write);
  // 类型强转为对象指针
  int *i1 = static_cast<int *>(region.get_address());
  // 使用
  std::cout << *i1 << std::endl;
  // 重复映射对应的虚拟地址不同，但指向的都是同一shm空间
  boost::interprocess::mapped_region region2(shdmem,
                                             boost::interprocess::read_only);
  int *i2 = static_cast<int *>(region2.get_address());
  std::cout << *i2 << std::endl;
  // 修改i1的值，i2改变
  *i1 = 90;
  std::cout << *i2 << std::endl;

  // 如果 remove() 没有被调用, 那么，即使进程终止，共享内存还会一直存在。
  bool removed = boost::interprocess::shared_memory_object::remove("Highscore");
  std::cout << removed << std::endl;
}

// boost::interprocess::shared_memory_object 的构造函数需要三个参数。
// 第一个参数指定共享内存是要创建或打开。 上面的例子实际上是指定了两种方式：用
// boost::interprocess::open_or_create
// 作为参数，共享内存如果存在就将其打开，否则创建之。

// 假设之前已经创建了共享内存，现打开前面已经创建的共享内存。
// 为了唯一标识一块共享内存，需要为其指定一个名称，传递给
// boost::interprocess::shared_memory_object
// 构造函数的第二个参数指定了这个名称。

// 第三个，也就是最后一个参数指示应用程序如何访问共享内存。
// 例子应用程序能够读写共享内存，这是因为最后的一个参数是
// boost::interprocess::read_write。

// 在创建一个 boost::interprocess::shared_memory_object
// 类型的对象后，相应的共享内存就在操作系统中建立了。
// 可是此共享内存区域的大小被初始化为0.为了使用这块区域，需要调用 truncate()
// 函数，以字节为单位传递请求的共享内存的大小。
// 对于上面的例子，共享内存提供了1,024字节的空间。

// 请注意，truncate() 函数只能在共享内存以 boost::interprocess::read_write
// 方式打开时调用。 如果不是以此方式打开，将抛出
// boost::interprocess::interprocess_exception 异常。

// 为了调整共享内存的大小，truncate() 函数可以被重复调用。

// 在创建共享内存后，get_name() 和 get_size()
// 函数可以分别用来查询共享内存的名称和大小。

// 由于共享内存被用于应用程序之间交换数据，所以每个应用程序需要映射共享内存到自己的地址空间上，这是通过
// boost::interprocess::mapped_region 类实现的。

// 你也许有些奇怪，为了访问共享内存，要使用两个类。
// 是的，boost::interprocess::mapped_region
// 还能映射不同的对象到具体应用的地址空间。 如 Boost.Interprocess 提供
// boost::interprocess::file_mapping 类实际上代表特定文件的共享内存。 所以
// boost::interprocess::file_mapping 类型的对象对应一个文件。
// 向这个对象写入的数据将自动保存关联的物理文件上。 由于
// boost::interprocess::file_mapping 不必加载整个文件，但却可以使用
// boost::interprocess::mapped_region
// 将任意部分映射到地址空间，所以就能处理几个GB的文件，而这个文件在32位系统上是不能全部加载到内存上的。
