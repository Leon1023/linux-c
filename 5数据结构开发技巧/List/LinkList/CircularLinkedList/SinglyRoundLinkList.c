#include <stdio.h>
#include <stdlib.h>
#include "SinglyRoundLinkList.h"

NodePtr CreatNode(void)
{
    return((NodePtr)malloc(sizeof(Node)));
}

/*----------------------------------*/
Status SRLLInit(SRLListPtr SRLLP)
{
    NodePtr LLP;
    if(!(LLP = CreatNode()))
        return ERROR;
    LLP->data = 0;
    LLP->next = LLP;
    if(SRLLP != NULL){
        SRLLP->head = LLP;
        SRLLP->rear = LLP;
    }
    return OK;
}


/*----------------------------------*/
int SRLLLength(SRLListPtr SRLLP)
{
    NodePtr LLP = NULL;
    int length=0;
    if(!SRLLP){
        perror("It is a invalid ptr!");
        return ERROR;
    }
    if(SRLLP->head == SRLLP->rear)
        return 0;
    LLP = SRLLP->head->next;
    while(LLP != SRLLP->rear){
        length++;
        LLP=LLP->next;
    }
    length++;
    return length;
}

/*----------------------------------*/
Status SRLLDisplay(SRLListPtr SRLLP)
{
    SRLListPtr LLP;
    NodePtr NP;
    LLP = SRLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    if(LLP->head == LLP->rear){
        perror("It is a empty linklist");
        return ERROR;
    }
    NP = LLP->head->next;
    printf("\nThe link list are: ");
    while(NP != LLP->head){
        printf("%d-->",NP->data);
        NP = NP->next;
    }
    return OK;
}


/*----------------------------------*/
Status SRLLInsert(SRLListPtr SRLLP, int location, LElemType elem)
{
    int i,j,k;
    NodePtr NP,S;
    SRLListPtr LLP;
    LLP = SRLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    NP = LLP->head;
    i = location;
    j = SRLLLength(LLP);
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
    NP->next = S;
    if(i == j+1)
        LLP->rear = S;
    return OK;
}


/*----------------------------------*/
Status NodeDelete(SRLListPtr SRLLP, int location)
{
    int i,j,k;
    SRLListPtr LLP;
    NodePtr NP,D;
    LLP = SRLLP;
    if(!LLP){
        perror("It is a invalid linklist");
        return ERROR;
    }
    NP = LLP->head;
    i = location;
    j = SRLLLength(LLP);
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
    if(i==j)
        LLP->head = NP;
    free(D);
    return OK;
}


/*----------------------------------*/
Status SRLLDestroy(SRLListPtr SRLLP)
{
    int i;
    SRLListPtr LLP;
    NodePtr NP,NDP;
    LLP = SRLLP;
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
SRLListPtr SRLLUnion(SRLListPtr SRLLPA,SRLListPtr SRLLPB)
{
    NodePtr NP;
    NP = SRLLPA->rear->next;
    SRLLPA->rear->next = SRLLPB->head->next;
    SRLLPA->rear = SRLLPB->rear;
    free(SRLLPB->head);
    return SRLLPA;
}
