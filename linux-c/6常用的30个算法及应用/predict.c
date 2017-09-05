/****************************************
技巧22：SHA加密
安全哈希算法（secure hash algorithm）主要适用数字签名标准里面
定义的数字签名算法。
****************************************/

/****************************************
技巧23：MD5加密
MD5是一种被广泛使用的“消息-摘要算法”，实际上即使一个单项散列函数。
****************************************/

/****************************************
技巧24：RSA加密
RSA算法是非对称加密的代表。RSA算法是第一个同时用于加密和数字签名
的算法。
****************************************/

/****************************************
技巧25：DES加密
美国数据加密标准DES是一种对称加密算法。对称是指采用保密密玥既可
用于加密也可用于解密。
****************************************/

/****************************************
技巧26：RC4加密
RC4是可变的流加密算法簇。RC4算法包括初始化算法（KSA）和伪随即
子密码生成算法（PRGA）两大部分。
****************************************/

/****************************************
技巧29：迪杰斯特拉算法
其思想是：设置并逐步扩充一个集合S，存放已求出其最短路径的顶点，则
尚未确定路径的顶点集合是V-S，其中V为网中所有顶点集合。按最短路径
长度递增的顺序逐个将V-S中的顶点加到S中，直到S中包含全部顶点，而
V-S为空。
****************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 30
#define MAXCOST 1000
int dist[MAXCOST],cost[MAXNODE][MAXNODE],n=5;
void dijkstra(int v0)  //自定义函数，用来求最小生成树
{
  int s[MAXNODE];             //定义一个集合s，其可扩充
  int mindis,dis,i,j,u;
  for (i=1; i<=n; i++)
    {
      dist[i]=cost[v0][i];
      s[i]=0;
    }
  s[v0]=1;
  for (i=1; i<=n; i++)
    {
      mindis=MAXCOST;
      for(j=1;j<=n;j++)
	if (s[j]==0&&dist[j]<mindis)
	  {
	    u=j;
	    mindis=dist[j];
	  }
      s[u]=1;
      for(j=1;j<=n;j++)
	if (s[j]==0)
	  {
	    dis=dist[u]+cost[u][j];
	    dist[j]=((dist[j]<dis)?dist[j]:dis);
	  }
    }
}
void display_path(int v0)     //自定义函数，用来输出到个顶点的最短路径
{
  int i;
  printf ("顶点%d到各个顶点的最短路径长度如下：\n",v0);
  for (i=1; i<=n; i++)
    {
      printf ("(v%d->v%d):",v0,i);
      if(dist[i]==MAXCOST)
	printf ("wu lu jing\n");
      else
	printf ("%d\n",dist[i]);
    }
}
main()
{
  int i,j,v0=1;
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      cost[i][j]=MAXCOST;
  for(i=1;i<=n;i++)
    cost[i][i]=0;
  cost[1][2]=10;
  cost[1][5]=100;
  cost[1][4]=30;
  cost[2][3]=50;
  cost[4][3]=20;
  cost[3][5]=10;
  cost[4][5]=60;
  dijkstra(v0);
  display_path(v0);
  return 0;
}
*/

