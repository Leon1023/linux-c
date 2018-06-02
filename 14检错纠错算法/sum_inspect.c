/*
 *和校验是指，连续传送n个字节的数据，并在传送完之后
 *将这个n个字节的和sum("算术和"或"逻辑和<异或和>")也传
 *送过去，作为和校验数据。该方法常用于传送HEX格式数据
 */

#include <reg51.h>
#define 200 SIZE	//传输的字节数据个数
typedef unsigned char uchar;
uchar trdata[SIZE];	//存储发送数据
uchar redata[SIZE];	//存储接收数据
sbit ERR;		//错误标志

void Trans(void)//发送函数
{
	int i;
	uchar sum=0;
	TMOD=0x20;//串口初始化，波特率9600
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;//选择方式1，允许发送和接受
	PCON=0x00;
	for(i=0;i<SIZE;i++){
		ACC=trdata[i];//取一个字节的数据
		SBUF=ACC;//send
		while(TI==0) ;//等待发送结束
		TI=0;//发送完毕后，清除TI标志
		sum+=ACC;//summary of dates
	}
	BUF=sum;//send sum
	while(TI==0) ;//等待发送结束
	TI=0;//发送完毕后，清除TI标志
}

void recev(void)//数据接受函数
{
	int i;
	uchar sum=0;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;
	PCON=0x00;
	ERR=0;//错误标志位清零
	for(i=0;i<SIZE;i++){
		while(RI==0) ;//等待接收完毕
		RI=0;
		ACC=SBUF;
		redata[i]=ACC;//将接收的数据放入redata[]里
		sum+=ACC;//
	}
	while(RI==0) ;//等待接收完毕
	RI=0;
	ACC=SBUF;
	if(sum!=ACC) ERR=1;
	
}
