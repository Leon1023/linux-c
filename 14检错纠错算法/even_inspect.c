/*
 *码重:二进制串中，1的个数;
 *码距:两个位数一致的二进制串中，从一个串变成另一个串需要改变的位数;
 *在进行数据传输时，一般只从所有代码中选择部分码作为有效码，且他们之
 *间的码距至少为2，此时若信道干扰致使某码某一位发生改变，从接受端接受
 *后，发现此码非有效码(因为有效码之间的码距至少为2，保证某一位改变不可能
 *使原来的码变成另外的某有效码，从而造成误接受)即可判定此码传输出错，
 *可要求重传或放弃此码。
 *在本例中，我们代码串选择8位，采取传ASCII码(占7位)的形式，并把最高位用来
 *做偶校验(通过选择此位为0或1，使此8位串中1的个数为偶数)检查位。
 *所以每次传4个比特，将它转变成ASCII码后，添加偶校验位后用来传输。
 *下面基于51单片机编写8位ASCII码偶校验发送和接受程序！
 */
#include <reg51.h>
#define 200 SIZE	//传输的字节数据个数
typedef unsigned char uchar;
uchar trdata[SIZE];	//存储发送数据
uchar redata[SIZE];	//存储接收数据
sbit ERR;		//错误标志

uchar HEX2ASCII(uchar ch)//十六进制数转换成ASCII码函数，0x5f==>'5''f'
{
	ch&=0x0f;	//取低4位，即两位16进制数的低位
	ch=ch<0xa?ch+0x30:ch+0x37;//如果是数字，直接加0x30即为ASCII码的数值。如果是字母(a~f),则加37h
	ACC=ch;//将ASCII码值放进CPU的累加器
	return(P==1?ch+0x80:ch);  //如果累加器里的二进制串码重是奇数，则P置1，反之清零。
	//若P为1则最高位置1，使ch码重为偶数，即完成了偶校验
}

void Trans(void)//发送函数
{
	int i;
	uchar ch;
	TMOD=0x20;//串口初始化，波特率9600
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;//选择方式1，允许发送和接受
	PCON=0x00;
	for(i=0;i<SIZE;i++){
		ch=trdata[i];//取一个字节的数据
		SBUF=HEX2ASCII(ch>>4);//先发送高四位
		while(TI==0) ;//等待发送结束
		TI=0;//发送完毕后，清除TI标志
		SBUF=HEX2ASCII(ch);//发送低四位
		while(TI==0) ;//等待发送完毕
		TI=0;
	}
}


uchar ASCII2HEX(uchar ch)//ASCII转成16进制数
{
	ACC=ch;//将接受的数放入累加器判断奇偶
	if(P==1) ERR=1;//如果码重为奇数，出错
	ch&=0x7f;//去掉奇偶校验位
	return(ch<0x40?ch-0x30:ch-0x37);//将ASCII码转换成十六进制数
}

void recev(void)//数据接受函数
{
	int i;
	uchar ch;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;
	PCON=0x00;
	ERR=0;//错误标志位清零
	for(i=0;i<SIZE;i++){
		while(RI==0) ;//等待接收完毕
		RI=0;
		ch=ASCII2HEX(SBUF);//将接收的高四位数据放入ch变量里
		while(RI==0) ;//等待接收低四位数据完毕
		RI=0;
		ACC=ASCII2HEX(SBUF);//将接受到的低四位数据放入累加器
		redata[i]=(ACC|(ch<<4));//同ch里的高四位数据合并后存入接收数组
	}
}


/*
 *将一个字节拆分成两个四位二进制数，再分别用ASCII码传输，
 *除了利于查看和显示外最大的缺点就是效率太低。在51系列
 *单片机中，串口的工作方式3在传送完一个字节数据后，会
 *额外自动再传送一位TB8，我们利用该位作为奇偶校验位，以此
 *达到偶校验。
 *
 */
#include <reg51.h>
#define 200 SIZE	//传输的字节数据个数
typedef unsigned char uchar;
uchar trdata[SIZE];	//存储发送数据
uchar redata[SIZE];	//存储接收数据

void Trans(void)//发送函数
{
	int i;
	uchar ch;
	TMOD=0x20;//串口初始化，波特率9600
	TH1=0xfd;
	TL1=0xfd;
	SCON=0xd0;//选择方式3，允许发送和接受
	PCON=0x00;
	for(i=0;i<SIZE;i++){
		ACC=trdata[i];//取一个字节的数据,放入累加器取得其码重
		TB8=P;//将数据的码重情况赋给将在字节传完后自动传送的TB8
		SBUF=ACC;//将数据交给缓存，开始传输
		while(TI==0);//等待传输完毕
		TI=0;
	}
}

void recev(void)//数据接受函数
{
	int i;
	uchar ch;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	SCON=0xd0;
	PCON=0x00;
	ERR=0;//错误标志位清零
	for(i=0;i<SIZE;i++){
		while(RI==0) ;//等待接收完毕
		RI=0;
		ACC=SBUF;//将接收的数据存入累加器判定码重情况
		if(P!=RB8) ERR=0;//如果接收字节的码重情况和发送字节不同，则判定出错
		redata[i]=ACC;
	}
}