/**********************************************
 *30.无回代过程主元消去法求解多元一次线性方程组
 *...有回代过程主元消去法求解多元一次线性方程组
 *...行列式法法求解多元一次线性方程组
**********************************************/
/*
#include<stdio.h>
#include<math.h>	 //需要使用其中的绝对值函数fabs()
#define N 3		 //线性方程组的阶数
float A[N][N+1];	//线性方程组的增广系数矩阵(将常数项B移到系数矩阵内,作为最后一列)
float B[N];
float X[N];		 //线性方程组的解

void findmain(int i) 	//寻找第i列的主元,并将其所在行交换到当前处理行位置上
{
	int j,k;
	float c;
	c = fabs(A[i][i]);
	k = i; 			//初始化主元在第i行
	for(j=i+1;j<N;j++)	//寻找主元(绝对值最大)所在行
		if(fabs(A[j][i])>c){
			c=fabs(A[j][i]);
			k=j;
		}
	if(k!=i)
		for(j=0;j<=N;j++){ //将主元所在行交换到当前处理行位置上
			c = A[k][j];
			A[k][j]=A[i][j];
			A[i][j]=c;
		}
}

void divmain(int i)		 //将主元所在行的各个系数除以主元,使主元为1
{
	int j;
	float c;
	c = A[i][i];		 //取出主元的原数值
	A[i][i] = 1.0;			//使主元为1
	for(j=i+1;j<=N;j++)
		A[i][j]/=c;	 //将主元所在行的各个系数除以主元的原数值
}

void del_nobackin(int i) 		//进行第i列的消元处理
{
	int j,k;
	float c;
	for(j=0;j<N;j++)
		if(j!=i&&A[j][i]){	//只处理除i行之外且i列系数非零的行(行下标为j)
			c=A[j][i];
			A[j][i]=0;	 //记录被消系数的原数值,然后将其消零
			for(k=i+1;k<=N;k++)
				A[j][k] -= c*A[i][k]; //调整同行的其他系数
		}
}

void del_backin(int i) 			//进行第i列的消元处理
{
	int j,k;
	float c;
	for(j=i+1;j<N;j++)
		if(A[j][i]){		//只处理i行以下的且i列系数非零的行(行下标为j)
			c=A[j][i];
			A[j][i]=0;	 //记录被消系数的原数值,然后将其消零
			for(k=i+1;k<=N;k++)
				A[j][k] -= c*A[i][k]; //调整同行的其他系数
		}
}

float DETA(void)	 //行列式计算
{
return(A[0][0]*A[1][1]*A[2][2]+A[1][0]*A[2][1]*A[0][2]+A[2][0]*A[0][1]*A[1][2]-A[2][0]*A[1][1]*A[0][2]-A[0][0]*A[2][1]*A[1][2]-A[1][0]*A[0][1]*A[2][2]);
}

void swap(int k) 	//常数项与k列系数交换
{
int i;
float t;
for(i=0;i<3;i++){
	t=B[i];
	B[i]=A[i][k];
	A[i][k]=t;
}
}

void XYZ(void) 		//求解三元一次方程组
{
float d;
d=DETA();		 //求系数行列式的值
swap(0);		 //将 X 的系数与常数项交换
X[0]=DETA()/d;		 //解出 X
swap(0);		 //恢复原来的系数与常数项
swap(1); 		//将Y 的系数与常数项交换
X[1]=DETA()/d; 		//解出Y
swap(1); 		//恢复原来的系数与常数项
swap(2); 		//将Z 的系数与常数项交换
X[2]=DETA()/d; 		//解出Z
swap(2); 		//恢复原来的系数与常数项
}


int main(void)
{
	int i,j;
	char ch;
	printf("\n请输入线性方程组的增广系数矩阵:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("A%d%d=",i+1,j+1);
			scanf("%f",&A[i][j]);
		}
		printf("B%d=",i+1);
		scanf("%f",&A[i][N]);
	}
	for(i=0;i<N;i++)
		B[i]=A[i][N];
	scanf("%*[^\n]%*c");//在输入选择字符前，必须清除标准输入缓存！！！
	setbuf(stdin,NULL);
	printf("\n请选择求解线性方程组的方法:\n\t(a):无回代过程主元消去法\n\t(b):有回代过程主元消去法");
	printf("\n\t(c):行列式法\n\t你的选择:");
	ch = getchar();
	switch(ch){
		case 'a':
			for(i=0;i<N;i++){	 	//按行处理
				if(i<N-1) findmain(i);	 //寻找主元,并将其交换到当前处理行位置上
				divmain(i); 		//将当前处理行的各个系数除以主元,使主元为1
				del_nobackin(i);	 //进行消元处理
			}
			for(i=0;i<N;i++) X[i]=A[i][N]; 		//保存n阶线性方程组的解
			break;
		case 'b':
			for(i=0;i<N;i++){	 	//按行处理
				if(i<N-1) findmain(i);	 //寻找主元,并将其交换到当前处理行位置上
				divmain(i); 		//将当前处理行的各个系数除以主元,使主元为1
				if(i<N-1) del_backin(i);
			}
			for(i=N-2;i>=0;i--) //回代过程
				for(j=N-1;j>i;j--) A[i][N]-= A[i][j]*A[j][N];
			for(i=0;i<N;i++) X[i]=A[i][N]; 		//保存n阶线性方程组的解
			break;
		case 'c':
			XYZ();
			break;
		default:
			printf("wrong select!\n");
			return -1;
	}
	printf("\n线性方程组的解:\n");
	for(i=0;i<N;i++)
		printf("X%d=%f ",i+1,X[i]);
	scanf("%*[^\n]%*c");
	setbuf(stdin,NULL);
	getchar();
	return 0;
}
*/
/****************************************
 *31.折线插值算法及抛物线插值算法(数字温度计)
****************************************/
/*
#include<stdio.h>
#define N 10 		//折线由10段线段组成(即有11个插值节点)

float w=10.0; 		//插值节点间隔为10.0℃(即 w=y1-y0=10.0)
float w0=0.0; 		//起点温度为0.0℃
float wn=100.0; 	//终点温度为100.0℃
int adc[N+1]={86,376,687,1021,1379,1760,2164,2592,3043,3515,4008};  //记录11个标定节点的A/D转换结果
float x0,x1,y0,y1,L01,L02,L012;//用于计算线性插值法的两个点0和1，及用于计算抛物线插值法的三个中间变量

float line(int x)	 //折线插值算法,x为A/D转换结果,返回对应温度值
{
	int i;
	if(x<adc[0]) return(w0); 	//A/D转换结果过低,返回起点温度
	if(x>=adc[N]) return(wn);		 //A/D转换结果过高,返回终点温度
	for(i=0;i<N;i++) 
		if(x<adc[i+1]) break; 		//判断x所在区间
	return(w*i+w*(x-adc[i])/(adc[i+1]-adc[i]));	//用点斜式线性插值算法计算温度值
}

float line2(float x)
{
	return(y0+(x-x0)*(y1-y0)/(x1-x0));
}

float qins(float x)
{
	int i;
	if(x<adc[0]) return(w0); 	//A/D转换结果过低,返回起点温度
	if(x>=adc[N]) return(wn);	//A/D转换结果过高,返回终点温度
	for(i=1;i<N;i++) 
		if(x<adc[i+1]) break; 		//判断x所在区间
	x0=adc[i-1];y0=w*(i-1);
	x1=adc[i];y1=w*i;
	L01=line2(x);
	x1=adc[i+1];y1=w*(i+1);
	L02=line2(x);
	x0=adc[i];y0=L01;
	x1=adc[i+1];y1=L02;
	L012=line2(x);
	return(L012);
}
	
int main(void) 		//折线插值算法验证程序
{
	int x;
	float y;
	char ch;
	while(1){
		printf("\n\t输入需D/A转换的值:");
		scanf("%d",&x);
		if(x==0) break; 		//输入0时结束验证
		printf("\n\t请选择方法:\n\t(a)线性插值算法\n\t(b)抛物线插值算法\n\t(c)退出\n\n\t你的选择是:");
		setbuf(stdin,NULL);
		ch=getchar();
		switch(ch){
			case'a':
				y=line(x);	//执行折线插值算法
				break;
			case'b':
				y=qins(x);
				break;
			case'c':
				return 0;
			default:
				printf("\n\t您的输入有误！请输入'a'或'b'!\n");
				return(-1);
		}
		printf("\n对应温度为 :%2.2f℃\n",y); 	//显示对应温度(显示两位小数)
	}
return 0;
}

*/



