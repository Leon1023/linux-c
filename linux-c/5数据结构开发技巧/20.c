/* >>>>> index <<<<<
技巧11：从链表中删除节点
技巧12：合并两个链表
技巧13：顺序栈(数组存储形式)
技巧14: 链栈(链表存储形式)
技巧15：应用栈实现进制转换
技巧16: 循环队列(FIFO)
技巧17: 链表队列(FIFO)
*/
/****************************************
技巧11：从链表中删除节点
****************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define DataType int
typedef struct student
{
  int num;
  struct student *next;
}LNode,*LinkList;

LinkList create(int n)
{
  int i;
  DataType x;
  LinkList head,p1,p2;
  head=NULL;
  printf ("the record:\n");
  for (i=n; i>0; --i)
    {
      p1=(LinkList)malloc(sizeof(LNode));
      scanf("%d",&x);
      p1->num=x;
      if (head==NULL)
	{
	  head=p1;
	  p2=p1;
	}
      else
	{
	  p2->next=p1;
	  p2=p1;
	}
    }
  p2->next=NULL;
  return head;
};
struct student *delnode(struct student *head,int i)
{
  int j=0;
  struct student *p,*r;
  p=head;
  while(p&&j<i-1)           //找到要删除的位置
    {
      p=p->next;
      ++j;
    }
  if(!p->next||j>i-1)
    exit(1);
  r=p->next;
  p->next=r->next;           //删除节点
  free(r);
};
main()
{
  int i;
  DataType n;
  LinkList q;
  printf ("input the count of the nodes you want to creat:\n");
  scanf("%d",&n);
  q = create(n);
  i = 2;
  DelNode(q,i);
  printf ("the third record is deleted!\nthe result is:\n");
  while(q)
    {
      printf ("%d ",q->num);
      q=q->next;
    }
  return 0;
}
*/
/****************************************
技巧12：合并两个链表
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
typedef struct student
{
  int num;
  struct student *next;
}LNode,*LinkList;
LinkList create(void)
{
  LinkList head;
  LNode *p1,*p2;
  char a;
  head=NULL;
  a=getchar();
  while(a!='\n')
    {
      p1=(LNode*)malloc(sizeof(LNode));
      p1->num=a;
      if(head==NULL)
	head=p1;
      else
	p2->next=p1;
      p2=p1;
      a=getchar();
    }
  p2->next=NULL;
  return head;
}
LinkList coalition(LinkList L1,LinkList L2)
{
  LNode *temp;
  if(L1==NULL)
    return L2;
  else
    {
      if (L2 !=NULL)
	{
	  for(temp=L1;temp->next != NULL;temp=temp->next);
	  temp->next=L2;
	}
    }
  return L1;
}
int main(int argc, char *argv[])
{
  LinkList L1,L2,L3;
  printf ("please input two linklist:\n");
  printf ("the first linklist:\n");
  L1=create();
  printf ("the second linklist:\n");
  L2=create();
  coalition(L1,L2);
  printf ("the resultant linklist is:\n");
  while(L1)
    {
      printf ("%c",L1->num);
      L1=L1->next;
    }
  return 0;
}
*/

/****************************************
技巧13：顺序栈数(组存储形式)
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define STACKSIZE 64
#define DataType int
typedef struct {
	DataType data[STACKSIZE];
	int top;
}sqstack;

//创建顺序栈(初始化）
int Initial(sqstack *s)
{
	s->top = -1;
	return 0;
}

//判栈空
int is_empty(sqstack *s)
{
	if(s->top < 0)
		return 1;
	else
		return 0;
}

//判满栈
int is_full(sqstack *s)
{
	if(s->top == STACKSIZE-1)
		return 1;
	else 
		return 0;
}

//取栈顶元素
int get_top(sqstack *s)
{
	if(is_empty(s)){
		printf("栈空！\n");
		return(NULL);
	}
	else
		return(s->data[s->top]);
}

//入栈,成功返回1，失败返回0
int push(sqstack *s,DataType x)
{
	if(is_full(s)){
		printf("栈满！\n");
		return 1;
	}
	else{
		(s->top)++;
		s->data[(s->top)] = x;
		return 0;
	}
}

//出栈，成功返回0，失败返回1
DataType pop(sqstack *s,DataType *xptr)
{
	if(is_empty(s)){
		printf("栈空！\n");
		*xptr = NULL; 
		return 1;
	}
	else{
		*xptr =(s->data[(s->top)--]); 
		return 0;
	}
}

int main(int argc,char *argv[])
{
	int i;
	DataType x,xp;
	char c;
	sqstack *s;
	s = (sqstack *)malloc(sizeof(sqstack));
	while(1)
	{
		printf("\n\n\t请选择\t");
		printf("\n\tA:建顺序队列\t");
		printf("\n\tB:取顺序队列节点\t");
		printf("\n\tC:入队\t");
		printf("\n\tD:出队\t");
		printf("\n\tE:结束\t\n");
		c = getchar();
		switch(c){
			case 'A':
			case 'a':
				scanf("%*[^\n]%*c");//该句与下句合用可清除键盘输入缓冲区！
				setbuf(stdin, NULL);
			       if(! Initial(s))
					printf("\n队列初始化完毕!\n");
			       else{
				       perror("initial sqstack failed!\n");
				       exit(1);
			       }
				break;
			case 'B':
			case 'b':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if(get_top(s))
					printf("取出的元素为:%d\n",get_top(s));
				break;
			case 'C':
			case 'c':
				printf("\n请输入入队的数据:");
				scanf("%d",&x);
				setbuf(stdin, NULL);
				push(s,x);
				printf("\n当前队列的数据为:");
				i = s->top;
				while(i > -1){
					printf("\n\t%5d",s->data[i--]);
				}
				break;
			case 'D':
			case 'd':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if(!pop(s,&xp)){
				printf("\n出队元素为:%d",xp);
				printf("\n当前循环队列的数据为:");
				i = s->top;
				while(i>-1)
					printf("\n\t%5d",s->data[i--]);
				}
				break;
			case 'E':
			case 'e':
				return 0;
		}
	}
}
*/

