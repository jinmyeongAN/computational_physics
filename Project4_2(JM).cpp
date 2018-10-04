//Start line
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

static double fd(double x)
{
	return (5*x*x*x*x-12*x*x*x-9*x*x+14*x+2);
}

template <class T>
void zbrak(T &fx, const double x1, const double x2, const int n, vector<double> &xb1,
	vector<double> &xb2, int &nroot)
{
	int nb=20;
	xb1.resize(nb);
	xb2.resize(nb);
	nroot=0;
	double dx=(x2-x1)/n;
	double x=x1;
	double fp=fx(x1);
	for (int i=0;i<n;i++) {
		double fc=fx(x += dx);
		if (fc*fp <= 0.0) {
			xb1[nroot]=x-dx;
			xb2[nroot++]=x;
			if(nroot == nb) {
				vector<double> tempvec1(xb1),tempvec2(xb2);
				xb1.resize(2*nb);
				xb2.resize(2*nb);
				for (int j=0; j<nb; j++) {
					xb1[j]=tempvec1[j];
					xb2[j]=tempvec2[j];
				}
				nb *= 2;
			}
		}
		fp=fc;
	}
}

template <class T>
double rtsafe(T &funcd, const double x1, const double x2, const double xacc) {
	const int MAXIT=100;
	double xh,xl;
	double fl=funcd(x1);
	double fh=funcd(x2);
	if ((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0))
		
	if (fl == 0.0) return x1;
	if (fh == 0.0) return x2;
	if (fl < 0.0) {
		xl=x1;
		xh=x2;
	} else {
		xh=x1;
		xl=x2;
	}
	double rts=0.5*(x1+x2);
	double dxold=abs(x2-x1);
	double dx=dxold;
	double f=funcd(rts);
	double df=fd(rts);
	for (int j=0;j<MAXIT;j++) {
		if ((((rts-xh)*df-f)*((rts-xl)*df-f) > 0.0)
			|| (abs(2.0*f) > abs(dxold*df))) {
			dxold=dx;
			dx=0.5*(xh-xl);
			rts=xl+dx;
			
			if (xl == rts) return rts;
		} else {
			dxold=dx;
			dx=f/df;
			double temp=rts;
			rts -= dx;
			if (temp == rts) return rts;
		}
		if (abs(dx) < xacc) return rts;
		f=funcd(rts);
		df=fd(rts);
		if (f < 0.0)
			xl=rts;
		else
			{xl=rts;}
	}
	
}

double fx(double x)
{
	return (x*x*x*x*x-3*x*x*x*x-3*x*x*x+7*x*x+2*x-1);

}

int main()
{
	const int N=100000,NBMAX=20;
        const double X1=-2,X2=5;
        int i,nb=NBMAX;
        double xacc,root;
        vector<double> xb1(NBMAX),xb2(NBMAX);

        zbrak(fx,X1,X2,N,xb1,xb2,nb);
        cout << endl << "Roots of function" << endl;
        cout << setw(20) << "x" << setw(16) << "f(x)" << endl;
        cout << fixed << setprecision(6);
	
        for (i=0;i<nb;i++) {
          xacc=(1.0e-10)*(xb1[i]+xb2[i])/2.0;
          root=rtsafe(fx,xb1[i],xb2[i],xacc);
          cout << "root" << setw(4) << (i+1) << setw(15) << root;
          cout << setw(15) << fx(root) << endl;
        }
        return 0;
}
