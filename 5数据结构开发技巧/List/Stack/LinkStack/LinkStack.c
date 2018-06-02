#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

/*----------------------------------*/
Status LSInit(LStackPtr LSP)
{
    if(LSP == NULL){
        perror("invalid stack ptr");
        return ERROR;
    }
    LSP->top = NULL;
    LSP->count = 0;
    return OK;
}


/*----------------------------------*/
int LSLength(LStackPtr sp)
{
    return sp->count;
}


/*----------------------------------*/
Status LSDisplay(LStackPtr sp)
{
    LStackPtr lsp;
    NodePtr nd = NULL;
    lsp = sp;
    if(lsp == NULL){
        perror("invalid stack ptr!");
        return ERROR;
    }
    printf("\nThe stack are: ");
    nd = lsp->top;
    while(nd != NULL){
        printf("%d<--",nd->data);
        nd = nd->next;
    }
    return OK;
}


/*----------------------------------*/
Status Push(LStackPtr sp, SElemType elem)
{
    NodePtr s;
    if(sp==NULL){
        perror("invalid stack ptr ");
        return ERROR;
    }
    if(!(s=(NodePtr)malloc(sizeof(Node)))){
        perror("malloc false. ");
        return ERROR;
    }
    s->data = elem;
    s->next = sp->top;
    sp->top = s;
    sp->count++;
    return OK;
}


/*----------------------------------*/
Status Pop(LStackPtr sp, SElemType *ElemPtr)
{
    NodePtr p;
    if(sp==NULL){
        perror("invalid stack ptr ");
        return ERROR;
    }
    if(LSLength(sp)==0){
        perror(" stack is empty. ");
        return ERROR;
    }
    *ElemPtr = sp->top->data;
    p = sp->top;
    sp->top = p->next;
    free(p);
    sp->count--;
    return OK;
}


/*----------------------------------*/
Status LSDestroy(LStackPtr sp)
{
    NodePtr np,dp;
    LStackPtr lsp;
    lsp = sp;
    np =NULL;
    if(lsp == NULL){
        perror("invalid stack ptr!");
        return ERROR;
    }
    np = lsp->top;
    while(np != NULL){
        dp = np->next;
        free(np);
        np = dp;
    }
    free(lsp);
    return OK;
}