/****************************************
技巧14: 链栈(链表存储形式)
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define DataType int
typedef struct link_stack{
	DataType data;
	struct link_stack *next;
}link_stack;

//置空链栈
link_stack * reset(link_stack *top)
{
	link_stack *ls;
	while(top != NULL){
		ls = top;
		top = top->next;
		free(ls);
	}
	return(top);
}

//判栈空
int is_empty(link_stack *top)
{
	if(top == NULL)
		return 1;
	else
		return 0;
}

//取栈顶元素
int get_top(link_stack *top)
{
	if(is_empty(top)){
		printf("栈空！\n");
		return(NULL);
	}
	else
		return(top->data);
}

//入栈,成功返回新的top地址，失败返回NULL
link_stack * push(link_stack *top,DataType x)
{
	link_stack *new;
	new = (link_stack *)malloc(sizeof(link_stack));
	new->data = x;
	new->next = top;
	return(new);
}

//出栈，成功返回1，失败返回NULL
link_stack * pop(link_stack *top,DataType *xp)
{
	if(is_empty(top)){
		printf("栈空！\n");
		return(NULL);
	}
	else{
		*xp =top->data;
		return(top->next);
	}
}

int main(int argc,char *argv[])
{
	DataType x;
	char c;
	link_stack *top=NULL,*s;
	while(1)
	{
		printf("\n\n\t请选择\t");
		printf("\n\tA:建链队列\t");
		printf("\n\tB:取链队列节点\t");
		printf("\n\tC:入队\t");
		printf("\n\tD:出队\t");
		printf("\n\tE:结束\t\n");
		c = getchar();
		switch(c){
			case 'A':
			case 'a':
				scanf("%*[^\n]%*c");//该句与下句合用可清除键盘输入缓冲区！
				setbuf(stdin, NULL);
			       if(!(top=reset(top)))
					printf("\n队列初始化完毕!\n");
			       else{
				       perror("reset link_stack failed!\n");
			       }
				break;
			case 'B':
			case 'b':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if(get_top(top))
					printf("取出的元素为:%d\n",get_top(top));
				break;
			case 'C':
			case 'c':
				printf("\n请输入入队的数据:");
				scanf("%d",&x);
				setbuf(stdin, NULL);
				if((top=push(top,x))!=NULL){
					printf("\n当前队列的数据为:");
					s = top;
					while(s != NULL){
						printf("\n\t%5d",s->data);
						s = s->next;
					}
				}
				break;
			case 'D':
			case 'd':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if((top=pop(top,&x))){
					printf("\n出队元素为:%d",x);
					printf("\n当前循环队列的数据为:");
					s = top;
					while(s != NULL){
						printf("\n\t%5d",s->data);
						s = s->next;
					}
				}
				break;
			case 'E':
			case 'e':
				return 0;
		}
	}
}
*/	

