#include <stdio.h>
#include "LinkStack.h"

int main(void)
{
    int i;
    SElemType elem;
    LStackPtr lsp;
    LSInit(lsp);
    printf("after initialed:\n");
    LSDisplay(lsp);

    printf("\nafter pushed:\n");
    for(i=1;i<=4;i++)
        if(Push(lsp,i)==ERROR){
            perror("The queue is full!");
    return ERROR;
        }
    LSDisplay(lsp);

    printf("\npop first elem:\n");
    Pop(lsp,&elem);
    LSDisplay(lsp);
    printf("\nouted elem:%d\n",elem);
    printf("\nqueue length:%d\n",LSLength(lsp));

    printf("\npop second:\n");
    Pop(lsp,&elem);
    LSDisplay(lsp);
    printf("\nouted elem:%d\n",elem);
    printf("\nqueue length:%d\n",LSLength(lsp));
    printf("\npop third:\n");
    Pop(lsp,&elem);
    LSDisplay(lsp);
    printf("\nouted elem:%d\n",elem);
    printf("\nqueue length:%d\n",LSLength(lsp));
    printf("\npop forth:\n");
    Pop(lsp,&elem);
    LSDisplay(lsp);
    printf("\nouted elem:%d\n",elem);
    printf("\nqueue length:%d\n",LSLength(lsp));
    printf("\npop fifth:\n");
    Pop(lsp,&elem);
    LSDisplay(lsp);
    printf("\nouted elem:%d\n",elem);
    printf("\nqueue length:%d\n",LSLength(lsp));
    return 0;
}
