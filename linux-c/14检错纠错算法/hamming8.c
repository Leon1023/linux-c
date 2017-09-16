/*
 *汉明检错纠错码。令待传数据位是n位，附加校验位是m位。他们需满足2^m>=(m+n+1).
 *意思就是添加的m位组成二进制数时要能指明汉明码所有(m+n)位哪一位有传错，另加
 *无传错的一种状态，共计m+n+1位的状态。当上式取等号时就是效率最好的汉明码。
 *
 *===>Hamming7<===
 *when n=4，then m=3。我们以此"Hamming7"为例编程说明汉明码的编码及验码原理。
 *检验方程:  C1=D1+D3+D5+D7;//D1~D7:7位汉明码，C3C2C1组成3位二进制数，代表Dx出错
(=代表偶校验)C2=D2+D3+D6+D7;//000代表无差错。传输前合理选择分配哪几位用来传输信息
	     C3=D4+D5+D6+D7;哪几位是附加码。通过观察我们选择3567位传信息，124位作附加码
 *即实际传输的数据格式为:0 D1 D2 D4; D3 D5 D6 D7
 *传输前合理选择D1D2D4的值，使校验方程的C1C2C3都为零。
 *D1取D3`D5`D7的偶校验值，使C1对D1`D3`D5`D7取偶校验时为0.
 *D2取D3`D6`D7的偶校验值，使C2对D2`D3`D6`D7取偶校验时为0.
 *D4取D5`D6`D7的偶校验值，使C3对D4`D5`D6`D7取偶校验时为0.
 *接收端取得数据后，先通过对相应位的3次偶校验，求得C3C2C1的值
 *当C3C2C1取值应为000时正确传送，若不为000，则它的取值指出了汉明码的哪一位出错
 *001则D1出错，111则D7出错，000则无出错。当然可事先编好汉明码，传输时通过查表求得
 *
 *===>Hamming8<===
 *汉明7中共使用了D1-D7位，当我们把第八位D8利用起来，作为之前7位的偶校验位。就是汉明8编码方法。
 *接收端先对接收来的8位数据做偶校验，结果记为C4.再依次求得C1-C3。
 *如果C4为0，说明传输无差错或有两个差错。此时若C3C2C1为零，则无差错，非零则无法断定出错位置。
 *如果C4非零，说明有1个差错。此时，若C3C2C1为零，则差错在D8,正常解码就好，若非零，则修正后解码。
 */

#include <stdio.h>
#include <reg51.h>
#define SIZE 200
typedef unsigned char uchar;
uchar trdata[SIZE];	//待发送数组
uchar redata[SIZE];	//接收数组


uchar ham8;//存储汉明码
sbit D1=ham7^6;
sbit D2=ham7^5;
sbit D4=ham7^4;
sbit D3=ham7^3;
sbit D5=ham7^2;
sbit D6=ham7^1;
sbit D7=ham7^0;
sbit D8=ham7^7;

void CreatHam8(uchar ch)//汉明码生成函数，ch为待传输原始字节数据
{
	ch&=0x0f;
	ham8=ch;//汉明码低四位存储原始信息
	ACC=ch;
	ACC^=0x0d;//对D357进行偶校验
	D1=P;
	ACC=ch;
	ACC^=0x0b;//对D367进行偶校验
	D2=P;
	ACC=ch;
	ACC^=0x07;//对D567进行偶校验
	D4=P;
	ACC=ch;
	D8=P;
	SBUF=ham8;//将生成的汉明码存到发送缓存待传送
	while(TI==0);
	TI=0;
}


//查表法求汉明码并发送，省去每次调用函数生成汉明码，以节省时间。
uchar ham8[16]={0x00,0x71,0xb2,0xc3,0xd4,0xa5,0x66,0x17,0xe8,0x99,0x5a,\
	0x2b,0x3c,0x4d,0x8e,0xff};//对传送的四位数据分别按组合求得汉明码序列

void Ham8(uchar ch)//查表求得数据对应汉明码并进行传送
{
	ch&=0x0f;
	ACC=Ham8[ch];
	SBUF=ACC;
	while(TI==0);
	TI=0;
}




void Trans(void)//发送函数
{
	int i;
	uchar ch;
	TMOD=0x20;//串口初始化，波特率9600
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;//工作方式1，允许发送接收
	PCON=0x00;
	for(i=0;i<SIZE;i++){
		ch=trdata[i];
		Ham8(ch>>4);
		Ham8(ch);
	}
}


uchar Errbit[8]={0x00,0x40,0x20,0x08,0x10,0x04,0x02,0x01};//差错定位表
uchar check;//可位操作的临时字节变量
uchar state;//可位操作的临时字节变量 
sbit C1=check^0;
sbit C2=check^1;
sbit C3=check^2;
sbit C4=state^1;
sbit ERR=state^0;

uchar UNHam8(uchar ch)
{
	check=0;
	ACC=ch;//将接收到的汉明码存入累加器中
	C4=P
	ACC&=0x4d;//对D1357进行偶校验
	C1=P;
	ACC=ch;
	ACC&=0x2b;//对D2367进行偶校验
	C2=P;
	ACC=ch;
	ACC&=0x17;//对D4567进行偶校验
	C3=P;
	if(check){
		if(C4==0)ERR=1;
		ch^=Errbit[check];
	}
	return(ch&=0x0f);//返回低四位有效二进制数
}

//如果程序空间充裕，可以将所有接收到的编码事先进行译码。
//对于没有差错，或只有一个差错的8位汉明码，直接查表取得译码;
//对于发生两个差错(D8!=0，C3C2C1!=0),给出0xff的结果，进行判错
//

uchar code[256]={0x00,0x00,0x00,0xff,0x00,0xff,0xff,0x07...};
uchar UNHam8(uchar ch)
{
	ACC=code[ch];
	if(ACC==0xff){
		ERR=1;
		ACC^=0x0f;
	}
	return ACC;
}


void Receive(void)
{
	int i;
	uchar ch;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	SCON=0x50;
	PCON=0x00;
	for(i=0;i<SIZE;i++){
		while(RI==0);
		RI=0;
		ch=UNHam8(SBUF);
		while(RI==0);
		RI=0;
		ACC=UNHam8(SBUF);
		ACC|=ch<<4;
		redata[i]=ACC;
	}
}


