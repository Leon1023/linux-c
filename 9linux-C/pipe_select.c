/* 函数名：pipe_select.c
*函数作用：
     建立两个有名管道in1和in2及标准输入
     这3个输入文件描述符集，通过select函数
     实现在一个进程中对多个IO设备文件的监视。
*验证流程：
  （1）在第1个虚拟终端上运行主程序：
       $ ./pipe_select （必须先运行主程序）
  （2）在第2个终端上运行 cat>in1后输入字符串，
       将在第一个终端上看到同步输入情况 $ cat > in1
  （3）在第3个终端上运行 cat>in2后输入字符串，
       将在第一个终端上看到同步输入情况 $ cat > in2
*特别注意：
   !!!需要注意的是这个实验在运行cat 命令时需要将目录
   cd 到当前程序目录，否则看不到实验结果。
 */ 
#include <fcntl.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <errno.h>
#define FIFO1 "in1" 
#define FIFO2 "in2"
#define MAX_BUFFER_SIZE 1024 /* 缓冲区大小*/
#define IN_FILES 3 /* 多路复用输入文件数目*/
#define TIME_DELAY 60 /* 超时值秒数 */
#define MAX(a, b) ((a > b)?(a):(b))

int main(void)
{
int fds[IN_FILES];
char buf[MAX_BUFFER_SIZE];
int i, res, real_read, maxfd;
struct timeval tv;
fd_set inset,tmp_inset;
fds[0] = 0;
/* 创建两个有名管道 */
if (access(FIFO1, F_OK) == -1){
  if ((mkfifo(FIFO1, 0666) < 0) && (errno != EEXIST)){
	printf("Cannot create fifo file\n");
	exit(1);
  }
}
if (access(FIFO2, F_OK) == -1){
  if ((mkfifo(FIFO2, 0666) < 0) && (errno != EEXIST)){
	printf("Cannot create fifo file\n");
	exit(1);
  }
}
/* 以只读非阻塞方式打开两个管道文件 */
if((fds[1] = open (FIFO1, O_RDONLY|O_NONBLOCK)) < 0){
  printf("Open in1 error\n");
  return 1;
}
if((fds[2] = open (FIFO2, O_RDONLY|O_NONBLOCK)) < 0){
  printf("Open in2 error\n");
  return 1;
}
/*取出两个文件描述符中的较大者*/
maxfd = MAX(MAX(fds[0], fds[1]), fds[2]);
/*初始化读集合inset ，并在读文件描述符集合中加入相应的描述集*/
FD_ZERO(&inset);
for (i = 0; i < IN_FILES; i++){
  FD_SET(fds[i], &inset);
}
FD_SET(0, &inset);
tv.tv_sec = TIME_DELAY;
tv.tv_usec = 0;
/*
 * 循环测试该文件描述符是否准备就绪，
 * 并调用select()函数对相关文件描述符做相应操作
*/
while(FD_ISSET(fds[0],&inset)\
	|| FD_ISSET(fds[1],&inset) || FD_ISSET(fds[2], &inset)){
/* 文件描述符集合的备份， 免得每次进行初始化 */
  tmp_inset = inset;
  res = select(maxfd + 1, &tmp_inset, NULL, NULL, &tv);
  switch(res){
	case -1:
	  printf("Select error\n");
	  return 1;
	  break;
	case 0: /* Timeout */
	  printf("Time out\n");
	  return 1;
	  break;
	default:
	  for (i = 0; i < IN_FILES; i++){
		if (FD_ISSET(fds[i], &tmp_inset)){
		  memset(buf, 0, MAX_BUFFER_SIZE);
		  real_read = read(fds[i], buf, MAX_BUFFER_SIZE);
		  if (real_read < 0){
			if (errno != EAGAIN)
			  return 1;
		  }
		  else if (!real_read){
			close(fds[i]);
			FD_CLR(fds[i], &inset);
		  }
		  else{
			if (i == 0){/* 主程序终端控制 */
			  if ((buf[0] == 'q') || (buf[0] == 'Q'))
				return 1;
			}
			else{/* 显示管道输入字符串 */
			  buf[real_read] = '\0';
			  printf("%s", buf);
			}
		  }
		} /* end of if */
	  } /* end of for */
	break;
  } /* end of switch */
} /*end of while */
return 0;
}
