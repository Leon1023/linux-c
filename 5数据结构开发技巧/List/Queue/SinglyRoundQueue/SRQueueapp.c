#include <stdio.h>
#include "SRQueue.h"

int main(void)
{
    int i;
    QElemType outelem[2];
    SRQueue srq;
    SRQueuePtr QP = &srq;
    InitSRQueue(QP);
    printf("after initialed:\n");
    SRQDisplay(srq);

    printf("\nafter inserted:\n");
    for(i=1;i<=4;i++)
        if(InSRQueue(QP,i)==ERROR)
            perror("The queue is full!");
    SRQDisplay(srq);

    printf("\nafter inserted:\n");
    if(InSRQueue(QP,222)==ERROR)
        perror("The queue is full!");
    else
        SRQDisplay(srq);

    printf("\ndelete first:\n");
    OutSRQueue(QP,&outelem[0]);
    SRQDisplay(srq);
    printf("\nouted elem:%d\n",outelem[0]);
    printf("\nqueue length:%d\n",SRQLength(srq));

    printf("\ndelete second:\n");
    OutSRQueue(QP,&outelem[1]);
    SRQDisplay(srq);
    printf("\nouted elem:%d\n",outelem[1]);
    printf("\nqueue length:%d\n",SRQLength(srq));
    return 0;
}
