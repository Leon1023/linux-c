/*名称：kill_raised.c
 *功能：首先使用 fork()创建了一个子进程，接着为了保证子进程不在父进程调用 kill()
        之前退出，在子进程中使用 raise()函数向自身发送 SIGSTOP 信号，使子进程暂停
		接下来再在父进程中调用 kill()向子进程发送信号，在此处使用的是SIGKILL。
 *作者：赵陈亮
 *日期：2018.3.1
 *版本：v1.0
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h>/*fork()*/ 
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> 

int main() 
{ 
 pid_t pid; 
 int ret; 

 /* 创建一子进程 */ 
 if ((pid = fork()) < 0) { 
   printf("Fork error\n"); 
   exit(1); 
 }  
 else if (pid == 0) { 
   /* 在子进程中使用 raise()函数发出 SIGSTOP 信号,使子进程暂停 */ 
   printf("Child(pid : %d) is waiting for any signal\n", getpid()); 
   raise(SIGSTOP); 
   exit(0); 
 } 
 else { 
   /* 在父进程中收集子进程发出的信号，并调用 kill()函数进行相应的操作 */ 
   sleep(1);/*等待子进程执行*/
   if ((waitpid(pid, NULL, WNOHANG)) == 0){
	 if ((ret = kill(pid, SIGKILL)) == 0){
	   printf("Parent(pid=%d) kill child proc(%d)\n",getpid(),pid);
	 }
   }
   waitpid(pid, NULL, 0);
   exit(0);
 }
}
