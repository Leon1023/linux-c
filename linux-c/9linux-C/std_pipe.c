/*名称：standard_pipe.c 
 *作者：赵陈亮
 *时间：2018.2.27
 *功能：标准流管道将一系列的创建过程合并到一个函数 popen()中完成。
 *它所完成的工作有以下几步:1.创建一个管道。2.fork()一个子进程。
 *3.在父子进程中关闭不需要的文件描述符。4.执行 exec函数族调用。
 *5.执行函数中所指定的命令。
 *这个函数的使用可以大大减少代码的编写量，但同时也有一些不利之处，
 *例如，它不如管道创建的函数那样灵活多样，并且用 popen()创建的管道
 *必须使用标准 I/O 函数进行操作，但不能使用read()、write()一类不带
 *缓冲的 I/O 函数。与之相对应，关闭用 popen()创建的流管道必须使用
 *函数 pclose()来关闭该管道流。该函数关闭标准 I/O 流，并等待命令执
 *行结束。在该实例中，使用 popen()来执行“ps -ef”命令。 
 */ 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#define BUFSIZE 1024 
int main() 
{ 
 FILE *fp; 
 char *cmd = "ps -ef"; 
 char buf[BUFSIZE]; 
 
 /*调用 popen()函数执行相应的命令*/ 
 if ((fp = popen("ps -ef", "r")) == NULL) 
 { 
 printf("Popen error\n"); 
 exit(1); 
 } 
 
 while ((fgets(buf, BUFSIZE, fp)) != NULL) 
 { 
 printf("%s",buf); 
 } 
 pclose(fp); 
 exit(0); 
} 
