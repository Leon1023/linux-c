#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

NodePtr CreatNode(void)
{
    return((NodePtr)malloc(sizeof(Node)));
}

/*----------------------------------*/
Status DLLInit(DLListPtr DLLP)
{
    NodePtr NP;
    if(!(NP = CreatNode()))
        return ERROR;
    NP->data = 0;
    NP->prior = NP;
    NP->next = NP;
    if(DLLP != NULL){
        DLLP->head = NP;
        DLLP->rear = NP;
    }
    return OK;
}


/*----------------------------------*/
int DLLLength(DLListPtr DLLP)
{
    NodePtr NP = NULL;
    int length=0;
    if(!DLLP){
        perror("It is a invalid ptr!");
        return ERROR;
    }
    if(DLLP->head == DLLP->rear)
        return 0;
    NP = DLLP->head->next;
    while(NP != DLLP->rear){
        length++;
        NP=NP->next;
    }
    length++;
    return length;
}

/*----------------------------------*/
Status DLLDisplay(DLListPtr DLLP)
{
    DLListPtr LLP;
    NodePtr NP;
    LLP = DLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    if(LLP->head == LLP->rear){
        perror("It is a empty linklist");
        return ERROR;
    }
    NP = LLP->head->next;
    printf("\nThe forward link list are: ");
    while(NP != LLP->head){
        printf("%d-->",NP->data);
        NP = NP->next;
    }

    NP = LLP->rear;
    printf("\nThe backward link list are: ");
    while(NP != LLP->head){
        printf("%d-->",NP->data);
        NP = NP->prior;
    }
    return OK;
}


/*----------------------------------*/
Status DLLInsert(DLListPtr DLLP, int location, LElemType elem)
{
    int i,j,k;
    NodePtr NP,S;
    DLListPtr LLP;
    LLP = DLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    NP = LLP->head;
    i = location;
    j = DLLLength(LLP);
    if(i<1 || i>j+1){
        perror("Wrong insert location! ");
        return ERROR;
    }
    for(k=1;k<i;k++)
        NP=NP->next;
    if(!NP){
        perror("something wrong!");
        return ERROR;
    }
    if(!(S=CreatNode())){
        perror("malloc node failed!");
        return ERROR;
    }
    S->data = elem;
    S->next = NP->next;
    S->prior = NP;
    NP->next->prior = S;
    NP->next = S;
    if(i == j+1)
        LLP->rear = S;
    return OK;
}


/*----------------------------------*/
Status NodeDelete(DLListPtr DLLP, int location)
{
    int i,j,k;
    DLListPtr LLP;
    NodePtr NP,D;
    LLP = DLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    NP = LLP->head;
    i = location;
    j = DLLLength(LLP);
    if(i<1 || i>j){
        perror("Wrong deleting location! ");
        return ERROR;
    }
    for(k=1;k<i;k++){
        NP = NP->next;
    }
    if(!LLP){
        perror("Something Wrong! ");
        return ERROR;
    }
    D = NP->next;
    NP->next = D->next;
    D->next->prior = NP;
    if(i==j)
        LLP->rear = NP;
    free(D);
    return OK;
}


/*----------------------------------*/
Status DLLDestroy(DLListPtr DLLP)
{
    int i;
    DLListPtr LLP;
    NodePtr NP,NDP;
    LLP = DLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    NP = LLP->head;
    if(LLP->rear == NP)
        free(NP);
    NP = NP->next;
    while(NP!=LLP->head){
        NDP = NP->next;
        free(NP);
        NP = NDP;
    }
    free(LLP->head);
    return OK;
}


/*----------------------------------*/
DLListPtr DLLUnion(DLListPtr DLLPA,DLListPtr DLLPB)
{
    NodePtr NP;
    NP = DLLPA->rear->next;
    DLLPA->rear->next = DLLPB->head->next;
    DLLPB->head->next->prior = DLLPA->rear;
    DLLPA->rear = DLLPB->rear;
    free(DLLPB->head);
    return DLLPA;
}
