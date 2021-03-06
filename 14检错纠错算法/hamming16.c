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
 *
 *===>Hamming16<===(Ham8编码长度一个字节，其中信息位仅占4位，传输效率50％。
 *在Ham16编码方案中，码长16位，其中信息位占11位，校验位占5位)when n=11，then m=4。
 *检验方程:C1=D1+D3+D5+D7+D9+D11+D13+D15;//D1~D16:16位汉明码，
 	C2=D2+D3+D6+D7+D10+D11+D14+D15;//C4C3C2C1组成4位二进制数，代表Dx出错,0000代表无差错
(=偶校验)C3=D4+D5+D6+D7+D12+D13+D14+D15; //传输前合理选择分配哪几位用来传输信息,哪几位是附加码
	C4=D8+D9+D10+D11+D12+D13+D4+D15;//通过观察我们选择第15~9,7~5,3共11位传信息，
					//1,2,4,8共4位作附加码.第16位作为对前述15位做偶校验。
 *即实际传输的数据格式为:(high)D15 D14 D13 D12 D11 D10 D9 D7 D6 D5 D3| D16 D8 D4 D2 D1(low)  
 *传输前合理选择D1D2D4D8的值，使校验方程的C1C2C3C4都为零。
 *D1取D3`D5`D7'D9'D11,D13'D15的偶校验值，使C1对D1`D3...D15取偶校验时为0.
 *D2取D3`D6`D7'D10'D11,D14'D15偶校验值，使C2对D2`D3...D15取偶校验时为0.
 *D4取D5`D6`D7'D12'D13,D14'D15的偶校验值，使C3对D5...D15取偶校验时为0.
 *D8取D9`D10`D11'D12'D13,D14'D15的偶校验值，使C4对D8...D15取偶校验时为0.
 *接收端取得数据后，先通过对相应位的4次偶校验，求得C4C3C2C1的值,确定出错位置
 *当C4C3C2C1取值应为0000时正确传送，若不为0，则它的取值指出了汉明码的哪一位出错
 *0001则D1出错，1111则D15出错。当然可事先编好汉明码，传输时通过查表求得
 *之前我们使用了D1-D15位，当我们把第16位D16利用起来，作为之前15位的偶校验位就是汉明16编码方法。
 *接收端先对接收来的16位数据做偶校验，结果记为C5.再依次求得C1-C4。
 *如果C5为0，说明传输无差错或有两个差错。此时若C4C3C2C1为零，则无差错，非零则无法断定出错位置。
 *如果C5非零，说明有1个差错。此时，若C4C3C2C1为零，则差错在D16,正常解码就好，若非零，则修正后解码。
 *编码:每次取11字节，转换生成8个16字节的Ham16码。11字节中的前8字节搁在8个汉明码的高字节，
 *后3个字节按位拆分分别装进后面3个汉明码的低字节的高三位,剩余的5位分别装D16,D8,D4,D2,D1
 *
 */

#include <stdio.h>
typedef unsigned char uchar;
typedef unsigned short ushort;
uchar trdata[11];	//待发送的11字节数据
uchar hamcode[16];	//存放8个16字节汉明码
uchar hamcode2[16];	//存放8个16字节汉明码
uchar hamcode3[16];	//存放8个16字节汉明码
uchar redata[11];	//接收的译码后的11字节数据
ushort errbit[16]={0x0,0x1,0x2,0x20,0x4,0x40,0x80,0x100,0x8,0x200,0x400,0x800,\
	0x1000,0x2000,0x4000,0x8000};//差错定位表

uchar Parity(ushort k)//偶校验函数,对16位数据k进行偶校验，并返回校验结果
{
	int i;
	uchar t=0;//初始化校验结果
	for(i=0;i<16;i++){
		if(k&0x1)t^=0x1;//若发现一个1，则添1取偶。再发现一个1，则取反为0.
		k>>=1;//校验下一位
	}
	return(t);
}

