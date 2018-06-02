/*名称：daemon_proc.c
 *作者：赵陈亮
 *时间：2018.02.26
 *功能：读者首先建立起一个守护进程，
 *然后在该守护进程中新建一个子进程，
 *该子进程暂停 10s，然后自动退出，
 *并由守护进程收集子进程退出的消息。
 *在这里， 子进程和守护进程的退出消
 *息都在系统日志文件（例如“/var/log/messages”，
 *日志文件的全路径名因版本的不同可能会 有所不同）
 *中输出。子进程退出后，守护进程循环暂停，其间隔时间为 10s。
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<syslog.h>

int main()
{
  pid_t child1,child2;
  int i;
  child1 = fork(); /* fork child proc*/
  if(child1 == -1){/* fork child proc fault. */
	perror("child1 fork fault.");
	exit(1);
  }
  else if(child1 > 0){ /* father proc */
	exit(0);
  }
  /* in child proc. 
   * and first open syslog 
   */
  openlog("daemon_proc_info",LOG_PID,LOG_DAEMON);

  /* creat daemon proc */
  setsid();
  chdir("/");
  umask(0);
  /* close all files which opened in father proc */
  for(i=0; i<getdtablesize; i++){
	close(i);
  }

  /* creat child2 proc */
  child2 = fork();
  if(child2 == -1){
	perror("child2 fork fault.");
	exit(1);
  }
  else if(child2 > 0){/* in child1(father proc) */
	waitpid(child2,NULL,0); /* to wait child2 proc exit */
	syslog(LOG_INFO,"child1 noticed that child2 has exited.");
	closelog();/* close syslog */

	while(1){
	  sleep(10);
	}
  }
  else{ /* in child2 */
	syslog(LOG_INFO,"child2 will sleep 10 sec.\n");
	sleep(10);
	syslog(LOG_INFO,"child2 is going to exit.\n");
	exit(0);
  }
}





