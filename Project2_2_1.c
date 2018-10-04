#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main()
{
	float f1(float);
	float f2(float);
	float x;
	
	scanf("%f",&x);
	printf("N! is %f, N!! is %f",f1(x),f2(x));
}

float f1(float a)
{
	int i;
	float c=a;
	for(i=1;i<c;i++)
	{
		a=a*(c-i);
	}

	return a;
}

float f2(float a)
{
	int j;
	float c=a;
	if(a==1)
	{
		return 1;
	}

	else
	{
		for(j=2;j<c;j=2+j)
		{
			a=a*(c-j);
		}


		return a;
	}
}


