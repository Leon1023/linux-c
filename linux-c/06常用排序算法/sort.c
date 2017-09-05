
/****************************************
技巧01：三大基本排序:冒泡排序，选择排序，插入排序
-->三种方法的时间复杂度均为T(n)=O(n²)，适合小规模的排序场合
...如果排序的数据规模较大，则应选择移动次数少的选择排序
...如果待排序数据已生成(静态排序)，则选择选择排序
...如果待排序数据不断生成(动态排序)，则选择插入排序
...如果是半动态排序。则选择冒泡排序
****************************************/

/*
void display(int i,int j,int n,int S[])
{
	int k;
	printf("\n\n数组下标:");
	for(k=0;k<=n;k++)
		printf("%4d",k);
	printf("\n\n数据数值:");
	for(k=0;k<=n;k++)
		printf("%4d",S[k]);
	printf("\n\n指针位置:");
	for(k=0;k<=n;k++){
		if(k==i){
			if(k!=j)
				printf("   i");
			else
				printf(" i,j");
		}
		else{
			if(k==j)
				printf("   j");
			else
				printf("    ");
		}
	}
	printf("\n\n");
	getchar();
}
*/

//-->：冒泡排序
// 时间复杂度为n²，不适合数据量很大的场合。但尤为适合待排序数组已有初步排序的情况
// 因为他有提前结束机制，同时他对资源需求很少，适合内存较小的嵌入式系统
/*
int main(int argc, char *argv[])
{
  int i,j,t,a[11];
  printf ("please input 10 numbers:\n");
  for(i=1;i<11;i++)
    scanf("%d",&a[i]);
  for(i=1;i<10;i++)        //i代表比较的趟数
    for(j=1;j<11-i;j++)    //j代表每趟两两比较的次数
      if (a[j]>a[j+1])
	{
	  t=a[j];
	  a[j]=a[j+1];
	  a[j+1]=t;
	}
  printf ("the sorted numbers:\n");
  for(i=1;i<=10;i++)
    printf ("%5d",a[i]);
  return 0;
}
*/
/****************************************
-->：选择排序
****************************************/
 /*
#include <stdio.h>
int main(int argc, char *argv[])
{
  int i,j,t,a[11];
  printf ("please input 10 numbers:\n");
  for(i=1;i<11;i++)
    scanf("%d",&a[i]);
  for(i=1;i<=9;i++)
    for(j=i+1;j<=10;j++)
      if (a[i]>a[j])
	{
	  t=a[i];
	  a[i]=a[j];
	  a[j]=t;
	}
  printf ("the sorted numbers:\n");
  for(i=1;i<=10;i++)
    printf ("%5d",a[i]);
  return 0;
}
 */
/****************************************
-->：直接插入排序(抓牌法)
****************************************/
  /*
#include <stdio.h>
 void insort(int s[],int n)
 {            //数组的下标从2开始，0做监视哨，一个数据无可比性
   int i,j;
   for (i=2; i<=n; i++)
     {
       s[0]=s[i];
       j=i-1;
       while(s[0]<s[j])
	 {
	   s[j+1]=s[j];
	   j--;
	 }
       s[j+1]=s[0];
     }
 }
int main(int argc, char *argv[])
{
  int a[11],i;
  printf ("please input number:\n");
  for(i=1;i<=10;i++)
    scanf("%d",&a[i]);
  printf ("the original order:\n");
  for(i=1;i<=10;i++)
    printf ("%5d",a[i]);
  insort(a,10);
  printf ("\nthe sorted numbers:\n");
  for(i=1;i<=10;i++)
    printf ("%5d",a[i]);
  return 0;
}
  */
