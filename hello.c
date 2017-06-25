#include <stdio.h>

int sum(int ,int);
void main()
{
	int a,b,c;
	a = 1;b = 2;
	c = sum(a,b);	
printf("hello,leon!\n\ta+b=%d\n",c);
}

int sum(int x ,int y)
{
	return(x+y);
}
