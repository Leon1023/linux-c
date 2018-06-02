/*
 *循环冗余校验(CRC校验)
 *基本原理:将所传数据看成是之后很长的二进制数，然后用一个特定的数
 *通常是0x11021去除它，将所得余数作为校验码附在最后传送。接受端做
 *相同处理，如果发现余数不同则判错！由于它强大的检错能力，被广泛
 *用在数据存储和通信中。
 *在8位或16位CPU的嵌入式系统中，常用CRC16校验算法。32位CPU则采用CRC32校验算法。
 *CRC16采用17位的二进制数0x11021作为除数,CRC32采用33位0x104c11db7作为除数
 *以CRC16为例说明:
 *待传数据块大小假定为128字节，即1024bit
 *校验位的长度2字节16位，其中除法的实现采用模2除法.
 *CRC校验码生成步骤:先在数据块后补2字节的清零空间以便存放16位的校验码。
 *                  然后从高位到低位进行模2除法,最后的余数就是校验码。
 *模2除法的操作过程:从高位至低位按二进制位扫描被除数，如果是0，则跳过。
 *如果是1，则将其后的16位数分别和除数的低16位即0x1021做异或操作。130个字节
 *的被除数要进行1024次处理，得到的1024位商被舍去，余下的16位就是所求CRC码。
 */

#include <reg51.h>
typedef unsigned char uchar;
typedef unsigned int uint;

uchar trdata[130];//待传的128字节数据及最后补零的2字节
uchar redata[130];//received data were stored here

uint CRC(void)//CRC校验码生成函数
{
	uint i,j,m,n,p,q,c=0x1021;
	m=trdata[0]<<8+trdata[1];//先取2字节
	for(i=1;i<64;i++){//剩余128字节分64组，每组2字节
		n=trdata[2*i]<<8+trdata[2*i+1];//取两字节数据,作为后补数据源
		for(j=0;j<16;j++){//对每组的16位进行处理
			p=m&0x8000;//取出被除数最高位
			q=n&0x8000;//取出后补源的最高位，以填入被除数最低位
			m<<=1;n<<=1;//m左移一位,开始处理第一位数据
			if(q) m++;//将后补数据补入被除数空出来的最低位
			if(p) m^=c;//如果正在处理的被除数位是1，则其后16数与c异或
		}
	}
	return(m);//返回CRC
}

void Trans(void)//function of send
{
	int i;
	uint c;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	PCON=0x00;
	SCON=0x50;
	trdata[128]=trdata[129]=0;
	c=CRC();
	trdata[128]=(uchar)c>>8;
	trdata[129]=(uchar)c&0x00ff;
	for(i=0;i<130;i++){
		SBUF=trdata[i];
		while(TI==0);
		TI=0;
	}	
}

//收方只要对含有CRC校验码的二进制串进行再次求CRC,
//如果传输无误，再次求得的CRC将为0。
//如果非零，则传输有误！

void Recev(void)//function of receive
{
	int i;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	PCON=0x00;
	SCON=0x50;
	ERR=0;
	for(i=0;i<130;i++){
		while(RI==0);
		RI=0;
		redata[i]=SBUF;
	}
	if(CRC()) ERR=1;
}

