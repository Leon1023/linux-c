/****************************************
技巧01：结构体简单应用
****************************************/
/*
#include <stdio.h>
struct student
{
  int num;
  char name[20];
  char sex;
  int age;
  float score;
};
int main(int argc, char *argv[])
{
  struct student student1={1001,"liming",'M',20,93.5};
  printf ("the information of the student is:\n");
  printf ("num:%d\n",student1.num);
  printf ("name:%s\n",student1.name);
  printf ("sex:%c\n",student1.sex);
  printf ("age:%d\n",student1.age);
  printf ("score:%5.1f\n",student1.score);
  return 0;
}
*/
/****************************************
技巧02：找最高分
****************************************/
/*
#include <stdio.h>
struct student
{
  int num;
  char name[20];
  float score;
};
int main(int argc, char *argv[])
{
  int i,m;
  float maxscore;
  struct student stu[5]=
  {
    {101,"liming",89},
    {102,"zhanghong",95},
    {103,"lili",89},
    {104,"weichen",85},
    {105,"yangfan",75}
  };
  m=0;
  maxscore=stu[0].score;
  for (i=1; i<5; i++)
    {
      if (stu[i].score>maxscore)
	{
	  maxscore=stu[i].score;
	  m=i;
	}
    }
  printf ("the maxmum score is :%5.1f\n",maxscore);
  printf ("the student number is:%d\n",stu[m].num);
  printf ("the student name is:%s\n",stu[m].name);
  return 0;
}
*/
/****************************************
技巧03:平均成绩
****************************************/
/*
#include <stdio.h>
int main(int argc, char *argv[])
{
  struct student_score
  {
    int mid;
    int end;
    int ave;
  }score;
  printf ("please input score(midterm and end of term:\n");
  scanf("%d%d",&score.mid,&score.end);
  score.ave=(score.mid+score.end)/2;
  printf ("average=%d\n",score.ave);
  return 0;
}
*/
/****************************************
技巧04：比较计数
****************************************/
 /*
#include <stdio.h>
#define N 5
struct order
{
  int num;
  int con;
}a[20];
int main(int argc, char *argv[])
{
  int i,j;
  for (i=0; i<N; i++)
    {
      scanf("%d",&a[i].num);
      a[i].con=0;
    }
  for(i=N-1;i>=1;i--)
    for(j=i-1;j>=0;j--)
      if(a[i].num<a[j].num)
	a[j].con++;
      else
	a[i].con++;
  printf ("the order is:\n");
  for(i=0;i<N;i++)
    printf ("%d\t%d\t\n",a[i].num,a[i].con);
  return 0;
}
 */
/****************************************
技巧05：信息查询
****************************************/
/*
#include <stdio.h>
#include <string.h>
#define MAX 10
struct aa
{
  char name[15];
  char tel[15];
};
int readin(struct aa *a)     //自定义函数，用来存储姓名及电话号码
{
  int i=0,n=0;
  while(1)
    {
      scanf("%s",a[i].name);     //输入姓名
      if(!str_cmp(a[i].name,"#")) 
	break;
      scanf("%s",a[i].tel);      //输入电话号码
      i++;
      n++;                       //记录的条数
    }
  return n;                      //返回条数
}
void search(struct aa *b,char *x,int n)
//自定义查找姓名所对应的电话号码函数
{
  int i;
  i=0;
  while(1)
    {
      if (!str_cmp(b[i].name,x))   //查找与输入姓名相匹配的记录
	{
	  printf ("name:%s tel:%s\n",b[i].name,b[i].tel);
	  break;
	}
      else
	i++;
      n--;
      if (n==0)
	{
	  printf ("no found!\n");
	  break;
	}
    }
}
int main(int argc, char *argv[])
{
  struct aa s[MAX];
  int num;
  char name[15];
  num=readin(s);
  printf ("please input the name:\n");
  scanf("%s",name);
  search(s,name,num);
  return 0;
}
*/
/****************************************
技巧06：计算开机时间(函数kbhit有问题）
****************************************/
/*
#include <stdio.h>
struct time      //定义结构体time，存储时间信息
{
  int hour;
  int minute;
  int second;
}t;
int main(int argc, char *argv[])
{
  FILE *fp = fopen("time", "r");    //定义文件类型指针fp
  fread(&t,sizeof(struct time),1,fp);  //以只读方式打开文件time
  while(!kbhit())                  //当无按键时执行循环体语句
    {
      rewind(fp);                 //将文件指针设置到文件起点
      sleep(1);                   //程序停止1秒钟
      fread(&t,sizeof(struct time),1,fp);//读取文件中的内容
      if (t.second == 59)          //如果到60秒
	{
	  t.minute=t.minute+1;     //如果到60秒分钟数加1
	  if (t.minute==60)        //判断是否到60分钟
	    {
	      t.hour=t.hour+1;     //到60分钟小时数加1
	      t.minute=0;          //分数置0
	      t.second=0;          //秒数置0
	    }
	}
      else
	t.second=t.second+1;       //秒数加1
      printf ("%d:%d:%d\n",t.hour,t.minute,t.second);//输出积累开机时间
      FILE *fp = fopen("time", "w");        //以可写方式打开time文件
      fwrite(&t,sizeof(struct time),1,fp);  //将结构体中的新内容存储
      fclose(fp);
    }
  return 0;
}
*/
/****************************************
技巧07：创建双向链表
****************************************/

