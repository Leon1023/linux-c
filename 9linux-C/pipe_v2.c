/*名称： pipe.c
 *作者：赵陈亮
 *日期：2018.2.27
 *功能：无名管道主要用于有亲缘关系（父子、兄弟）
 *的进程间进行通信。首先创建管道，之后父进程使用 
 *fork()函数创建子进程，之后通过关闭父进程的读描
 述符和子进程的写描述符，建立起它们之间的管道通信。
 */ 

#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define MAX_DATA_REC 16 
#define MAX_DATA_SEND 256 
#define DELAY_TIME 1 

int main() 
{ 
 pid_t pid; 
 int pipe_fd[2]; 
 char buf[MAX_DATA_REC]; 
 char quit[] = "quit" ; 
 char data[MAX_DATA_SEND]; 
 int real_read, real_write; 
 memset((void*)buf, 0, sizeof(buf)); 
 memset((void*)data, 0, sizeof(data)); 

 /* 创建管道 */ 
 if (pipe(pipe_fd) < 0){
   printf("pipe create error\n"); 
   exit(1); 
 } 
 
 /* 创建一子进程, 子进程关闭写描述符，
  * 并通过使子进程暂停3s等待父进程已关闭相应的读描述符
  */
 if ((pid = fork()) == 0){
   close(pipe_fd[1]);
   sleep(DELAY_TIME * 3);

 /* 子进程读取管道内容 */
   while ((real_read = read(pipe_fd[0], buf, MAX_DATA_REC)) > 0){
	 printf("read from father proc(%d):%s\n",getppid(), buf);
	 memset((void*)buf, 0, sizeof(buf)); 
   }

 /* 关闭子进程读描述符 */
   close(pipe_fd[0]);
   exit(0);
 }
 else if (pid > 0){
 /* 父进程关闭读描述符，并通过使父进程暂停 1s 等待子进程已关闭相应的写描述符 */
   close(pipe_fd[0]);
   sleep(DELAY_TIME);
   while(read(1,data,MAX_DATA_SEND)){
	 if(data[0]=='q'||data[0]=='Q') return 0;
	 if(data[0]!='\n'&&(real_write = write(pipe_fd[1], data, strlen(data))) != -1){
	   printf("Parent wrote %d bytes :%s\n", real_write, data);
	 }
	 memset((void*)data, 0, sizeof(data)); 
   }
   //可添加'quit'或QUIT等退出条件的检测
   close(pipe_fd[1]);/*关闭父进程写描述符*/
   waitpid(pid, NULL, 0); /*收集子进程退出信息*/
   exit(0);
 }
}

