/* multiplex_poll.c 
 * 主要实现通过调用 poll()函数来监听三个终端的输入
 * （分别重定向到两个管道文件的虚拟终端及主程序所
 * 运行的虚拟终端）并分别进行相应的处理。在这里我们
 * 建立了一个 poll()函数监视的读文件描述符集，其中
 * 包含三个文件描述符，分别为标准输入文件描述符和两
 * 个管道文件描述符。通过监视主程序的虚拟终端标准输入
 * 来实现程序的控制（如程序结束）；以两个管道作为数据
 * 输入，主程序将从两个管道读取的输入字符串写入到标准
 * 输出文件（屏幕）。为了充分表现poll()函数的功能，在
 * 运行主程序时，需要打开3个虚拟终端：首先用mknod命令
 * 创建两个管道 in1 和 in2。接下来，在两个虚拟终端上
 * 分别运行 cat>in1 和 cat>in2。同时在第三个虚拟终端上
 * 运行主程序。在程序运行后，如果在两个管道终端上输入
 * 字符串，则可以观察到同样的内容将在主程序的虚拟终端
 * 上逐行显示。如果想结束主程序，只要在主程序的虚拟终
 * 端下输入以“q”或“Q”字符开头的字符串即可。如果三个文
 * 件一直在无输入状态中，则主程序一直处于阻塞状态。为
 * 了防止无限期的阻塞，在程序中设置超时值（本实例中设
 * 置为 60s），当无输入状态持续到超时值时，主程序主动
 * 结束运行并退出。
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <poll.h>
#define MAX_BUFFER_SIZE 1024 /* 缓冲区大小 */
#define IN_FILES 3 /* 多路复用输入文件数目 */
#define TIME_DELAY 60000 /* 超时时间秒数：6s */
#define MAX(a, b) ((a > b)?(a):(b))
int main(void)
{
  struct pollfd fds[IN_FILES];
  char buf[MAX_BUFFER_SIZE];
  int i, res, real_read, maxfd;
/* 首先按一定的权限打开两个源文件 */
  fds[0].fd = 0;
  if((fds[1].fd = open ("in1", O_RDONLY|O_NONBLOCK)) < 0){
	printf("Open in1 error\n");
	return 1;
  }
  if((fds[2].fd = open ("in2", O_RDONLY|O_NONBLOCK)) < 0){
	printf("Open in2 error\n");
	return 1;
  }
/* 取出两个文件描述符中的较大者 */
  for (i = 0; i < IN_FILES; i++){
	fds[i].events = POLLIN;
  }
/* 循环测试是否存在正在监听的文件描述符 */
  while(fds[0].events || fds[1].events || fds[2].events){
	if (!(poll(fds, IN_FILES, TIME_DELAY) > 0)){
	  printf("Poll error or Time out\n");
	  return 1;
	}
 /* 判断在哪个文件上发生了事件 */
	for (i = 0; i< IN_FILES; i++){
	  if (fds[i].revents){
		printf("in%d have putin.\n",i);
		getchar();
		memset(buf, 0, MAX_BUFFER_SIZE);
		real_read = read(fds[i].fd, buf, MAX_BUFFER_SIZE);
		if (real_read < 0){
		  if (errno != EAGAIN){
			return 1; /* 系统错误，结束运行 */
		  }
		}
		else if (!real_read){
		  close(fds[i].fd);
		  fds[i].events = 0; /* 取消对该文件的监听 */
		}
		else{
		  if (i == 0){/* 如果在标准输入上有数据输入时 */
			if ((buf[0] == 'q') || (buf[0] == 'Q')){
			  return 1; /* 输入“q”或“Q”则会退出 */
			}
		  }
		  else{ /* 将读取的数据先传送到终端上 */
			buf[real_read] = '\0';
			printf("%s", buf);
		  }
		} /* end of if real_read*/
	  } /* end of if revents */
	} /* end of for */
  } /*end of while */
exit(0);
}
