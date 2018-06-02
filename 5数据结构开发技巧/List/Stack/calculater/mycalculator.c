#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculater.h"
#define MAXSIZE 50
int main(void)
{
    char mid_express[MAXSIZE]={'1','+','2','-','3','\0'};
    char end_express[MAXSIZE];
    char *exp_mid,*exp_end;
    exp_mid = mid_express;
    exp_end = end_express;
 //   puts("Enter express");
//    scanf("%s",mid_express);
//    MidToEnd(exp_mid,exp_end);    
//    puts(mid_express);
    printf("%c\n",mid_express[4]);
    printf("%c\n",mid_express[5]);
    return 0;
}
