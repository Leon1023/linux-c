#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"
#define MAXSIZE 50
int priority(char ch)
{
    switch(ch){
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        default:
            perror("invalid operator.");
            return(9);
    }
}



Status IsNumber(char ch)
{
        return (ch>='0'&&ch<='9')?TRUE:FALSE;
}



Status IsOperator(char ch)
{
   return (ch=='+'||ch=='-'||ch=='*'||ch=='/')?TRUE:FALSE; 
}



Status InvalidExpr(char *mp)
{
    char *p;
    p = mp;
    while(*p!='\0'){
        if(IsNumber(*p)||IsOperator(*p)||*p=='('||*p==')')
            p++;
        else
            return TRUE;
    }
    return FALSE;
}


Status MidToEnd(char * mid_expr, char *end_expr)
{
    char *mp,*ep;
    AStack *stkp;
    stkp = InitStack();
    mp = mid_expr;
    ep = end_expr;
//    if(InvalidExpr(mp)){
  //      perror("Leon:invalid express!");
    //    return ERROR;
 //   }
    while(*mp!='\0'){
        if(IsNumber(*mp))
            *ep++ = *mp;
        else if(IsOperator(*mp)){
            if(priority(stkp->data[stkp->top])<priority(*mp))
                Push(stkp,*mp);
            else
                while(priority(stkp->data[stkp->top])>=priority(*mp))
                    Pop(stkp,ep++);
            }
        else if(*mp==')'){
            while((stkp->data[stkp->top])!='(')
                Pop(stkp,ep++);
            stkp->top--;
        }
        else if(*mp=='(')
            Push(stkp,*mp);
        else
            return ERROR;
        mp++;
    }
    return OK;
}




int main(void)
{
    char mid_express[MAXSIZE]={'1','+','2','-','3','\0'};
    char end_express[MAXSIZE]={'\0'};
 //   puts("Enter express");
//    scanf("%s",mid_express);
    MidToEnd(mid_express,end_express);    
    puts(mid_express);
    puts(end_express);
    return 0;
}
