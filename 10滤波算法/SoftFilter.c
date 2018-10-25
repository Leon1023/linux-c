/********************************
 *
 *01.程序判断滤波(用于精度不高的低通滤波）
 * 依据前两个点的数值，预测第三个点的采样
 * 值是否可信即有没有超出最大允许变化范围
 * 仅用于干扰很小的偶发毛刺型滤波
********************************/
#include <stdio.h>
#define 10 Delt		// max allowed alternation 

float sample(void);	//function of sample
float history[3];	//recently three pointer of sampled value
float filter(void)	
{
	float ;
	history[0] = sample();	//function of sample
	delay(10);		//sample interval
	history[1] = sample();
	delay(10);
	while(1){
		new = sample();
		if(new-history[1]>Delt || history[1]-new>Delt){
			new = 2*history[1]-history[0];//lined predicated 
			if(new<0) new = 0;		//ADC vaule is high then zero
			if(new>0) new = 4096;		//ADC value is small then 4k when 12bit
		}
		history[0]=history[1];
		history[1]=new;
		control();				//related control function
		delay(10);
	}
}
	
/********************************
 *02.中值滤波(用于低通滤波）
 *   连续进行奇数次采样，然后对其排序，取中间值为本阶段采样的可信值
 *   函数分两个周期:大采样周期T1(实际要取得的采样值）
 *   小采样周期T2:对大周期中的每个采样点再次采样奇数次并取中间值
 *   受限于T1远大于T2,而T2受限于要大于突发毛刺干扰的持续时间
 *   一般也只能应用于频率较低的场合
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;

INT32U smp[60];		//存放有效样本数据的数组
void filter(INT32U *pdata)
{
	INT8U i,j,k,n;
	INT16U R[6];//定义连续采样(T2）的数组
	for(n=0;n<60;n++){
		for(j=1;j<6;j++){//获取连续的五个采样值
			R[j]=sample();
			delay(T2);//延迟T2
		}
		for(i=1;i<=3;i++){//利用选择排序法求得刚刚连续采样5次值的排序后中间第3次值为有效采样值
			k=i;
			for(j=i+1;j<6;j++)
				if(R[j]<R[k]) k=j;
			if(k!=i)
				R[0]=R[k];R[k]=R[j];R[j]=R[0];
		}
		smp[n]=R[3];
		delay(T1);//延迟T1周期
	}
}

/********************************
 *03.算术平均滤波(用于低通滤波）
 *   类似于中指滤波算法，不同之处在于有效采样值的获得是通过
 *   对连续采样值的算术平均，而非中值选择。
 *   该法对随机干扰的抑制较好，但却难以抑制毛刺型干扰
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;
#define N 10 		//定义算术平均的样本数
INT32U smp[60];		//存放有效样本数据的数组

void filter(INT32U *pdata)
{
	INT8U i,j,k,n;
	INT16U R[N],sum=0;//定义连续采样(T2）的数组
	for(n=0;n<60;n++){
		for(j=0;j<N;j++){//获取连续的N个采样值
			R[j]=sample();
			sum+=R[j];
			delay(T2);//延迟T2
		}
		smp[n]=sum/N;
		delay(T1-N*T2);//延迟T1周期
	}
}


/********************************
 *04去极值平均均滤波(用于低通滤波）
 *   类似于算术平均滤波算法，不同之处在于有效采样值smp[n]的获得是通过
 *   对连续N采样值的去掉最大max和最小min两个样本值之后的N-2算术平均。
 *   该法对随机干扰的抑制较好，也对抑制毛刺型干扰有一定作用
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;
#define N 10 		//定义算术平均的样本数
INT32U smp[60];		//存放有效样本数据的数组

void filter(INT32U *pdata)
{
	INT8U i,n;
	INT16U new=0,sum=0,max=0,min=0;//定义连续采样(T2）的数组
	for(n=0;n<60;n++){
		for(i=0;i<N;i++){//获取连续的N个采样值
			new=sample();
			if(new>max) max=new;
			if(new<min) min=new;
			sum+=new;
			delay(T2);//延迟T2
		}
		smp[n]=(sum-max-min)/(N-2);
		delay(T1-N*T2);//延迟T1周期
	}
}

/********************************
 *05.滑动平均滤波
 *   类似于算术平均滤波算法，不同之处在于有效采样值smp[n]的获得是通过
 *   对前面连续N-1次有效采样值及当前采样值的共N次(窗口）的算术平均。
 *   它避免了主次采样周期的限制
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;
#define N 6 				//定义滑动窗口的大小(平均的样本个数）
INT8U p;				//定义循环队列的入队下标
INT32U history[N],smp;			//采样值的历史记录(循环队列）smp为返回的当前有效采样值


void filter(INT32U *pdata)
{
	INT8U i,T;			//辅助变量及采样周期
	INT16U sum=0;
	for(p=0;p<N-1;p++){		//获取连续的N-1个采样值
		history[p]=sample();
		delay(T);		//延迟T
	}
	while(1){
		history[p]=sample();//新的采样数据入队
		p++;//调整入队指针
		if(p==N) p=0;		//指针循环控制
		for(i=0;i<N;++i)
			sum+=history[i];//累加窗口内的数据
		smp=sum/N;//获得有效采样值
		delay(T);//采样周期为T
	}
}

/********************************
 *06.滑动加权滤波
 *   类似于滑动平均滤波算法，不同之处在于对前面N-1个采样值
 *   分别乘以加权系数，以提高近处的权重降低远方的权重。
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;
#define N 6 				//定义滑动窗口的大小(平均的样本个数）
INT8U p,k[N]={1,2,3,4,5,6};		//定义循环队列的入队下标,及加权系数数组
INT32U history[N],smp;			//采样值的历史记录(循环队列）smp为返回的当前有效采样值


void filter(INT32U *pdata)
{
	INT8U i,j,T;			//辅助变量及采样周期
	INT16U A=0,sum=0;		//定义加权系数总和A及窗口采样值总和
	for(p=0;p<N-1;p++){		//获取连续的N-1个采样值
		history[p]=sample();
		delay(T);		//延迟T
	}
	while(1){
		history[p]=sample();//新的采样数据入队
		p++;//调整入队指针
		if(p==N) p=0;		//指针循环控制
		j=p;//j指向最远的采样值
		for(i=0;i<N;++i){
			sum+=k[i]*history[j];//累加窗口内的加权后数据
			++j;
			if(j==N) j=0;		//指针循环控制
		}
		i=0;
		while(i<N)
			A+=k[i];//求加权系数总和
		smp=sum/A;//获得有效采样值
		delay(T);//采样周期为T
	}
}


/********************************
 *07.一阶滞后滤波
 *   类似于加权平均滤波算法，不同之处在于平均的采样值只有两个。
 *   即y(n)=a*x(n)+(1-a)y(n-1);a为滤波系数，其值远小于1。
 *   y(n)为所求当前采样有效值,y(n-1)为上次所求的有效采样值，
 *   x(n)为当前实际采样值.截止频率为f=a/(2*pi*T)
*******************************/
typedef unsigned char INT8U;
typedef unsigned int INT32U;
#define a 0.006 		//加权系数
INT32U smp;			//smp为当前有效采样值

void filter(INT32U *pdata)
{
	INT32U new;			//实际采样值
	smp=sample();
	delay(T);		//延迟T
	while(1){
		new=sample();
		smp=a*new+(1-a)*smp;
		delay(T);
	}
}

