#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkList.h"

NodePtr CreatNode(void)
{
    return((NodePtr)malloc(sizeof(Node)));
}

/*----------------------------------*/
Status SLLInit(NodePtr L)
{
    NodePtr LLP;
    LLP = L;
    if(LLP != NULL){
        LLP->next = NULL;
        LLP->data = 0;
        return OK;
    }
    else
        return ERROR;
}


/*----------------------------------*/
int SLLLength(NodePtr L)
{
    NodePtr LLP=L;
    int length=0;
    if(LLP == NULL){
        perror("It is a invalid ptr!");
        return ERROR;
    }
    LLP = LLP->next;
    while(LLP != NULL){
        length++;
        LLP=LLP->next;
    }
    return length;
}


/*----------------------------------*/
Status SLLDisplay(NodePtr L)
{
    NodePtr LLP;
    LLP = L;
    if(LLP == NULL){
        perror("invalid listptr!");
        return ERROR;
    }
    LLP = LLP->next;
    printf("\nThe link list are: ");
    while(LLP != NULL){
        printf("%d-->",LLP->data);
        LLP = LLP->next;
    }
    return OK;
}


/*----------------------------------*/
Status SLLInsert(NodePtr L, int location, LElemType elem)
{
    int i,j,k;
    NodePtr LLP,S;
    LLP = L;
    i = location;
    j = SLLLength(LLP);
    if(i<1 || i>j+1){
        perror("Wrong insert location! ");
        return ERROR;
    }
    for(k=1;k<i;k++)
        LLP=LLP->next;
    if(!LLP){
        perror("something wrong!");
        return ERROR;
    }
    if(!(S=CreatNode())){
        perror("malloc node failed!");
        return ERROR;
    }
    S->data = elem;
    S->next = LLP->next;
    LLP->next = S;
    return OK;
}


/*----------------------------------*/
Status NodeDelete(NodePtr L, int location)
{
    int i,j,k;
    NodePtr LLP,D;
    LLP = L;
    i = location;
    j = SLLLength(LLP);
    if(i<1 || i>j){
        perror("Wrong deleting location! ");
        return ERROR;
    }
    if(!LLP){
        perror("Invalid listptr! ");
    }
    for(k=1;k<i;k++){
        LLP = LLP->next;
    }
    if(!LLP){
        perror("Something Wrong! ");
    }
    D = LLP->next;
    LLP->next = D->next;
    free(D);
    return OK;
}


/*----------------------------------*/
Status SLLDestroy(NodePtr L)
{
    NodePtr LLP,NDP;
    int i;
    LLP = L;
    if(!LLP){
        perror("invalid list!");
    }
    LLP = LLP->next;
    while(LLP){
        NDP = LLP->next;
        free(LLP);
        LLP = NDP;
    }
    L->next = NULL;
    return OK;
}
