//     >>>1 配置终端设备<<<
int set_com_config(int fd,int baud_rate,\
int data_bits, char parity, int stop_bits)
{
struct termios new_cfg,old_cfg;
int speed;
/* 保存并测试现有串口参数设置，
 * 在这里如果串口号等出错，会有相关的出错信息 */
if (tcgetattr(fd, &old_cfg) != 0){
  perror("tcgetattr");
  return -1;
}
new_cfg = old_cfg;
cfmakeraw(&new_cfg); /* 配置为原始模式 */
/* 设置波特率 */
switch (baud_rate){
  case 2400:
	speed = B2400;
	break;
  case 4800:
	speed = B4800;
	break;
  case 9600:
	speed = B9600;
	break;
  case 19200:
	speed = B19200;
	break;
  case 38400:
	speed = B38400;
	break;
  default:
  case 115200:
	speed = B115200;
	break;
}
cfsetispeed(&new_cfg, speed);
cfsetospeed(&new_cfg, speed);

/* 设置数据位 */
new_cfg.c_cflag &= ~CSIZE;//先清零再赋值
switch (data_bits){ 
  case 7:
	new_cfg.c_cflag |= CS7;
	break;
  default:
  case 8:
	new_cfg.c_cflag |= CS8;
	break;
}

/* 设置奇偶校验位 */
switch (parity){
  //不校验
  default
  case 'n':
  case 'N':
	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_iflag &= ~INPCK;
	break;
  //奇校验
  case 'o':
  case 'O':
	new_cfg.c_cflag |= (PARODD | PARENB);
	new_cfg.c_iflag |= INPCK;
	break;
  //偶校验
  case 'e':
  case 'E':
	new_cfg.c_cflag |= PARENB;
	new_cfg.c_cflag &= ~PARODD;
	new_cfg.c_iflag |= INPCK;
	break;
 /* as no parity */
  case 's':
  case 'S':
	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB;
	break;
}

/* 设置停止位 */
switch (stop_bits){
  default:
  case 1:
	new_cfg.c_cflag &= ~CSTOPB;
	break;
  case 2:
	new_cfg.c_cflag |= CSTOPB;
}

/* 设置等待时间和最小接收字符 */
new_cfg.c_cc[VTIME] = 0;
new_cfg.c_cc[VMIN] = 1;

/* 处理未接收字符 */
tcflush(fd, TCIFLUSH);

/* 激活新配置 */
if ((tcsetattr(fd, TCSANOW, &new_cfg)) != 0){
  perror("tcsetattr");
  return -1;
}
return 0;
}

//>>>2 打开终端设备文件,对串口进行读和写操作<<<
/*O_NOCTTY 标志用于通知 Linux 系统，该参数不会使打开的文件成为这个进程的
  控制终端。如果没有指定这个标志，那么任何一个输入（如键盘中止信号等）都将
  会影响用户的进程。
   *O_NDELAY 标志用于设置非阻塞方式。通知 Linux 系统，这个程序不关心 DCD 信
  号线所处的状态（端口的另一端是否激活或者停止）。如果用户没有指定这个标志，
  则进程将会一直处在睡眠状态，直到 DCD 信号线被激活。
*/

/*打开串口函数*/
int open_port(int com_port)
{
  int fd;
#if (COM_TYPE == GNR_COM) /* 使用普通串口 */
  char *dev[] = {"/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2"};
#else /* 使用 USB 转串口 */
  char *dev[] = {"/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2"};
#endif

  if ((com_port < 0) || (com_port > MAX_COM_NUM)){
	return -1;
  }

  /* 打开串口 */
  fd = open(dev[com_port - 1], O_RDWR|O_NOCTTY|O_NDELAY);

  if (fd < 0){
	perror("open serial port");
	return(-1);
  }

  /* 恢复串口为阻塞状态 */
  if (fcntl(fd, F_SETFL, 0) < 0){
	perror("fcntl F_SETFL\n");
  }

  /* 测试打开的文件是否连接到终端设备 */
  if (isatty(fd) == 0){
  perror("This is not a terminal device");
  }
  return fd;
}

/*读写串口操作与读写普通文件一样，使用 read()和 write()函数即可*/
read(fd, buff, BUFFER_SIZE);
write(fd, buff, strlen(buff));


/************写串口的程序****************/
/* com_writer.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart_api.h"
int main(void)
{
  int fd;
  char buff[BUFFER_SIZE]; 
  /* 打开串口 */
  if((fd = open_port(HOST_COM_PORT)) < 0){
	perror("open_port");
	return 1;
  } 
  /* 配置串口 */
  if(set_com_config(fd, 115200, 8, 'N', 1) < 0){
	perror("set_com_config");
	return 1;
  }

  do{
	printf("Input some words(enter 'quit' to exit):");
	memset(buff, 0, BUFFER_SIZE);
	if (fgets(buff, BUFFER_SIZE, stdin) == NULL){
	  perror("fgets");
	  break;
	}
	write(fd, buff, strlen(buff));
  }while(strncmp(buff, "quit", 4));

  close(fd);
  return 0;
}



/************读串口的程序****************/
/* com_reader.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart_api.h"
int main(void)
{
  int fd;
  char buff[BUFFER_SIZE];
  /* 打开串口 */
  if((fd = open_port(TARGET_COM_PORT)) < 0){
	perror("open_port");
	return 1;
  }
  /* 配置串口 */
  if(set_com_config(fd, 115200, 8, 'N', 1) < 0){
	perror("set_com_config");
	return 1;
  }
  do{
	memset(buff, 0, BUFFER_SIZE);
	if (read(fd, buff, BUFFER_SIZE) > 0){
	  printf("The received words are : %s", buff);
	}
  }while(strncmp(buff, "quit", 4));

  close(fd);
  return 0;
}
