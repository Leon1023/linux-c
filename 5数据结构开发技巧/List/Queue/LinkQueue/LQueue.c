#include <stdio.h>
#include <stdlib.h>
#include "LQueue.h"

/*-------------------------------------*/
Status InitLQueue(LQueuePtr LQP)
{
    if( !(LQP->front = (LQNodePtr)malloc(sizeof(LQNode))) )
        return ERROR;
    LQP->front->data = 0;
    LQP->front->next = NULL;
    LQP->rear = LQP->front;
    return OK;
}


/*-------------------------------------*/
Status InLQueue(LQueuePtr LQP, QElemType elem)
{
    LQNodePtr in_node_ptr;        
    if( !(in_node_ptr = (LQNodePtr)malloc(sizeof(LQNode))) )
        return ERROR;
    in_node_ptr->data = elem;
    in_node_ptr->next = NULL;
    LQP->rear->next = in_node_ptr;
    LQP->rear = in_node_ptr;
    return OK;
}


/*-------------------------------------*/
Status OutLQueue(LQueuePtr LQP, QElemType *elem)
{
    LQNodePtr out_node_ptr;
    if(LQP->front == LQP->rear)
        return ERROR;
    out_node_ptr = LQP->front->next;
    *elem = out_node_ptr->data;
    LQP->front->next = out_node_ptr->next;
    if(LQP->rear == out_node_ptr)
        LQP->rear = LQP->front;
    free(out_node_ptr);
    return OK;
}
