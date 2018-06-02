#include <stdio.h>
#include <stdlib.h>
#include "DoubleStack.h"

/*----------------------------------*/
/*初始化,建立一个空栈*/
DStack * InitStack(void){
    DStack *sp;
    if(!(sp = (DStack *)malloc(sizeof(DStack)))){
        perror("malloc  stack false.");
        return NULL;
    }
    sp->top1 = -1;
    sp->top2 = STACKSIZE;
    return sp;
}



/*----------------------------------*/
/*由栈底到栈顶显示栈的元素*/    
 Status StackDisplay(DStack *sp)
{
    int i=0,top1,top2;
    top1 = sp->top1;
    top2 = sp->top2;
    if(!sp){
        perror("invalid stack ptr.\n");
        return ERROR;
    }

    if(StackEmpty(sp)){
        printf("Stack is empty.\n");
    }
    else{
        while(0<=i&&i<=top1){
            printf("->|%d|",sp->data[i]);
            i++;
            }
        while(top1<i&&i<top2){
            printf("->| |");
            i++;
            }
        while(i>=top2&&i<STACKSIZE){
            printf("|%d|<-",sp->data[i]);
            i++;
            }
    }
    puts("\n");
    return OK;
}


/*----------------------------------*/
/*若栈存在,则销毁它。*/
Status DestroyStack(DStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
   free(sp);
   return OK;
}


/*将栈清空。*/
Status ClearStack(DStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    sp->top1 = -1;
    sp->top2 = STACKSIZE;
    return OK;
}


/*若栈为空,返回TRUE,否则返回FALSE.*/
Status StackEmpty(DStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    return ((sp->top1 == -1)&&(sp->top2 == STACKSIZE))?TRUE:FALSE;
}


/*若栈存在且非空,用e返回S的栈顶元素*/
Status GetTop(DStack *sp, int stacknum, SElemType *TopElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    if (stacknum == 1){
        if(sp->top1 == -1){
            perror("Stack 1 is empty.");
            return ERROR;
        }
        *TopElem = sp->data[sp->top1];
    }
    else if(stacknum == 2){
        if(sp->top2 == STACKSIZE){
            perror("Stack 2 is empty.");
            return ERROR;
        }
        *TopElem = sp->data[sp->top2];
    }
    else{
        perror("wrong stack num!");
        return ERROR;
    }
    return OK;
}


/*若栈S存在,插入新元素e到栈S中并成为栈顶元素。*/
Status Push(DStack *sp, int stacknum, SElemType PushElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    if(sp->top1+1 == sp->top2){
        perror("Stack is full.");
        return ERROR;
    }
    if(stacknum==1){
        (sp->top1)++;
        sp->data[sp->top1] = PushElem;
    }
    else if(stacknum==2){
        (sp->top2)--;
        sp->data[sp->top2] = PushElem;
    }
    else{
        perror("wrong stack num.");
        return ERROR;
    }
    return OK;
}


/*弹出栈S中栈顶元素,并用e返回其值。*/
Status Pop(DStack *sp, int stacknum, SElemType *PopElem)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
   if(StackEmpty(sp)){
        perror("Stack is empty.");
        return ERROR;
    }
    if((stacknum==1)&&(sp->top1!=-1)){
        *PopElem = sp->data[sp->top1];
        (sp->top1)--;
    }
    else if((stacknum==2)&&(sp->top2!=STACKSIZE)){
        *PopElem = sp->data[sp->top2];
        (sp->top2)++;
    }
    else{
        perror("the stack you poped is empty.");
        return ERROR;
    }
    return OK;
}



/*返回栈S的元素个数*/
int StackLength(DStack *sp)
{
    if(!sp){
        perror("invalid stack ptr.");
        return ERROR;
    }
    return (sp->top1+1)+(STACKSIZE-sp->top2);
}
