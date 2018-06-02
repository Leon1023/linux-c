#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"

int main(void)
{
    BiTree mytree;
    CreatPreOrdBiTree(&mytree);
    PreOrderTraverse(&mytree);
    return 0;
}
