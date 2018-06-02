#include <stdio.h>
#include "ArrayStack.h"

int main(void)
{
    int i,se=0;
    AStack *sp;
    sp = InitStack();
    printf("after initialed:\n");
    StackDisplay(sp);

    printf("\nafter push 4 elems:\n");
    for(i=1;i<=4;i++)
        Push(sp,i);
    StackDisplay(sp);

    printf("\nPop first:\n");
    Pop(sp,&se);
    StackDisplay(sp);
    printf("\npoped elem:%d\n",se);
    printf("\nStack length:%d\n",StackLength(sp));

    printf("\nPop 2:\n");
    Pop(sp,&se);
    StackDisplay(sp);
    printf("\npoped elem:%d\n",se);
    printf("\nStack length:%d\n",StackLength(sp));

    printf("\nPop 3:\n");
    Pop(sp,&se);
    StackDisplay(sp);
    printf("\npoped elem:%d\n",se);
    printf("\nStack length:%d\n",StackLength(sp));
    ClearStack(sp);
    printf("\nafter clear:\n");
    StackDisplay(sp);
    printf("\nStack length:%d\n",StackLength(sp));

    Push(sp,222);
    printf("\nafter push 1st:\n");
    StackDisplay(sp);

    printf("\nPop first:\n");
    Pop(sp,&se);
    StackDisplay(sp);
    printf("\npoped elem:%d\n",se);
    printf("\nStack length:%d\n",StackLength(sp));

    if(StackEmpty(sp))
        printf("--stack is empty");
    return 0;
}