/****************************************
 *32.曲线拟合算法(数字温度计)
****************************************/
/*
#include <stdio.h>
#define MAX 20

int n;			//实际用于拟合的曲线标定节点个数
float X[MAX],Y[MAX];	//用于存储标定节点，最多存MAX个
float A[3]={0,0,0},B[3]={0,0,0};	//用于存拟合函数的系数，系数矩阵的常数项列
float S[3][3]={{0,0},{0,0},{0,0}};	//系数矩阵

void lsline1(void)	//行列式法求解最小二乘法的拟合一元1次方程系数
{
	float sx=0,sy=0,sxx=0,sxy=0,dt=0;
	for(int i=0;i<n;i++){
		sx += X[i];	//	| n  sx | | a0 | | sy  |
				//	|	| |    |=|     |
		sy += Y[i];	//	| sx sxx| | a1 | | sxy |
		sxx += X[i]*X[i];
		sxy += X[i]*Y[i];
	}
	dt = n*sxx-sx*sx;
	A[0] = (sy*sxx-sx*sxy)/dt;	//a0
	A[1] = (n*sxy-sy*sx)/dt;	//a1
}


void lsline2(void)	//均方差法求解线性拟合方程
{
	float ave_x=0,ave_y=0,sum_xx=0,sum_xy=0;
	for(int i=0;i<n;i++){
		ave_x += X[i];
		ave_y += Y[i];
	}
	ave_x /= n;
	ave_y /= n;
	for(int i=0;i<n;i++){
		sum_xx += (X[i]-ave_x)*(X[i]-ave_x); 
		sum_xy += (X[i]-ave_x)*(Y[i]-ave_y);
	}
	A[1]=sum_xy/sum_xx;
	A[0]=ave_y-A[1]*ave_x;
}


float deta(void)
{
	return(S[0][0]*S[1][1]*S[2][2]+S[1][0]*S[2][1]*S[0][2]+S[0][1]*S[1][2]*S[2][0]-S[0][2]*S[1][1]*S[2][0]-S[0][1]*S[1][0]*S[2][2]-S[1][2]*S[2][1]*S[0][0]);
}

void swap(int k)
{
	float t;
	for(int i=0;i<3;i++){
		t = S[i][k];
		S[i][k] = B[i];
		B[i] = t;
	}
}


void lsline3(void)	//行列式法求解最小二乘法的拟合一元二次方程系数
{
	float t,dt;
	for(int i=0;i<n;i++){
			//	| n   sx   sxx  | | a0 | | sy  |
		      //	| sx  sxx  sxxx	| | a1 |=| sxy |
			//	| sxx sxxx sxxxx| | a2 | | sxxy|
		t = X[i];
		S[1][0] += t;
		t *= X[i];
		S[2][0] += t;
		t *= X[i];
		S[2][1] += t;
		t *= X[i];
		S[2][2] += t;
		t = Y[i];
		B[0] += t;
		t *= X[i];
		B[1] += t;
		t *= X[i];
		B[2] += t;
	}
	S[0][0] = n;
	S[0][1] = S[1][0];
	S[1][1] = S[0][2] = S[2][0];
	S[1][2] = S[2][1];
	dt = deta();
	swap(0);
	A[0]=deta()/dt;
	swap(0);
	swap(1);
	A[1]=deta()/dt;
	swap(1);
	swap(2);
	A[2]=deta()/dt;
	//swap(2);
}


int main(void)
{
	int i=0;
	char ch;
	printf("\n\t请输入标定节点的个数(<=%d):",MAX);
	scanf("%d",&n);
	setbuf(stdin,NULL);
	for(i=0;i<n;i++){
		printf("\n\t请输入第%d个标定节点A/D转换的数字值: ",i+1);
		scanf("%f",&X[i]);
		printf("\n\t请输入第%d个标定节点的温度值: ",i+1);
		scanf("%f",&Y[i]);
	}
	while(1){
		printf("\n\t请选择方法:\n\t(a)最小二乘法法\n\t(b)均方差法\n\t(c)抛物线拟合\n\t(d)退出\n\n\t你的选择是:");
		scanf("%*[^\n]%*c");
		setbuf(stdin,NULL);
		ch=getchar();
		switch(ch){
			case'a':
				lsline1();
				break;
			case'b':
				lsline2();
				break;
			case'c':
				lsline3();
				break;
			case'd':
				return 0;
			default:
				printf("\n\t您的输入有误！请输入'a','b'或'c'!\n");
				return(-1);
		}
		if(ch=='a'||ch=='b')
			printf("\n\t所求一元1次拟合函数为:y=%3.5fx%+3.5f",A[1],A[0]);
		else if(ch=='c')
			printf("\n\t所求一元2次拟合函数为:y=%3.5fx²%+3.5fx%+3.5f",A[2],A[1],A[0]);
		else
			printf("\n\t请重新输入!");
	}
	return 0;
}
*/


