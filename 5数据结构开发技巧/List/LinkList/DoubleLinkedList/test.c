#include <stdio.h>
#include "DoubleLinkedList.h"

int main(void)
{
    int i;
    DLList dll;
    DLListPtr dllp = &dll;
    DLLInit(dllp);
    printf("after initialed:\n");
    DLLDisplay(dllp);

    printf("\nafter inserted:\n");
    for(i=1;i<=4;i++)
        if(DLLInsert(dllp,i,i)==ERROR)
            perror("The list is full!");
    DLLDisplay(dllp);

    printf("\nafter 0 inserted:\n");
    if(DLLInsert(dllp,0,222)==ERROR)
        perror("The queue is full!");
    else
        DLLDisplay(dllp);

    printf("\nafter 000 inserted:\n");
    if(DLLInsert(dllp,DLLLength(dllp)+2,99)==ERROR)
        perror("The queue is full!");
    else
        DLLDisplay(dllp);

    printf("\ndelete 0:\n");
    NodeDelete(dllp,0);
    DLLDisplay(dllp);
    printf("\nthe list length:%d\n",DLLLength(dllp));

    printf("\ndelete 0+:\n");
    NodeDelete(dllp,DLLLength(dllp)+1);
    DLLDisplay(dllp);
    printf("\nthe list length:%d\n",DLLLength(dllp));
    return 0;
}
