#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double exponential(double x)
{
	return exp(-x*x);
}

double trap(double (*func)(double), double a, double b, int n)
{
	double sum=0;
	int i;

		for(i=1;i<n-1;i++)
		{
			sum=sum+(b-a)/(n-1)*(func(a+(b-a)/(n-1)*i));
		}	
		sum=sum+(b-a)/(n-1)*0.5*(func(a)+func(a+(b-a)));
		return sum;
}


int main()
{
	double result=0;
	int num;
	
	scanf("%d",&num);

	result=trap(exponential,-1,1,num);
	printf("%f\n",result);

	return 0;
}
