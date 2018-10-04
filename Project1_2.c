#include "stdio.h"
#include "stdlib.h"
#include "math.h"

float f1(float x1){
	return exp(-x1);
}

float f2(float x2){
	return x2*x2;
}

int main(){
	float f1(float);
	float f2(float);
	float y1,y2,y3;
	
	y1=f1(10);
	y2=f2(10);
	y3=y1*y2;
	
	printf("%f\n",y3);

}
