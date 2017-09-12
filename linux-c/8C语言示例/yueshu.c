#include <stdio.h>
#include <math.h>
int main(void)
{
  int n,i,k;
  printf ("please input a number:\n");
  scanf("%d=",&n);
  k=sqrt(n);
  printf ("%d=",n);
  for(i=2;i<=k;i++)
    while(n!=i)
      {
	if (n%i==0)
	  {
	    printf ("%d*",i);
	    n=n/i;
	  }
	else
	  break;
      }
  printf ("%d\n",n);
  return 0;
}
