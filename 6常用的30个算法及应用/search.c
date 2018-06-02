/*
技巧01：顺序查找
技巧02：二分查找(其序列必须是已排好序的)
技巧03：分块查找
技巧04:哈系查找（没能很好的运行）
*/


/****************************************
技巧01：顺序查找
****************************************/
/*
#include <stdio.h>
void search(int key,int a[],int n)
{
  int i,count = 0,count1=0;
  for (i=0; i<n; i++)
    {
      count++;
      if (a[i]==key)
	{
	  printf ("serch %d times a[%d]=%d\n",count,i,key);
	  count1++;
	}
    }
  if(count1==0)
    printf ("no found!\n");
  else
	  printf ("sum of %d key number in the list!\n",count1);

}

int main(int argc, char *argv[])
{
  int n,key,a[100],i;
  printf ("please input the length of array:\n");
  scanf("%d",&n);
  printf ("please input element:\n");
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  printf ("please input the number which do you want to search:\n");
  scanf("%d",&key);
  search(key,a,n);
  return 0;
}
*/

/****************************************
技巧02：二分查找(其序列必须是已排好序的)
****************************************/
/*
#include <stdio.h>
int BinarySearch(int key,int a[],int n)
{
  int low,high,mid,count=0,count1=0;
  low = 0;
  high = n-1;
  while(low<high)
    {
      count++;              //记录查找次数
      mid=(low+high)/2;     //求出中间位置
      if(key<a[mid])        //当key小于中间值
	high=mid-1;         //确定左子表范围
      else if(key>a[mid])   //当key大于中间值
	low=mid+1;          //确定右子表范围
      else if(key==a[mid])  //当key等于中间值证明查找成功
	{
	  printf ("success!\nsearch %d times! a[%d]=%d\n",count,mid,key);
//	  count1++;         //count1记录查找成功次数
//	  break;
	  return 0;
	}
    }
 // if(count1==0)
    printf ("no found!\n");
    return 1;
}

int main(int argc, char *argv[])
{
  int i,key,a[100],n;
  printf ("please input the length of array:\n");
  scanf("%d",&n);
  printf ("please input the element:\n");
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  printf ("please input the number which do you want to serch:\n");
  scanf("%d",&key);
  BinarySearch(key,a,n);
  return 0;
}
*/

/****************************************
技巧03：分块查找
****************************************/
/*
#include <stdio.h>
struct index           //定义块的结构
{
  int key;
  int start;
  int end;
}index_table[4];       //定义结构体数组

int block_search(int key,int a[])          //自定义实现分块查找
{
  int i,j;
  i=1;
  while(i<=3&&key>index_table[i].key)      //确定在哪个块中
    i++;
  if(i>3)                                  //大于分得的块数，则返回0
    return 0;
  j=index_table[i].start;                  //j等于块范围的起始值
  while(j<=index_table[i].end&&a[j]!=key)  //在确定的块内进行查找
    j++;
  if(j>index_table[i].end)    //如果大于块范围的结束值，则说明没有要查找的数
    j=0;
  return j;
}

int main(int argc, char *argv[])
{
  int i,j=0,k,key,a[16];
  printf ("please input 15 number:\n");
  for(i=1;i<16;i++)
    scanf("%d",&a[i]);
  for (i=1; i<=3; i++)
    {
      index_table[i].start=j+1;    //确定每个范围的起始行
      j=j+1;
      index_table[i].end=j+4;      //确定每个块范围的结束值
      j=j+4;
      index_table[i].key=a[j];     //确定每个块范围中元素的最大值
    }
  printf ("please input the number whick do you want to search:\n");
  scanf("%d",&key);
  k=block_search(key,a);
  if(k!=0)
    printf ("success ! the position is :%d\n",k);
  else
    printf ("no found!\n");
  return 0;
}
*/


/****************************************
技巧04:哈系查找（没能很好的运行）
****************************************/
/*
#include <stdio.h>
#include <time.h>
#define Max 11
#define N 8
int hashtable[Max];
int func(int value)
{
  return value % Max;           //哈希函数
}
int search(int key)              //自定义函数实现哈希函数
{
  int pos,t;
  pos=func(key);                //哈希函数确定出的位置
  t=pos;                        //t存放确定出的位置
  while(hashtable[t]!=key && hashtable[t]!=-1)
       //如果该位置上不等与要查找的关键字且不为空
    {
      t=(t+1)%Max;              //利用线性探测求出下一个位置
      if(pos==t)
       //如果经多次探测又回到原来用哈希函数求出的位置则
       //说明要查找的数不存在
	return -1;
    }
  if(hashtable[t]==-1)          //如果探测的位置是-1则说明要查找的数不存在
    return 0;
  else 
    return t;
}
void creathash(int key)         //自定义函数创建哈系表
{
  int pos,t;
  pos = func(key);              //哈希函数确定元素的位置
  t = pos;
  while(hashtable[t]!=-1)
       //如果该位置有元素存在则在则进行线性探测再散列
    {
      t=(t+1)%Max;
      if(pos==t)
       //如果冲突处理后确定的位置与原位置相同则说明哈系表已满
	{
	  printf ("hash table is full\n");
	  return ;
	}
    }
  hashtable[t]=key;              //将元素放入确定的位置
}
int main(int argc, char *argv[])
{
  int flag[50];
  int i,j,t;
  for(i=0;i<Max;i++)
    hashtable[i]=-1;             //哈希表中初始化位置全置-1
  for(i=0;i<50;i++)
    flag[i]=0;                   //50以内所有数未产生时均标志为0
  rand((unsigned long)time(0));  //利用系统时间做种子产生随机数
  i=0;
  while(i != N)
    {
      t=rand()%50;               //产生一个50以内的随机数附给t
      if (flag[t]=0)             //查看t是否产生过
	{
	  creathash(t);          //调用函数创建哈希表
	  printf ("%2d:\n",t);   //将该元素输出
	  for (j=0; j < Max; j++)
	    printf ("(%2d) \n",hashtable[j]);    //输出哈希表的内容
	  printf ("\n");
	  flag[t]=1;             //将产生的这个数标志为1
	  i++;                   //i自加
	}
    }
  printf ("please input number whick do you want to search:\n");
  scanf("%d",&t);                //输入要查找的元素
  if (t>0&&t<50)
    {
      i=search(t);               //调用search进行哈系查找
      if(i != -1)
	printf ("success! the position is:%d\n",i); //若找到该元素则输出其位置
      else
	printf ("sorry,no found!\n");               //未找到输出提示信息
    }
  else 
    printf ("input error!\n");
  return 0;
}
*/

