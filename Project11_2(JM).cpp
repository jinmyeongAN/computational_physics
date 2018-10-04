#include <cmath>
#include <iostream>
#include <vector>
#include "nr3.h"
#include <fstream>

using namespace std;


struct Epsalg {
	vector <double> e;
	int n,ncv;
	bool cnvgd;
	double eps,small,big,lastval,lasteps;
	
	Epsalg(int nmax, double epss) : e(nmax), n(0), ncv(0), cnvgd(0), eps(epss), lastval(0.)
	{
		small = numeric_limits<double>::min()*10.0;
		big = numeric_limits<double>::max();
	}

	double next(double sum) {
		double diff,temp1,temp2,val;
		e[n]=sum;
		temp2=0.0;
		for (int j=n; j>0; j--) {
			temp1=temp2;
			temp2=e[j-1];
			diff=e[j]-temp2;
			if (abs(diff) <= small)
				e[j-1]=big;
			else
				e[j-1]=temp1+1.0/diff;
		}
		n++;
		val = (n & 1) ? e[0] : e[1];
		if (abs(val) > 0.01*big) val = lastval;
		lasteps = abs(val-lastval);
		if (lasteps > eps) ncv = 0;
		else ncv++;
		if (ncv >= 3) cnvgd = 1;
		return (lastval = val);
	}
	
};

double term(int jterm)
{
	double answer;
	answer = pow(-1,jterm)/(2*jterm+1);
	return answer;
}

int main()
{
	double val, partialsum, eps=10, nmax =10;
	int i,j;
	Epsalg mysum(nmax,eps);	
	
	
	ofstream regular("regular.txt",ios::trunc);	
	ofstream d2process("d2process.txt",ios::trunc);
	
	for (j=1; j <= nmax; j++)
	{
		for (i=1; i <= j; i++)
		{
			partialsum += term(i-1);	
		}
		regular << j-1 << " " << partialsum << endl;
		val = mysum.next(partialsum);
			
		if (j > 2)
		{	d2process << j-3 << " " << val << endl;
			
		}
		
		partialsum = 0;
	}
}
