/*名称：fifo_read.c
 *作者：赵陈亮
 *时间：2018.2.27
 *功能：在读管道的程序里创建有名管道，通过阻塞的方式读取另一进程
 写入到管道的数据。
 *知识点：pipe管道是无名管道，它只能用于具有亲缘关系的进程之间，
 *这就大大地限制了管道的使用。有名管道fifo的出现突破了这种限制，
 *它可以使互不相关的两个进程实现彼此通信。该管道可以通过路径名来指出，
 *并且在文件系统中是可见的。在建立了管道之后，两个进程就可以把它当作
 *普通文件一样进行读写操作，使用非常方便。不过值得注意的是，FIFO 是
 *严格地遵循先进先出规则的，对管道及 FIFO 的读总是从开始处返回数据，
 *对它们的写则把数据添加到末尾，它们不支持如 lseek()等文件定位操作。
 *有名管道的创建可以使用函数 mkfifo() ,还可以在命令行使用“mknod 管道名 p”
 *来创建有名管道。该函数类似文件中的 open()操作，可以指定管道的路径和
 *打开的模式。在创建管道成功之后，就可以使用 open()、read()和 write()这些函数了。
 *与普通文件的开发设置一样，对于为读而打开的管道可在 open()中设置 O_RDONLY，
 *对于为写而打开的管道可在 open()中设置 O_WRONLY，在这里与普通文件不同的是
 *阻塞问题。由于普通文件的读写时不会出现阻塞问题，而在管道的读写中却有阻塞的
 *可能，这里的非阻塞标志可以在 open()函数中设定为 O_NONBLOCK。
 */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <limits.h> 
#define MYFIFO "/data/data/com.termux/files/home/leon/linux-c/linux-c/9linux-C/fifo1" /* 有名管道文件名*/ 
#define MAX_BUFFER_SIZE PIPE_BUF /*定义在于 limits.h 中*/ 

int main()
{
 char buff[MAX_BUFFER_SIZE];
 int fd;
 int nread;

 /* 判断有名管道是否已存在，F_OK(exist?),R_OK(readable),W_OK(writable),
  * X_OK(executable);若尚未创建，则以相应的权限创建
  */
 if (access(MYFIFO, F_OK) == -1){/*if not exist*/
   if ((mkfifo(MYFIFO, 0666) < 0) && (errno != EEXIST)){/*creat file with mode of 0666*/
	 printf("Cannot create fifo file\n");
	 exit(1);
   }
 }

 /* 以只读阻塞方式打开有名管道 */
 fd = open(MYFIFO, O_RDONLY);
 if (fd == -1){
   printf("Open fifo file error\n");
   exit(1);
 }

 while (1){
   memset(buff, 0, sizeof(buff));
   if ((nread = read(fd, buff, MAX_BUFFER_SIZE)) > 0){
	 printf("Read '%s' from FIFO\n", buff);
   }
 }
 close(fd);
 exit(0);
}
