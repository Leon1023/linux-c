/*名称：fifo_write.c
 *作者：赵陈亮
 *时间：2018.2.27
 *功能：在写管道的程序里写入数据到有名管道，通过阻塞的方式写入数据到管道。
 *知识点：为了能够较好地观察运行结果，配合fifo_read.c，需要把这两个程序分
 *别在两个终端里运行，在这里首先启动读管道程序。读管道进程在建立管道之后
 *就开始循环地从管道里读出内容，如果没有数据可读，则一直阻塞到写管道进程
 *向管道写入数据。在启动了写管道程序后，读进程能够从管道里读出用户的输入
 *内容.
 */ 

#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#define MYFIFO  "/data/data/com.termux/files/home/leon/linux-c/linux-c/9linux-C/fifo1"     /* 有名管道文件名*/ 
#define MAX_BUFFER_SIZE  PIPE_BUF /*定义在于 limits.h 中*/ 
int main(int argc, char * argv[]) /*参数为即将写入的字符串*/ 
{ 
 int fd; 
 char buff[MAX_BUFFER_SIZE]; 
 int nwrite; 
 
 if(argc <= 1){ 
   printf("Usage: ./fifo_write string\n"); 
   exit(1); 
 } 
 sscanf(argv[1], "%s", buff); 
 
 /* 以只写阻塞方式打开 FIFO 管道 */ 
 fd = open(MYFIFO, O_WRONLY); 
 if (fd == -1){ 
   printf("Open fifo file error\n"); 
   exit(1); 
 }

 /*向管道中写入字符串*/
 if ((nwrite = write(fd, buff, MAX_BUFFER_SIZE)) > 0){
   printf("Write '%s' to FIFO\n", buff);
 }
 close(fd);
 exit(0);
}
