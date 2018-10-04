#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int f1(int a)
{
	int i;

	for(i=1;i<a;i++)
	{
		a=a*(a-i);
	}
	
	return a;
}

int f2(int b)
{
	int i,j;
	
	for(i=1;i<b;i++)
	{
		b=b*(b-i);
	}

	for(j=1;j<b;j++)
	{
		b=b*(b-j);
	}

	return b;
}

int main()
{
	int x;
	
	scanf("%d",&x);
	int f1(int),f2(int);
	
	printf("N! is %d, N!! is %d",f1(x),f2(x));
}