/****************************************
emacs的剪切为C-w；复制为M-w
成员运算符（.）和指向结构体成员的运算符（->）两者都是用来引用结构体变量
成员的，但是他们的应用环境是完全不同的。
成员运算符（.）用在一般结构体变量中，表示结构体变量的成员。
指向结构体成员运算符（->）与指向结构体变量的指针连用，表示指向结构体变量
指针的成员。
strut student
{
  int num;
  char name[10];
};
struct student stu, *s=&stu;
其中，stu.num s->num是正确的引用方法，但是stu->num和s.num是不允许。
其实，s->num就相当于（*s）.num。
****************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct node
{
  char name[20];    //存储数据
  struct node *prior,*next;  //指针类型，其指向本结构体类型的数据
}stud;             //双向链表的结构定义
stud *create(int n)
{
  stud *p,*h,*s;   //声明结构体指针
  int i;
  h=(stud*)malloc(sizeof(stud));   //申请节点空间
  h->name[0]='\0';  
  h->prior=NULL;
  h->next=NULL;
  //第0个节点称为整个链表的头节点，它一般不存放具体数据，只是存放第一个
  //节点的地址，也称为头指针
  p=h;
  for (i=0; i<n; i++)
    {
      s=(stud*)malloc(sizeof(stud));
      p->next=s;                   //指定后继节点
      printf ("input the %d student's name: \n",i+1);
      scanf("%s",s->name);
      s->prior=p;               //指定前驱节点
      s->next=NULL;
      p=s;
    }
  p->next=NULL;
  return (h);
}
stud *search(stud *h,char *x)
{
  stud *p;
  char *y;
  p=h->next;
  while(p)
    {
      y=p->name;
      if(str_cmp(y,x)==0)  //如果是要删除的节点，则返回地址
	return (p);
      else 
	p=p->next;
    }
  printf ("cannot find data!\n");
}
void del(stud *p)
{
  p->next->prior=p->prior;    //p的下一个节点的前驱指针指向p的前驱节点
  p->prior->next=p->next;     //p的前驱节点的后继指针指向p的后继节点
  free(p);
}
int main(int argc, char *argv[])
{
  int number;             //定义变量
  char sname[20];         //定义字符型数组
  stud *head,*sp;
  puts("please input the size of the list:");
  scanf("%d",&number);    //输入链表节点数
  head=create(number);     //创建链表
  sp=head->next;
  printf ("now the double list is:\n");
  while(sp)               //输出链表中数据
    {
      printf ("%s\n",&*(sp->name));   
      sp=sp->next;
    }
  printf ("please input the name which you want to find:\n");
  scanf("%s",sname);
  sp=search(head,sname);      //查找指定节点
  printf ("the name you want to find is: %s\n",*&sp->name);
  del(sp);                    //删除节点
  sp=head->next;
  printf ("now the double list is:\n");
  while(sp)                   //输出当前链表中数据
    {
      printf ("%s ",&*(sp->name));
      sp=sp->next;
    }
  printf ("\n");
  return 0;
}
*/
/****************************************
技巧08：创建循环链表
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
typedef struct student  //student为结构体名
{
  int num;       //结构体成员
  struct student *next;    //结构体成员
}LNode,*LinkList;      //LNode *LinkList为结构体变量名
LinkList create(void)  //自定义函数，实现创建一个循环列表
{
  LinkList head;
  LNode *p1,*p2;
  char a;
  head = NULL;
  a=getchar();
  while(a!='\n')
    {
      p1=(LNode*)malloc(sizeof(LNode));   //分配空间
      p1->num=a;                    //数据域赋值
      if(head==NULL)
	head=p1;
      else
	p2->next=p1;
      p2=p1;              //将指针p1附给指针p2，相当与前者指向后者
      a=getchar();
    }
  p2->next=head;       //尾节点指向头节点
  return head;         //返回循环链表的头指针
}
int main(int argc, char *argv[])
{
  LinkList L1,head;
  printf ("please input the linklist:\n");
  L1=create();
  head=L1;
  printf ("the resultant linklist is:\n");
  printf ("%c ",L1->num);
  L1=L1->next;         //指向下一个节点
  while(L1!=head)
    {
      printf ("%c ",L1->num);
      L1=L1->next;
    }
  return 0;
}
*/
/****************************************
技巧09：创建顺序表并插入元素
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define Listsize 100
struct sqlist
{
  int data[Listsize];
  int length;
};
void InsertList(struct sqlist *l,int t,int i)  //创建自定义函数
{
  int j;
  if (i<0||i>l->length)
    {
      printf ("position error\n");
      exit(1);
    }
  if (l->length>=Listsize)
    {
      printf ("overflow\n");
      exit(1);
    }
  for(j=l->length-1;j>=i;j--)       //插入元素
    l->data[j+1]=l->data[j];
  l->data[i]=t;
  l->length++;
}
int main(int argc, char *argv[])
{
  struct sqlist *sq;
  int i,n,t;
  sq=(struct sqlist*)malloc(sizeof(struct sqlist));
  sq->length=0;
  printf ("please input the size of the list:\n");
  scanf("%d",&n);
  printf ("please input the elements of the list:\n");
  for (i=0; i<n; i++)
    {
      scanf("%d",&t);
      InsertList(sq,t,i);
    }
  printf ("now the list is:\n");
  for (i=0; i<sq->length; i++)
    {
      printf ("%d ",sq->data[i]);
    }
  return 0;
}
*/
/****************************************
技巧10:向链表中插入节点
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct student
{
  int num;
  struct student *next;
};
struct student *create(int n)
{
  int i;
  struct student *head,*p1,*p2;
  int a;                   
  head=NULL;                 //初始化头节点地址
  printf ("the record:\n");
  for (i=n; i>0; --i)
    {
      p1=(struct student*)malloc(sizeof(struct student));
      scanf("%d",&a);
      p1->num=a;
      if (head==NULL)       //（head/p2)-->(p1/p2)-->...
	{
	  head=p1;
	  p2=p1;
	}
      else
	{
	  p2->next=p1;       //指定后继指针
	  p2=p1;
	}
    }
  p2->next=NULL;             //后继指针为空，链表结束
  return head;               //返回头节点
}
struct student *insertnode(struct student *head,char x,int i)
{
  int j=0;
  struct student *p,*s;
  p=head;
  while(p&&j<i-1)     //找到要插入的位置
    {
      p=p->next;
      ++j;            //先对j进行++，然后再用j进行运算
    }
  if(!p||j>i-1)
    exit(1);
  s=(struct student*)malloc(sizeof(struct student));
  s->num=x;
  s->next=p->next;
  p->next=s;
}
int main(int argc, char *argv[])
{
  int n,i;
  int x;
  struct student *q;
  printf ("input the count of the nodes you want to creat:\n");
  scanf("%d",&n);
  q=create(n);
  i=2;
  x=123;
  insertnode(q,x,i);
  printf ("the result is:\n");
  while(q)              //输出插入节点后的链表
    {
      printf ("%d ",q->num);
      q=q->next;
    }
  return 0;
}
*/
/****************************************
EMACS的字符串搜索C-s向后查找，C-r向前查找，重复组合键时会搜索下一个匹配的关键字
而针对替换操作为M-%（alt+shift+5），形式为（被替换操作符）with（替换的操作符）
撤销操作是C-/，而自动补全操作快捷键是M-/，切换buffer快捷键是C-x b。
每行前边加入特定的字符串快捷键为C-x r t，即实际为rectangle操作。
****************************************/