/****************************************
技巧02：归并排序(递归算法)
****************************************/
/*
#include <stdio.h>
#define MAX 100
int n,s[MAX],d[MAX];

void merge(int s[],int d[],int x1,int x2,int x3)
{              //实现一次归并排序函数
  int i,j,k;
  i=x1;        //第一部分的开始位置
  j=x2;      //第二部分的开始位置
  k=x1;
  while((i<x2)&&(j<x3))			//当i和j都在两个要合并的部分中
    if (s[i]<=s[j]) d[k++]=s[i++];	//筛选两部分中较小的元素放到数组s中
    else d[k++]=s[j++];
  while(i<x2) 			       //将x1，x2范围内的未比较的数顺次加到数组r中
    d[k++]=s[i++];
  while(j<x3)				//将x2，x3范围内的未比较的数顺次加到数组r中
    d[k++]=s[j++];
}

void merge_pass(int s[],int d[],int length)
{
	int i=0,j=0;
	while((i+2*length-1)<n){
		merge(s,d,i,i+length,i+2*length);
		i+=length*2;
	}
	if(i+length<n)
		merge(s,d,i,i+length,n);
	else
		for(j=i;j<n;++j)
			d[j]=s[j];
}


void disp(int a[])
{
	int i=0;
	printf("\n\t");
	for(;i<n;++i)
		printf("%4d",a[i]);
	printf("\n");
}


void merge_sort(void)
{
  int length=1;
  while(length<n){
	  merge_pass(s,d,length);
	  printf("\nlength=%d",length);
	  disp(d);
	  length*=2;
	  merge_pass(d,s,length);
	  printf("\nlength=%d",length);
	  disp(s);
	  length*=2;
  }   
  printf("\n\nafter sorted:");
  disp(s);
}



int main(void)
{
  int i=0;
  while(1){
	  printf ("\nHow many numbers do you sored:");
	  scanf("%d",&n);
	  if(n<MAX) break;
	  printf("\nnumber you sorted must small than %d!",MAX);
  }
  for(i=0;i<n;++i){        //从键盘中输入10个数
    printf("\nnumber %d:",i+1);
    scanf("%d",&s[i]); 
  }
  printf("\nbefor sorted:");
  disp(s);
  merge_sort();     //调用merge_sort函数进行归并排序
}
*/
/****************************************
技巧03：改进型归并排序(第一轮扫描时进行一次排序，以减少队列大小)
****************************************/
/*
#include <stdio.h>
#define MAX 10			//maxed number of be sorted
#define MAXS ((MAX+1)/2+2)	//首轮扫描归并后，存放子序列起始位置的循环队列最多需要(MAX+1)/2个空间，
                                //再加上循环队列的头front及一个代表结尾的-1，所以还需要2个存储空间

int n,times=0,SR[MAX],TR[MAX];	//n代表实际待排序个数，SR代表待排序数组，TR代表中间交换数组
typedef struct{
	int d[MAXS];
	int front,rear;
}sequeue;//存放各子序列开头位置的循环队列的数据结构
sequeue sq;

int in_seq(int x)//如果队列未满，则子序列其实位置入队
{
	int i;
	if(sq.front==(sq.rear+1)%MAXS)
		return 0;
	else{
		sq.rear=(sq.rear+1)%MAXS;
		sq.d[sq.rear]=x;
		return 1;
	}
}

int out_seq(void)//如果循环队列非空，则将一个子序列的起始位置出队
{
	if(sq.front==sq.rear) return 0;
	else{
		sq.front=(sq.front+1)%MAXS;
		return(sq.d[sq.front]);
	}
}

void disp(int a[])//显示待排序数组的当前状态
{
	int i=0;
//	printf("\n\t");
	for(;i<n;++i)
		printf("%4d",a[i]);
	printf("\n");
}

void merger(int s[],int d[],int x1,int x2,int x3)
{              //实现一次归并排序函数,x1,x2,x3分别代表连续子序列的起始位置
  int i,j,k;
  i=x1;        //子序列1的开始位置
  j=x2;      //子序列2的开始位置
  k=x1;//k代表这两个子序列归并后的有序序列的位置
  while((i<x2)&&(j<x3))			//当i和j都在各自的子序列中时
    if (s[i]<=s[j]) d[k++]=s[i++];	//筛选两部分中较小的元素放到数组d中
    else d[k++]=s[j++];
  while(i<x2) 			       //将子序列1中的未比较的数顺次加到数组d中
    d[k++]=s[i++];
  while(j<x3)				//将子序列2中的未比较的数顺次加到数组d中
    d[k++]=s[j++];
  printf("\nmerger %d-->",++times);
  disp(d);
}

int merger_pass(int s[],int d[])
{
	int x1,x2,x3,i,count=0;
	x1=out_seq();//从起始位置循环队列中取出第一个位置
	while(1){
		x2=out_seq();//再取出第二个位置
		if(x2==-1){//如果再取出的这个位置是结束标志，说明没有子序列2合并了，故将子序列1依次搬到目的数组中
			for(i=x1;i<n;++i)
				d[i]=s[i];
			++count;
			in_seq(x1);
			in_seq(-1);
			return(count);
		}
		x3=out_seq();//取出第三个子序列的起始位置
		if(x3==-1){//如果他为结束标志，说明这两个子序列合并后这一轮合并就算结束了
			x3=n;
			merger(s,d,x1,x2,x3);
			++count;
			in_seq(x1);
			in_seq(-1);
			return(count);
		}
		merger(s,d,x1,x2,x3);
		++count;
		in_seq(x1);
		x1=x3;
	}
}


int merger_pass_first(int s[],int d[])//首轮扫描并合并
{
	int x1,x2,x3,i,count=0;
	x1=0;//从第一个元素开始扫描，并令子序列1的起始位是0
	while(1){
		for(i=x1+1;i<n;++i)
			if(s[i]<s[i-1]) break;
		x2=i;//找到子序列2的起始位
		if(x2==n){//如果它为数组的最后元素的后面，说明原数组已经排好序了
			for(i=x1;i<n;++i) d[i]=s[i];
			in_seq(x1);
			in_seq(-1);
			++count;
			return(count);
		}

		for(i=x2+1;i<n;++i)
			if(s[i]<s[i-1]) break;
		x3=i;//找到子序列3的起始位，也是子序列2的结束位+1
		if(x3==n){//如果子序列2结尾刚好是数组结尾则合并这两个子序列，并标记序列结束
			merger(s,d,x1,x2,x3);
			in_seq(x1);
			in_seq(-1);//标记序列结束
			++count;
			return(count);
		}
		merger(s,d,x1,x2,x3);//正常合并后
		in_seq(x1);
		++count;
		x1=x3;//把第三个子序列的起始位，作为下轮合并操作的子序列1的起始位
	}
}

int merger_sort(int s[],int d[])
{
	int i;
	sq.front=sq.rear=MAXS-1;//初始化循环队列为空
	merger_pass_first(s,d);//进行首轮归并及创建循环队列
//	disp(d);
	while(1){
		if(merger_pass(d,s)==1)//进行第二轮归并，如果归并结束则返回
			return 0;
//		disp(s);
		merger_pass(s,d);//如果排序未完成，则再进行新一轮次的归并
//		disp(d);
	}
}


int main(void)
{
  int i=0;
  while(1){
	  printf ("\nHow many numbers do you sored:");
	  scanf("%d",&n);
	  if(n<=MAX) break;
	  printf("\nnumber you sorted must small than %d!",MAX);
  }
  for(i=0;i<n;++i){        //从键盘中输入n个数
    printf("\nnumber %d:",i+1);
    scanf("%d",&SR[i]); 
  }
  printf("\nbefor sorted:");
  disp(SR);
  merger_sort(SR,TR);     //调用merge_sort函数进行归并排序
  printf("\nafter sorted:");
  disp(SR);
}

*/
/****************************************
技巧04：希尔排序(插入排序的改进）
****************************************/
/*
#include <stdio.h>
void shsort(int s[],int n)
{
  int i,j,d;
  d=n/2;            //确定固定增量值
  while(d>=1)
    {
      for (i=d+1; i<=n; i++)  //数组下标从d+1开始进行直接插入排序
	{
	  s[0]=s[i];          //设置监视哨
	  j=i-d;              //确定要进行比较的元素的最右边位置
	  while((j>0)&&(s[0]<s[j]))
	    {
	      s[j+d]=s[j];    //数据右移
	      j=j-d;          //向左移d个位置
	    }
	  s[j+d]=s[0];        //在确定的位置插入s[i]
	}
      d=d/2;                  //增量变为原来的一半
    }
}
int main(int argc, char *argv[])
{
  int a[11],i;
  printf ("please input numbers:\n");
  for(i=1;i<=10;i++)
    scanf("%d",&a[i]);
  shsort(a,10);
  printf ("the sorted numbers:\n");
  for(i=1;i<=10;i++)
    printf ("%5d",a[i]);
  return 0;
}
*/
/****************************************
技巧05:快速排序
主要的算法思想是在带排序的n个数据中取第一个数据作为基准值，将所有的记录分为3组，使得
第一组中各数据值均小于或等于基准值，第二组便是做基准值的数据，第三组中个数举值均大于
或等于基准值。这便实现了第一趟分隔，然后再对第一组和第三组分别重复上述方法。
****************************************/
/*
#include <stdio.h>
#define MAX 100
int SR[MAX+1];
int n;


void disp(int a[])//显示待排序数组的当前状态
{
	int i=1;
//	printf("\n\t");
	for(;i<=n;++i)
		printf("%4d",a[i]);
	printf("\n");
}

void qusort(int start,int end)
{          //自定义快排函数
  int i,j;                   
  i=start;
  j=end;
  SR[0]=SR[i];            //设置基准值
  while(i<j)
    {
      while(i<j&&SR[0]<SR[j]) j--;                //位置左移
      if(i<j) SR[i++]=SR[j];        //将s[j]放到s[i]的位置上,i位置右移
      while(i<j&&SR[i]<=SR[0]) i++;                //位置右移
      if (i<j) SR[j--]=SR[i];        //将大于基准值的s[j]放到s[i]位置,j位置右移
    }  
  SR[i]=SR[0];                //将基准值放入指定位置
  if(start<i) qusort(start,j-1);    //对分隔出的部分递归调用函数qusort()
  if(i<end)  qusort(j+1,end);
}

int main(void)
{
  int i=0;
  while(1){
	  printf ("\nHow many numbers do you sored:");
	  scanf("%d",&n);
	  if(n<=MAX) break;
	  printf("\nnumber you sorted must small than %d!",MAX);
  }
  for(i=1;i<=n;++i){        //从键盘中输入n个数
    printf("\nnumber %d:",i);
    scanf("%d",&SR[i]); 
  }
  printf("\nbefor sorted:");
  disp(SR);
  qusort(1,n);     //调用merge_sort函数进行归并排序
  printf("\nafter sorted:");
  disp(SR);
}
*/


