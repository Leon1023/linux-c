#define STACKSIZE 10
#define  ERROR 1
#define  OK 0
#define  TRUE 1
#define  FALSE 0
typedef  char SElemType;
typedef int Status;
typedef struct AStack{
    SElemType data[STACKSIZE];
    int top;
}AStack;

/*初始化操作,建立一个空栈。*/
AStack * InitStack(void);

/*由栈底到栈顶显示栈的元素*/    
Status StackDisplay(AStack *);

/*若栈存在,则销毁它。*/
Status DestroyStack(AStack *);

/*将栈清空。*/
Status ClearStack(AStack *);

/*若栈为空,返回TRUE,否则返回FALSE.*/
Status StackEmpty(AStack *);

/*若栈存在且非空,用e返回S的栈顶元素*/
Status GetTop(AStack *, SElemType*);

/*若栈S存在,插入新元素e到栈S中并成为栈顶元素。*/
Status Push(AStack *, SElemType);

/*弹出栈S中栈顶元素,并用e返回其值。*/
Status Pop(AStack *, SElemType *);

/*返回栈S的元素个数*/
int StackLength(AStack *);
