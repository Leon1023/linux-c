#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"

/*----------------------------------*/
/*初始化,建立一个空栈*/
AStack * InitStack(void){
    AStack *sp;
    if(!(sp = (AStack *)malloc(sizeof(AStack)))){
        perror("malloc  stack false.");
        return NULL;
    }
    sp->top = -1;
    return sp;
}



/*----------------------------------*/
/*由栈底到栈顶显示栈的元素*/    
 Status StackDisplay(AStack *sp)
{
    int i=0,astop;
    astop = sp->top;
    if(!sp){
        perror("invalid stack ptr.\n");
        return ERROR;
    }
    if(sp->top == -1){
        printf("Stack is empty.\n");
    }
    else{
        while(i<=astop){
            printf("->|%d|",sp->data[i]);
            i++;
        }
    }
    return OK;
}


/*----------------------------------*/
/*若栈存在,则销毁它。*/
Status DestroyStack(AStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
   free(sp);
   return OK;
}


/*将栈清空。*/
Status ClearStack(AStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    sp->top = -1;
    return OK;
}


/*若栈为空,返回TRUE,否则返回FALSE.*/
Status StackEmpty(AStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    return sp->top == -1?TRUE:FALSE;
}


/*若栈存在且非空,用e返回S的栈顶元素*/
Status GetTop(AStack *sp, SElemType *TopElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    if(sp->top == -1){
        perror("Stack is empty.");
        return ERROR;
    }
    *TopElem = sp->data[sp->top];
    return OK;
}


/*若栈S存在,插入新元素e到栈S中并成为栈顶元素。*/
Status Push(AStack *sp, SElemType PushElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    if(sp->top == STACKSIZE-1){
        perror("Stack is full.");
        return ERROR;
    }
    (sp->top)++;
    sp->data[sp->top] = PushElem;
    return OK;
}



/*弹出栈S中栈顶元素,并用e返回其值。*/
Status Pop(AStack *sp, SElemType *PopElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    if(sp->top == -1){
        perror("Stack is empty.");
        return ERROR;
    }
    *PopElem = sp->data[sp->top];
    sp->top--;
    return OK;
}



/*返回栈S的元素个数*/
int StackLength(AStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    return sp->top+1;
}