/****************************************
技巧06:快速排序(seq)
主要的算法思想是在带排序的n个数据中取第一个数据作为基准值，将所有的记录分为3组，使得
第一组中各数据值均小于或等于基准值，第二组便是做基准值的数据，第三组中个数举值均大于
或等于基准值。这便实现了第一趟分隔，然后再对第一组和第三组分别重复上述方法。
****************************************/
/*
#include <stdio.h>
#define OVER -1		//flag of sequeue empty or full
#define MAX 100			//maxed number of be sorted
#define MAXS 101		//length of sequeue of rotate

int n,s[MAX+1];	//n代表实际待排序个数，SR代表待排序数组，SR[0] for swap
typedef struct{
	int d[MAXS];
	int front,rear;
}sequeue;//存放各子序列开头位置的循环队列的数据结构
sequeue sq;

int in_seq(int x)//如果队列未满，则子序列其实位置入队
{
	int i;
	if(sq.front==(sq.rear+1)%MAXS)
		return OVER;
	else{
		sq.rear=(sq.rear+1)%MAXS;
		sq.d[sq.rear]=x;
		return 1;
	}
}

int out_seq(void)//如果循环队列非空，则将一个子序列的起始位置出队
{
	if(sq.front==sq.rear) return OVER;
	else{
		sq.front=(sq.front+1)%MAXS;
		return(sq.d[sq.front]);
	}
}

void disp(int a[])//显示待排序数组的当前状态
{
	int i=1;
//	printf("\n\t");
	for(;i<=n;++i)
		printf("%4d",a[i]);
	printf("\n");
}

int seq_qusort(void)
{
	int i,j,l,r;
	in_seq(1);
	in_seq(n);
	while(1){
		l=out_seq();
		r=out_seq();
		if(l==OVER) return 0;
		i=l;j=r;
		s[0]=s[i];
		while(i<j){
			while(j>i&&s[j]>s[0]) j--;
			if(j>i) s[i++]=s[j];
			while(i<j&&s[i]<s[0]) i++;
			if(i<j) s[j--]=s[i];
		}
		s[i]=s[0];
		disp(s);
		if(l<i-1){
			in_seq(l);
			in_seq(i-1);
		}
		if(i+1<r){
			in_seq(i+1);
			in_seq(r);
		}
	}
}




int main(void)
{
  int i=0;
  sq.front=sq.rear=0;
  while(1){
	  printf ("\nHow many numbers do you sored:");
	  scanf("%d",&n);
	  if(n<=MAX) break;
	  printf("\nnumber you sorted must small than %d!",MAX);
  }
  for(i=1;i<=n;++i){        //从键盘中输入n个数
    printf("\nnumber %d:",i);
    scanf("%d",&s[i]); 
  }
  printf("\nbefor sorted:");
  disp(s);
  seq_qusort();     //调用merge_sort函数进行归并排序
  printf("\nafter sorted:");
  disp(s);
}
*/
