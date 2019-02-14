/*
 * 实现自定义打印函数LOG()，唯有在程序定义了DEBUG宏之后，
 * 该函数才能有效，没定义宏时该函数等同于一个空语句。
 */

#include <stdio.h>

void __attribute__(( format(printf,1,2) )) LOG(char *fmt,...)
{
#ifdef DEBUG
    va_list args;
    va_start(args,fmt);
    vprintf(fmt,args);
    va_end(args);
#endif
}