/****************************************
 *33.平滑算法
****************************************/
/*
#include <stdio.h>
#define CH 1024
float cps[CH],temp[CH];

void petrum_smooth(int W)
{
	for(int i=0;i<CH;i++) 
		temp[i] = cps[i];
	switch(W){
		case'5':
			for(int i=2;i<(CH-2);i++)
				cps[i]=(-3*(temp[i-2]+temp[i+2])+12*(temp[i-1]+temp[i+1])+17*temp[i])/35;
			break;
		case'7':
			for(int i=3;i<(CH-3);i++)
				cps[i]=(-2*(temp[i-3]+temp[i+3])+3*(temp[i-2]+temp[i+2])+6*(temp[i-1]+temp[i+1])+7*temp[i])/21;
			break;
		case'9':
			for(int i=4;i<(CH-4);i++)
				cps[i]=(-21*(temp[i-4]+temp[i+4])+14*(temp[i-3]+temp[i+3])+39*(temp[i-2]+temp[i+2])+54*(temp[i-1]+temp[i+1])+59*temp[i])/231;
			break;
		case'11':
			for(int i=5;i<(CH-5);i++)
				cps[i]=(-36*(temp[i-5]+temp[i+5])+9*(temp[i-4]+temp[i+4])+44*(temp[i-3]+temp[i+3])+69*(temp[i-2]+temp[i+2])+84*(temp[i-1]+temp[i+1])+89*temp[i])/429;
			break;
		default:
			break;
	}
}

*/