/****************************************
技巧15：应用栈实现进制转换
****************************************/
/*
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define STACKSIZE 64
typedef struct {
  DataType *base;
  DataType *top;
  int stacksize;
}SeqStack;

void Initial(SeqStack *s)
{
  //构造一个空栈
  s->base=(DataType *)malloc(STACKSIZE *sizeof(DataType));
  if(!s->base)
    exit(-1);
  s->top=s->base;
  s->stacksize=STACKSIZE;
}
//判栈空
int IsEmpty(SeqStack *s)
{
  return s->top==s->base;
}
//判栈满
int IsFull(SeqStack *s)
{
  return s->top - s->base==stacksize-1;
}
//进栈
void Push(SeqStack *s,DataType x)
{
  if (IsFull(s))
    {
      printf ("栈上溢\n"); //上溢，退出运行
      exit(1);
    }
  *++(s->top) = x;    //栈顶指针加1后将x入栈
}
//出栈
DataType Pop(SeqStack *s)
{
  if (IsEmpty(s))
    {
      printf ("栈为空\n");  //下溢，退出运行
      exit(1);
    }
  return *(s->top--); //栈顶元素返回后将栈顶指针减1
}
//取栈顶元素
DataType Top(SeqStack *s)
{
  if (IsEmpty(s))
    {
      printf ("栈为空\n");   //下溢，退出运行
      exit(1);
    }
  return *(s->top);
}
void conversion(int N,int B)
{          //假设N是非负的十进制整数，输出等值的B进制数
  int i;
  SeqStack *S;
  Initial(S);
  while(N)
    {      //从右向左产生B进制的各位数字，并将其进栈
      Push(S,N%B);     //将bi进栈0<=i<=j
      N=N/B;
    }
  while(!IsEmpty(S))
    {
      i=Pop(S);        //栈非空时退栈输出
      printf ("%d\n",i);
    }
}
void main(int argc,char * argv[])
{
  int n,d;
  printf ("Input the integer you want to transform:\n");
  scanf("%d",&n);
  printf ("Input the integer of the system:\n");
  scanf("%d",&d);
  printf ("result:\n");
  conversion(n,d);
}
*/
/****************************************
技巧16:创建循环队列FIFO
****************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#define maxsize 50
#define TRUE 1
#define FAILE 0

typedef int DataType;
typedef struct {
	DataType data[maxsize];//为了有效判别空或满队
	int front;		//头指针指向的空间不用于存数据
	int rear;
}sequeue;

void reset(sequeue *sq)
{//将头尾指针都指向数组第一个空间，且此时该空间不存储数据
	sq->front = 0;
	sq->rear = 0;
}
//当头尾指针相等时，队列为空
//当"(rear+1)%maxsize == front"时，队列为满
int is_empty(sequeue *sq)//队列为空时返回1，不为空时返回0
{
	if(sq->rear == sq->front)
		return 1;
	else
		return 0;
}

int is_full(sequeue *sq)//队列为满时返回1，不为满时返回0
{
	if(((sq->rear)+1)%maxsize == sq->front)//循环队列
		return 1;
	else
		return 0;
}

//获得循环队列的头节点，同时队列保持不变
DataType get_front(sequeue *sq,DataType *xp)
{
	if(is_empty(sq)){
		printf("sequeue is NULL!\n");
		return(NULL);
	}
	else
		*xp = sq->data[((sq->front)+1)%maxsize];
		return 1;
}

//入队
DataType in_sequeue(sequeue *sq,DataType x) //将x插入到循环队列中
{
	if(is_full(sq)){
		printf("sequeue is full\n");
		return(NULL); //队列已满，返回
	}
	else{
		sq->rear = ((sq->rear)+1)%maxsize;//队尾指针加1
		sq->data[sq->rear] = x;//将x插入到队尾
		return 1;//入队成功，函数返回0
	}
}

//出队
DataType out_sequeue(sequeue *sq,DataType *xp) //函数返回队顶元素
{
	if(is_empty(sq)){
		printf("sequeue is null\n");
		return(NULL); //队列已空，返回NULL
	}
	else{
		sq->front = ((sq->front)+1)%maxsize;//队首指针加1
		*xp = sq->data[sq->front];//出队成功，将出队元素传给xp所指地址内
		return 1;//出队成功，函数返回1
	}
}

int main(int argc,char *argv[])
{
	DataType xp;
	int i;
	char c;
	sequeue *q;
	q = (sequeue *)malloc(sizeof(sequeue));
	while(TRUE)
	{
		printf("\n\n\t请选择\t");
		printf("\n\tA:建字符队列\t");
		printf("\n\tB:取队列节点\t");
		printf("\n\tC:入队\t");
		printf("\n\tD:出队\t");
		printf("\n\tE:结束\t\n");
		c = getchar();
			case 'a':
				scanf("%*[^\n]%*c");//清除键盘缓冲
				setbuf(stdin, NULL);//清除键盘缓冲
			        reset(q);
				printf("\n循环队列初始化完毕!\n");
				break;
			case 'B':
			case 'b':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if(get_front(q,&xp))
					printf("取出的元素为:%d\n",xp);
				break;
			case 'C':
			case 'c':
				printf("\n请输入入队的数据:");
				scanf("%d",&xp);
				setbuf(stdin, NULL);
				if(in_sequeue(q,xp)){
					printf("\n当前循环队列的数据为:");
					i = q->front;
					while(i!=q->rear){
						i = (i+1)%maxsize;
						printf("%5d",q->data[i]);
					}
				}
				break;
			case 'D':
			case 'd':
				scanf("%*[^\n]%*c");
				setbuf(stdin, NULL);
				if(out_sequeue(q,&xp)){
					printf("\n出队元素为:%d",xp);
					printf("\n当前循环队列的数据为:");
					i = q->front;
					while(i!=q->rear){
						i = (i+1)%maxsize;
						printf("%5d",q->data[i]);
					}
				}
				break;
			case 'E':
			case 'e':
				return 0;
		}
	}
}
*/
/****************************************
技巧17:创建链表队列FIFO
****************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FAILE 0

typedef int DataType;
typedef struct link_queue_node{
	DataType data;
	struct link_queue_node *next;
}link_queue_node;

typedef struct {
	link_queue_node *front;
	link_queue_node *rear;
}link_queue;

//初始化一个链表队列
void reset_link_queue(link_queue *lq)
{
	lq->front = (link_queue_node *)malloc(sizeof(link_queue_node));//分配头结点空间
	lq->front->next = NULL;//头节点指针域置空
	lq->rear = lq->front;//尾指针指向头节点
}

//当头尾指针相等时，队列为空
int is_empty(link_queue *lq)
{
	if(lq->front == lq->rear)
		return 1;//队列为空时返回1
	else
		return 0;//不为空时返回0
}


//获得循环队列的头节点，同时队列保持不变
DataType get_front(link_queue *lq,DataType *xp)
{
	if(is_empty(lq)){
		printf("link queue is NULL!\n");
		return(NULL);
	}
	else
		*xp = lq->front->next->data;
		return 1;
}

//入队
DataType in_link_queue(link_queue *lq,DataType x) //将x插入到队尾
{
	lq->rear->next = (link_queue_node *)malloc(sizeof(link_queue_node));//分配空间给新节点，并插到队尾
	lq->rear = lq->rear->next;//尾指针指向新插入节点
	lq->rear->data = x;//给新节点数据域赋值
	lq->rear->next = NULL;//新节点指针域赋值
	return 0;//入队成功，函数返回0
}

//出队
DataType out_link_queue(link_queue *lq,DataType *xp) //函数返回队顶元素
{
	link_queue_node *s;
	if(is_empty(lq)){
		printf("the link queue is empty!");//队空，函数返回0
		return(NULL);
	}
	s = lq->front;//头结点赋给s
	lq->front = s->next;//头结点指向原队头节点
	free(s);//释放原头结点
	*xp = lq->front->data;//出队成功，函数返回原队头节点的数据域
	return 1;
	
}

int main(int argc,char *argv[])
{
	DataType x;
	char c;
	link_queue_node *s;
	link_queue *lq;
	lq = (link_queue *)malloc(sizeof(link_queue));
	while(TRUE)
	{
		printf("\n\n\t请选择\t");
		printf("\n\tA:建字符队列\t");
		printf("\n\tB:取队列节点\t");
		printf("\n\tC:入队\t");
		printf("\n\tD:出队\t");
		printf("\n\tE:结束\t\n");
		c = getchar();
		switch(c){
			case 'A':
			case 'a':
				scanf("%*[^\n]%*c");
				setbuf(stdin,NULL);
			        reset_link_queue(lq);
				printf("\n循环队列初始化完毕!\n");
				break;
			case 'B':
			case 'b':
				scanf("%*[^\n]%*c");
				setbuf(stdin,NULL);
				if(get_front(lq,&x))
					printf("取出的元素为:%d\n",x);
				break;
			case 'C':
			case 'c':
				printf("\n请输入入队的数据:");
				scanf("%d",&x);
				setbuf(stdin, NULL);
				if(!in_link_queue(lq,x)){
					printf("\n当前链表队列的数据为:");
					s = lq->front->next;
					while(s!=NULL){
						printf("%5d",s->data);
						s = s->next;
					}
				}
				break;
			case 'D':
			case 'd':
				scanf("%*[^\n]%*c");
				setbuf(stdin,NULL);
				if(out_link_queue(lq,&x)){
					printf("\n出队元素为:%d",x);
					printf("\n当前循环队列的数据为:");
					s = lq->front->next;
					while(s!=NULL){
						printf("%5d",s->data);
						s = s->next;
					}
				}
				break;
			case 'E':
			case 'e':
				return 0;
		}
	}
}
*/
