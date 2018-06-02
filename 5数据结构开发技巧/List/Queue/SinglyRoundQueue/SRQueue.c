#include "SRQueue.h"
#include <stdio.h>

/*------------------------------------------*/
Status InitSRQueue(SRQueuePtr QP)
{
    if(!QP){
        return ERROR;
    }
    QP->front = 0;
    QP->rear = 0;
    return OK;
}


/*------------------------------------------*/
int SRQLength(SRQueue Q)
{
    return( (Q.rear-Q.front+QSize)%QSize );
}


/*------------------------------------------*/
Status SRQDisplay(SRQueue Q)
{
    int i;
    if(Q.front==Q.rear){
        printf("It is a NULL queue!\n");
        return ERROR;
    }
    printf("The Queue are:");
    for(i=Q.front;i<Q.rear;i++){
        printf("%d\t",Q.data[i]);
    }
    return OK;
}
    

/*------------------------------------------*/
Status InSRQueue(SRQueuePtr QP, QElemType elem)
{
    if((QP->rear+1)%QSize == QP->front){
        return ERROR;
    }
    QP->data[QP->rear] = elem;
    QP->rear = (QP->rear+1)%QSize;
    return OK;
}


/*------------------------------------------*/
Status OutSRQueue(SRQueuePtr QP, QElemType *elem)
{
    if(QP->front == QP->rear){
        return ERROR;
    }
    *elem = QP->data[QP->front];
    QP->front = (QP->front+1)%QSize;
    return OK;
}