/****************************************
技巧11:堆分配存储串基本操作(char *s指向字符串首地址，并以\0结尾)
****************************************/
/*
#include<stdio.h>
#include<stdlib.h>
#define maxsize 20

//求字符串长度
int str_len(char *s)
{
	int len=0;
	while(*s++!='\0')
		len++;
	return(len);
}

//字符串复制s->t
void str_cpy(char *s,char *t)
{
	while(*s!='\0')
		*(t++) = *(s++);
	*t='\0';
}

//字符串连接s=s+t
void str_concat(char *s,char *t)
{
	while(*s!='\0')
		s++;
	while(*t!='\0')
		*(s++)=*(t++);
	*s = '\0';
}

//求子串：将字符串s中第pos位置开始的长度为len的子串存到t中
void str_sub(char *s,char *t,int pos,int len)
{
	if(pos<1 || pos> str_len(s)){
		printf("您输入的位置有误，请重新输入：");
		return;
	}
	if(len<1){
		printf("您输入的子串长度有误，请重新输入：");
		return;
	}
	s = s+pos-1;
	while((len--)>0 && *s!='\0')
		*(t++) = *(s++);
	*t = '\0';
}

//比较两个字符串的大小,s>t返回1，s<t返回-1，s=t返回0
int str_cmp(char *s,char *t)
{
	while(*s!='\0'&&*t!='\0'){
		if(*s>*t)
			return 1;
		else if(*s<*t)
			return -1;
		else{
			*(s++);
			*(t++);
		}
	}
	if(*s=='\0'&&*t=='\0')
		return 0;
	else if(*s=='\0'&&*t!='\0')
		return -1;
	else
		return 1;
}

//字符串插入
//将字符串t插入到字符串s的pos位置
void str_insert2(char *s,char *t,int pos)
{
	int i;
	int lens = str_len(s);
	int lent = str_len(t);
	if(pos<1||pos>lens){
		printf("您输入的位置有误，请重新输入：");
		return;
	}
	for(i=lens;i>=(pos-1);i--)//将字符串s从被插入位置向后移动字符串t长度个空间
		*(s+i+lent) = *(s+i); 
	while(*t!='\0')//将字符串t复制到s串中指定位置
		*((s++)+(pos-1))=*t++;
}

//从串s中的pos位置删除长度为len的子串
void str_del(char *s,int pos,int len)
{
	int i,lens=str_len(s);
	if((pos+len)>=lens)
		*(s+pos-1) = '\0';
	else{
		i=pos+len-1;
		while(*(s+i)!='\0'){
			*(s+i-len) = *(s+i);
			i++;
		}
		*(s+i-len) = '\0';
	}
}

//串定位
int str_index(char *s,char *t,int pos)
{
	int lens,lent,i=pos-1,j=0;
	lens = str_len(s);
	lent = str_len(t);
	while(i<=(lens-lent)&&j<lent){
		if(*(s+i)==*(t+j)){
			i++;
			j++;
		}
		else{
			i = (i-j+1);
			j = 0;
		}
	}
		if(j==lent)
			return(i-lent+1);
		else
			return 0;
	}

//从串s中的pos位置插入长度为len的子串t
void str_insert(char *s,char *t,int pos)
{
	int i=0,lens=str_len(s),lent=str_len(t);
	char *x;
	//当插入位置大于字符串长度时，一律插在串的末尾
	if(pos>=lens){
		s += lens;
		while(*t!='\0')
			*s++=*t++;
		*s = '\0';
	}
	//当插入位置小于串的开始位置时，一律插在串的前面
	else if(pos<1){
		x = s+lens;//将指针指向串的末尾'\0'的位置
		while(lens>=0){//将串的每个元素向后移动lent个位置
			*(x+lent) = *x;
			x--;
			lens--;
		}
		while(*t!='\0'){//将需要插入的串复制到原字符串空开的位置
			*s++ = *t++;
		}
	}
	else{
		x = s+lens;//将指针指向串的末尾'\0'的位置
		while((lens-pos)>=0){//从被插入位置开始，将串s依次后移lent个位置
			*(x+lent) = *x;
			x--;
			lens--;
		}
		//将需要插入的串复制到原字符串空开的位置
		while(*t!='\0')
			*((x++)+1) = *(t++);
	}
}

int main(int argc,char *argv[])
{
	char *s,*t,ch;
	int i,j,pos;
	int max = maxsize/2;
	while(1){
	printf("\n\t请选择");
	printf("\n\n\t[a]建主串");
	printf("\n\t[b]求串长");
	printf("\n\t[c]串复制");
	printf("\n\t[d]串连接");
	printf("\n\t[e]求子串");
	printf("\n\t[f]比较串");
	printf("\n\t[g]串插入");
	printf("\n\t[h]串删除");
	printf("\n\t[i]串定位");
	printf("\n\t[j]退出\n");
	ch = getchar();
	switch(ch){
		case 'a':
			printf("\n请输入字符串(长度小于%d):",max);
			s = (char *)malloc(sizeof(char)*max);
			scanf("%s",s);
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n你输入的字符串为：%s\n",s);
			break;
		case 'b':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n你输入的字符串长度为：%d\n",str_len(s));
			break;
		case 'c':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			t = (char *)malloc(sizeof(char)*max);
			str_cpy(s,t);
			printf("\n复制后的字符串为：%s\n",t);
			break;
		case 'd':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入需连接的字符串(长度小于%d):",max);
			t = (char *)malloc(sizeof(char)*max);
			scanf("%s",t);
			setbuf(stdin, NULL);
			str_concat(s,t);
			printf("\n连接后的字符串为:%s\n",s);
			break;
		case 'e':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入子串的起始位置：");
			scanf("%d",&i);
			printf("\n请输入子串的长度：");
			scanf("%d",&j);
			setbuf(stdin, NULL);
			t = (char *)malloc(sizeof(char)*max);
			str_sub(s,t,i,j);
			printf("\n截取的字符子串为：%s\n",t);
			break;
		case 'f':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入被比较的字符串：");
			gets(t);
			i = str_cmp(s,t);
			switch(i){
				case 1:
					printf("\n字符串s > 字符串t\n");
					break;
				case -1:
					printf("\n字符串s < 字符串t\n");
					break;
				case 0:
					printf("\n字符串s = 字符串t\n");
					break;
			}
			break;
		case 'g':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入插入的子串：");
			t = (char *)malloc(sizeof(char)*max);
			scanf("%s",t);
			setbuf(stdin, NULL);
			printf("\n请输入插入的位置：");
			scanf("%d",&pos);
			setbuf(stdin, NULL);
			str_insert(s,t,pos);
			printf("\n插入子串后的字符串为：%s\n",s);
			break;
		case 'h':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入被删除子串的起始位置：");
			scanf("%d",&i);
			printf("\n请输入被删除子串的长度：");
			scanf("%d",&j);
			setbuf(stdin, NULL);
			str_del(s,i,j);
			printf("\n删除子串后的字符串为：%s\n",s);
			break;
		case 'i':
			scanf("%*[^\n]%*c");
			setbuf(stdin, NULL);
			printf("\n请输入被定位的字符串：");
			t = (char *)malloc(sizeof(char)*max);
			scanf("%s",t);
			setbuf(stdin, NULL);
			printf("\n请输入定位的起始位置：");
			scanf("%d",&pos);
			setbuf(stdin, NULL);
			printf("\n定位结果为为：%d",str_index(s,t,pos));
			break;
		case 'j':
			return 0;
	}
	}
}

*/
/****************************************
技巧12:链表法表示稀疏矩阵
****************************************/
/*
#include<stdio.h>
#include<stdlib.h>
#define MAX 10
typedef int datatype;

//稀疏矩阵的十字链表结构
typedef struct lmnode{
	int row,col;
	datatype e;
	struct lmnode *right,*down;
}lmnode;

lmnode *ROW[MAX],*COL[MAX];

typedef struct{
	int r,c,n;
	lmnode **rhead,**chead;
}CrossList;

//创建十字链表的函数
//CrossList * creat_olmatrix()
int main()
{
	int m,n,t,i,j,e;
	lmnode *p,*q;
	CrossList *matrix;
	if(!(matrix=(CrossList *)malloc(sizeof(CrossList))))
			return(NULL);
	printf("请依次输入稀疏矩阵的行数，列数和元素个数:");
	scanf("%d%d%d",&m,&n,&t);
	matrix->r = m;
	matrix->c = n;
	matrix->n = t;
	matrix->rhead = ROW;
	matrix->chead = COL;
	for(i=0;i<m;i++)
		matrix->rhead[i] = NULL;
	for(i=0;i<n;i++)
		matrix->chead[i] = NULL;
	printf("请依次输入稀疏矩阵的元素内容:");
	scanf("%d%d%d",&i,&j,&e);
	while(i>0){
		if(!(p=(lmnode *)malloc(sizeof(lmnode))))
				return(NULL);
		p->row = i;
		p->col = j;
		p->e = e;
		p->right =NULL;
		p->down =NULL;
		if(matrix->rhead[i-1] == NULL)
			matrix->rhead[i-1] = p;
		else{
			q=matrix->rhead[i-1];
			while(q->right&&q->right->col<(j-1))
				q=q->right;
			p->right = q->right;
			q->right = p;
		}
		if(matrix->chead[j-1] == NULL)
			matrix->chead[j-1] = p;
		else{
			for(q=matrix->chead[j-1];q->down&&q->down->row<(i-1);q=q->down);
			p->down = q->down;
			q->down = p;
		}
		printf("请依次输入稀疏矩阵的元素内容:");
		scanf("%d%d%d",&i,&j,&e);
	}
	printf("您输入的矩阵为:\n");
	for(i=0;i<(matrix->r);i++){
		for(j=0;j<(matrix->c);j++){
			if((matrix->rhead[i]!=NULL)&&(matrix->rhead[i]->col==(j+1)))
				printf("%3d",matrix->rhead[i]->e);
			else
				printf("  0");
		}
		printf("\n");
	}
	return(0);
}


*/
/****************************************
技巧13:数组法表示稀疏矩阵,及求和运算
****************************************/
//为了简化问题，在嵌入式系统中只定义三元组节点数据结构，放弃了定义三元组表结构体。
//该用三元组节点数组来表示稀疏矩阵，其中下标为0的节点的三个数据域分别用来标记稀疏矩阵
//的总行数，总列数和非零数据个数。
/*
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
struct node	//定义三元组节点结构体
{
	int row;	//行域
	int col;	//列域
	datatype data;	//数据域
}A[10],B[10],S[20];	//定义三元组数组

int m;			//稀疏矩阵的行数
int n;			//稀疏矩阵的列数

void display(struct node c[])	//打印稀疏矩阵的函数
{
	int i,j,k,d[20];
	if(c[0].data==0){	//检查矩阵中非零元素个数
		printf("非零元素个数为零！\n");
		return;
	}
	printf("\n三元组:\n\t行号\t列号\t数据\n\t_____________________\n");	//逐行显示非零元素
	for(i=1;i<=c[0].data;i++)
		printf("\t%2d\t%2d\t%2d\n",c[i].row,c[i].col,c[i].data);
	printf("\n矩阵形式:\n");			//矩阵形式显示
	for(i=1;i<=c[0].row;i++){			//逐行显示
		for(j=1;j<=c[0].col;j++)		//初始化辅助数组为0
			d[j]=0;
		for(k=1;k<=c[0].data;k++){		//逐个检查非零元素
			if(c[k].row==i)			//如果该行有非零元素
				d[c[k].col]=c[k].data;	//则把辅助数组的相应元素设为非零元素值
			if(c[k].row>i)
				break;
		}
		for(j=1;j<=c[0].col;j++)		//显示第i行的元素
			printf("%4d",d[j]);
		printf("\n");
	}
	getchar();					//显示完毕，等待用户输入
}


void init(struct node c[])					//稀疏矩阵的初始化
{
	int i=0;
	while(1){
		printf("\n\t请输入稀疏矩阵非零元素的个数:");
		scanf("%d",&c[0].data);
		if(c[0].data>2&&c[0].data<10)
			break;
		else
			printf("\n非零元素的个数范围:3---9!\n");
	}

	printf("\n\t请按行的顺序输入%d个稀疏矩阵非零元素!\n",c[0].data);
	for(i=1;i<=c[0].data;i++){
		printf("\t请输入第%d个稀疏矩阵非零元素:\n",i);
		while(1){
			printf("\n\t行号:");
			scanf("%d",&c[i].row);
			if(c[i].row>0&&c[i].row<=m)
				break;
			else
				printf("\n范围:1---%d!\n",m);
		}
		while(1){
			printf("\n\t列号:");
			scanf("%d",&c[i].col);
			if(c[i].col>0&&c[i].col<=n)
				break;
			else
				printf("\n范围:1---%d!\n",n);
		}
		printf("\n\t数据:");
		scanf("%d",&c[i].data);
		printf("\n");
	}
	display(c);
}

int main(int argc,char *argv[])
{
	int i,j,k,l;
	char ch;
	while(1){
		printf("\n\n请选择:\n\n(1)输入稀疏矩阵的大小\n");
		printf("\n(2)请输入稀疏矩阵A\n\n(3)请输入稀疏矩阵B\n");
		printf("\n(4)输出稀疏矩阵S\n\n(5)退出\n");
		ch=getchar();
		setbuf(stdin,NULL);
		switch(ch){
			case '1':
				while(1){
					printf("\n\t矩阵行数:");
					scanf("%d",&m);
					if(m>2&&m<9)
						break;
					else
						printf("\n矩阵行数范围:3--->8!\n");
				}
				while(1){
					printf("\n\t矩阵列数:");
					scanf("%d",&n);
					setbuf(stdin,NULL);
					if(n>2&&n<9)
						break;
					else
						printf("\n矩阵列数范围:3---9!\n");
				}
				A[0].col=B[0].col=S[0].col=n;//填入稀疏矩阵的行数
				A[0].row=B[0].row=S[0].row=m;//填入稀疏矩阵的列数
				break;
			case '2':
				init(A);			//输入稀疏矩阵A
				break;
			case '3':
				init(B);			//输入稀疏矩阵B
				break;
			case '4':
				i=j=k=1;					//三个三元组表的操作对象序列初始化
				while(i<=A[0].data||j<=B[0].data){		//只要A或B中还有非零元素
					if(i>A[0].data){			//A中元素已经处理完，直接将B赋给S
						S[k].row=B[j].row;		
						S[k].col=B[j].col;
						S[k].data=B[j].data;
						k++;				//调整S的序号
						j++;				//调整B的序号
					}
					else if(j>B[0].data){			//B中元素已经处理完，直接将A赋给S
						S[k].row=A[i].row;		
						S[k].col=A[i].col;
						S[k].data=A[i].data;
						k++;				//调整S的序号
						i++;				//调整A的序号
					}
					else if((((A[i].row*n)+A[i].col)<((B[j].row*n)+B[j].col))){	//A[i]行列优先,将A赋给S
						S[k].row=A[i].row;		
						S[k].col=A[i].col;
						S[k].data=A[i].data;
						k++;				//调整S的序号
						i++;				//调整A的序号
					}
					else if((((B[j].row*n)+B[j].col)<((A[i].row*n)+A[i].col))){	//B[i]行列优先,将B赋给S
							S[k].row=B[j].row;	
							S[k].col=B[j].col;
							S[k].data=B[j].data;
							k++;				//调整S的序号
							j++;				//调整B的序号
						}
					else{						//A,B行列相同，需要相加
						if((S[k].data=A[i].data+B[j].data)!=0){	//A,B相加
							S[k].row=A[i].row;
							S[k].col=A[i].col;
							k++;				//调整S的序号，使刚保存的数据有效
						}
						i++;
						j++;
					}
				}
				k--;							//运算结束，使序号回调到最后一个位置上
				S[0].data=k;
				display(A);
				display(B);
				display(S);
				break;
			case '5':
				return 0;
		}
	}
}
*/

