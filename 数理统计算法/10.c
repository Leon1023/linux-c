/****************************************************************************************
 * 01.数理统计法消除粗大误差
 *    误差一般分为:系统误差(硬件校准解决），随机误差(多次测量求平均值解决），粗大误差。
 *    一般数据都符合正态分布，只要利用一定的样本值就可以估算出整体数据的期望E和均方差a
 *    根据正态分布理论，99.7%的数据都在(E-3a,E+3a)范围内，95.4%的数据都在(E-2a,E+2a)范围内.
 *    据此，我们可以剔除数据中的超出这个范围的坏样本，从而达到消除粗大误差的目的
****************************************************************************************/
/*
#include <stdio.h>
#include <math.h>
#define M 200
typedef float datatype;

datatype E,a,sample[M];
int n;

datatype average(void)
{
	int i;
	datatype sum=0;
	for(i=0;i<n;++i)
		sum+=sample[i];
	return(sum/n);
}


datatype jfc(void)
{
	int i;
	datatype c=0,sum=0,re=0;
	for(i=0;i<n;++i){
		c=sample[i]-E;
		sum+=c*c;
	}
	return(sqrt(sum/(n-1)));
}


int delete(void)
{
	int i,flag;
	datatype min=0,max=0;
	min=E-3*a;max=E+3*a;
	flag=0;
	for(i=0;i<n;++i)
		if(sample[i]<min || sample[i]>max){
			flag=1;
			if(i<n-1){
				sample[i]=sample[n-1];
				--i;
			}
			--n;
		}
	return(flag);
}


int main(void)
{
	int i;
	printf("\n\t请输入样本个数:");
	scanf("%d",&n);
	for(i=0;i<n;++i){
		printf("\n\t请输入%d样本:",i+1);
		scanf("%f",&sample[i]);
	}
	getchar();
	while(1){
		E=average();
		a=jfc();
		if(!delete()) break;
	}
	printf("\n\t剔除坏样本后的平均值为:%4.2f\t均方差为:%4.2f",E,a);
	getchar();
	return 0;
}
*/

/****************************************************************************************
 *02.线性相关系数的计算
 *     sum(1->n){(xi-xa)(yi-ya)}
 *r=________________________________
 *  sqrt(sum(1->n){(xi-xa)²(yi-ya)²})
 * r为1时,x和y完全正相关。-1时完全负相关。0时完全无关
****************************************************************************************/
/*
#include <stdio.h>
#include <math.h>
#define N 20
float x[N];
float y[N];

float Relation(void)
{
	int i,xa=0,ya=0,sumxx=0,sumyy=0,sumxy=0;
	for(i=0;i<N;++i){
		xa+=x[i];
		ya+=y[i];
	}
	xa/=N;ya/=N;
	for(i=0;i<N;++i){
		sumxy+=(x[i]-xa)*(y[i]-ya);
		sumyy+=(y[i]-ya)*(y[i]-ya);
		sumxx+=(x[i]-xa)*(x[i]-xa);
	}
	return(sumxy/sqrt(sumxx*sumyy));
}
*/
		

