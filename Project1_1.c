#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main()
{	
	float a;
	float f(float);
	a=f(10);
	printf("%f\n",a);
	
}

float f(float x)
{
	return sin(x);
}
