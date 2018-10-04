#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 10;

void eulsum(float *sum,float term,int jterm, float wksp[])
{
	int j;
	static int nterm;
	float tmp,dum;

	if (jterm == 1) {
		nterm=1;
		*sum=0.5*(wksp[1]=term);
	} else {
		tmp=wksp[1];
		wksp[1]=term;
		for (j=1;j<=nterm-1;j++) {
			dum=wksp[j+1];
			wksp[j+1]=0.5*(wksp[j]+tmp);
			tmp=dum;
		}
		wksp[nterm+1]=0.5*(wksp[nterm]+tmp);
		if (fabs(wksp[nterm+1]) <= fabs(wksp[nterm]))
			*sum += (0.5*wksp[++nterm]);
		else
			*sum += wksp[nterm+1];
	}
}

float term (int jterm)
{
	float y= pow(-1,jterm)/(2*jterm+1);
	return y;
}

int main()
{
	int j;
	float sum = 0;
	float wksp[MAX];
	float tmp;

	ofstream euler("eulsum.txt",ios::trunc);
	for (j = 1; j < MAX; j++)
	{
		tmp = term(j-1);
		eulsum(&sum, tmp, j, wksp);
		euler << j-1 << " " << sum << endl;
	}
}