/****************************************
 *34.自动寻峰算法(能谱曲线)
 共有:简单比较法，导数法，对称零面积卷积法，协方差算法。
 简单比较法:找出比周围道的计数大的多的峰位。以5道极值法说明，
 如果i道的计数ni满足n(i-2)<ni-k*sqrt(ni)>n(i+2),
 则在ni,n(i-1),n(i+1)中选择计数最大的道，此道就为峰值所在道，
 其中k为找峰阈值，一般取1--1.5
****************************************/
/*
#include <stdio.h>
#include <math.h>
#define CH 1024			//最大的能谱数据道数
#define MAX 24			//最大峰值数

float cps[CH];			//能谱数据的存储数组
float peak[MAX];		//峰值对应的道数

int lookfor_peak(int k)
{
	int j=0;
	float t=0;
	for(int i=2;i<CH-2;i++){			//5道极值法
		t=cps[i]-k*sqrt(cps[i]);
		if(cps[i-2]<t&&cps[i+2]<t){
			peak[j]=i-1;			//假定i-1道为峰值所在道
			if(cps[i]>cps[i-1]) peak[j]=i;	//如果i道的值更大则i道为峰值所在道
			if(cps[i+1]>cps[peak[j]]) peak[j]=i+1;
		j++;
		if(j==MAX) return(j);			//如果已经找完MAX个峰了，则返回
		}
	}
	return(j);					//返回找到的峰值个数
}
*/

/****************************************
 *35.自动校正算法(能谱曲线)
 依据两个校准点的精确数据，求得校准函数
 然后，所有点依此函数求得偏移数据
****************************************/
/*
#include <stdio.h>
#define CH 1024

float cps[CH],temp[CH];
//low and low0分别为能谱线低端的实际道值和校准后应该移至的道值
void petrum_adjust(int low,int low0,int high,int high0)
{
	float k,ch0;			//k为校准函数的斜率，ch0为i校准后的值
	int j;
	for(int i=0;i<CH;i++){
		temp[i]=cps[i];		//将实际值存入暂存区
		cps[i]=0;
	}
	k=(high0-low0)/(high-low);
	for(int i=0;i<CH;i++){		//逐点校准
		ch0=k*(i-low)+low0;	//求得i的校准位置
		while(ch0>0&&ch0<CH-1){
			j=(int)ch0;	//当校准位非整数时，将其整数部分赋给j
			cps[j]+=(j+1-ch0)*temp[i];	//按近者多得的选择分配计数值
			cps[j+1]+=(ch0-j)*temp[i];
		}
	}
}


*/	


	