void Ham16(void)//16位汉明码编码函数
{
	uchar c0,c1,c2,c3,c4;//c0至c2分别存放11字节的后3个字节。c3c4组成16位汉明码
	int i,j=0;
	ushort m;//存放汉明16码
	c0=trdata[8];
	c1=trdata[9];
	c2=trdata[10];
	for(i=0;i<8;i++){
		c3=trdata[i];//取一个字节存入汉明码高字节
		c4=0;//初始化汉明码低字节
		if(c0&0x80) c4+=0x80;//分别取后3个字节的一位存入汉明码低字节高三位
		if(c1&0x80) c4+=0x40;
		if(c2&0x80) c4+=0x20;
		c0<<=1;c1<<=1;c2<<=1;//左移一位，为下次做准备
		m=c3*256+c4;//拼装出初始汉明码
		if(Parity(m&0xab61)) m+=0x1;//计算出D1
		if(Parity(m&0xcda2)) m+=0x2;//计算出D2
		if(Parity(m&0xf1c4)) m+=0x4;//计算出D4
		if(Parity(m&0xfe08)) m+=0x8;//计算出D8
		if(Parity(m&0xffff)) m+=0x10;//计算出D16
		hamcode[j++]=c3;hamcode[j++]=m%256;//将汉明码存入汉明码序列
	}
}


ushort UNHam16(void)//译码函数，对hamcode汉明码序列进行译码，结果存入接收数组redata
{
	int i,j,k;
	int ok=1;//初始化译码成功标志
	uchar p,q,r,c1,c2;//
	ushort m,n;
	p=q=r=0;//初始化最后3信息字节
	for(i=0,j=0;i<8;i++,j++){//分8组处理
		c1=hamcode3[2*i];
		c2=hamcode3[2*i+1];
		m=c1*256+c2;//拼装出16位汉明码
		n=0;//校验结果初始化
		if(Parity(m&0xab61)) n+=0x1;//计算校验结果D1
		if(Parity(m&0xcda2)) n+=0x2;//计算校验结果D2
		if(Parity(m&0xf1c4)) n+=0x4;//计算校验结果D4
		if(Parity(m&0xfe08)) n+=0x8;//计算校验结果D8
		k=Parity(m&0xffff);//计算校验结果D16
		if(!k&&n) ok=0;//两个差错，译码失败
		m^=errbit[n];//纠错处理
		redata[j]=m/256;//输出高字节八位信息
		p<<=1;q<<=1;r<<=1;//空出最低位
		if(m&0x80) p++;//存入位信息
		if(m&0x40) q++;
		if(m&0x20) r++;
	}
	redata[8]=p;
	redata[9]=q;
	redata[10]=r;
	return(ok);//返回函数执行情况
}


/*
 *无论是ham8或是ham16，只要传输中发生两个以上的错误，就无法纠正错误了。
 *为了提高编码的抗连续干扰，可以将编码好的16字节汉明码hamcode分成两个8字节长的数据
 *再分别从每组的这8个字节抽出一位凑成一个字节，依此共拼凑出新的8字节。另一组同样按此法操作。
 *这样生成新的16字节的hamcode2再通过Trans()函数发送出去,接收函数Receiv()通过转换之后恢复原来
 *的汉明16码存入hamcode3，再进过驿马程序得到原始数据。这样就算发生连续的多位错误，平摊到各个汉明 *码也只是1个，完全可以检错纠错，提高了抗连续干扰能力。
 */
void Trans(void)
{
	int i,j;
	uchar m;
	for(i=0;i<8;i++){
		m=hamcode[i];
		for(j=0;j<8;j++){
			hamcode2[j]<<=1;
			if(m&0x80) hamcode2[j]++;
			m<<=1;
		}
	}
	for(i=8;i<16;i++){
		m=hamcode[i];
		for(j=8;j<16;j++){
			hamcode2[j]<<=1;
			if(m&0x80) hamcode2[j]++;
			m<<=1;
		}
	}
}

void Receiv(void)
{
	int i,j;
	uchar m;
	for(i=0;i<8;i++){
		m=hamcode2[i];
		for(j=0;j<8;j++){
			hamcode3[j]<<=1;
			if(m&0x80) hamcode3[j]++;
			m<<=1;
		}
	}
	for(i=8;i<16;i++){
		m=hamcode2[i];
		for(j=8;j<16;j++){
			hamcode3[j]<<=1;
			if(m&0x80) hamcode3[j]++;
			m<<=1;
		}
	}
}


int main(void)
{
	int i;
	printf("\nint put your dates into trdata[]:");
	for(i=0;i<11;i++)
		trdata[i]=getchar();
	printf("starting to trans...\n");
	Ham16();
	printf("after hamming,putout hamed code:\n");
	for(i=0;i<16;i++)
		putchar(hamcode[i]);
	Trans();
	Receiv();
	putchar(10);
	UNHam16();
	printf("after hamming,putout reiceved data:\n");
	for(i=0;i<11;i++)
		putchar(redata[i]);
	putchar(10);
	return 0;
}
