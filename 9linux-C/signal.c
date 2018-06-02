/*名称：signal.c
 *功能：通过signal()函数自定义信号处理函数，
 *知识点：使用 signal()函数处理时，只需要指出要处理的信号和处理函数即可。
          它主要是用于前 32 种非实时信号的处理，不支持信号传递信息，但是
		  由于使用简单、易于理解，因此也受到很多程序员的欢迎。Linux 还支
		  持一个更健壮、更新的信号处理函数 sigaction()，推荐使用该函数。     
 *作者：赵陈亮
 *邮箱：liangzc1124@163.com
 *日期：2018年3月2日
 */
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

/*自定义信号处理函数*/ 
void my_func(int sign_no) 
{ 
 if (sign_no == SIGINT) { 
   printf("\nI have get SIGINT\n"); 
 } 
 else if (sign_no == SIGQUIT) { 
   printf("\nI have get SIGQUIT\n"); 
 } 
} 

int main() 
{ 
  printf("Waiting for signal SIGINT or SIGQUIT...\n"); 
 /* 发出相应的信号，并跳转到信号处理函数处 */ 
 signal(SIGINT, my_func);/*Ctrl+C*/ 
 signal(SIGQUIT, my_func); /*Ctrl+\*/
 pause(); 
 exit(0); 
} 
