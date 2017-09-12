#include <stdio.h>
int main(int argc,char *argv[])
{
  int a,b,num1,num2,temp;
  printf ("please input two numbers(以逗号分隔）:\n");
  scanf("%d,%d",&num1,&num2);
  a=(num1>num2)?num1:num2;
  b=(a==num1)?num2:num1;
  while(b!=0)
    {
      temp=a%b;
      a=b;
      b=temp;
    }
  printf ("公约数:%d\n",a);
  printf ("公倍数:%d\n",num1*num2/a);
  return 0;
}
