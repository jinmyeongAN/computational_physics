#include <iostream>
#include <cstdlib>

using namespace std;

class calculate
{
}

class plus : public calculate
{
		public:
		float summation(float a, float b);
		float product(float a, float b)
		
};

float plus::summation(float a,float b)
{
	float sum;
	sum=a+b;
	return sum;
}

float plus::product(float a,float b)
{
	float g;
	g=a*b;
	return g;
}

main(int argc,char *argv[])
{
	
	float x,y,result;
	x=atof(argv[1]);
	y=atof(argv[2]);
	
	plus calculation;
	result=calculation.summation(x,y);
	cout<<"sum= "<<result<<endl;
}

