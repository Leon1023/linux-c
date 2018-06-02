#include <stdio.h>
#include "DoubleStack.h"

int main(void)
{
    int i,j,se=0;
    DStack *sp;
    sp = InitStack();
    printf("after initialed:\n");
    StackDisplay(sp);

    printf("\nafter push 4 elems for each stack:\n");
    for(i=1;i<=4;i++)
        Push(sp,1,i);
    for(j=10;j>=7;j--)
        Push(sp,2,j);
    StackDisplay(sp);
    printf("\nStack length:%d\n",StackLength(sp));

    ClearStack(sp);
    printf("\nafter clear:\n");
    StackDisplay(sp);
    printf("\nStack length:%d\n",StackLength(sp));

    Push(sp,1,111);
    Push(sp,2,222);
    printf("\nafter push 1st:\n");
    StackDisplay(sp);

    printf("\nPop first:\n");
    Pop(sp,1,&se);
    StackDisplay(sp);
    printf("\npoped elem:%d\n",se);

    printf("\nPop 2sec:\n");
    Pop(sp,1,&se);
    StackDisplay(sp);
    return 0;
}
