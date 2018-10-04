//Start
#include <math.h>
#define MAXIT 100
#include <stdio.h>
#define NRANSI


#define N 100
#define NBMAX 20
#define X1 1.0
#define X2 50.0

void zbrak(float (*fx)(float), float x1, float x2, int n, float xb1[],
	float xb2[], int *nb)
{
	int nbb,i;
	float x,fp,fc,dx;

	nbb=0;
	dx=(x2-x1)/n;
	fp=(*fx)(x=x1);
	for (i=1;i<=n;i++) {
		fc=(*fx)(x += dx);
		if (fc*fp <= 0.0) {
			xb1[++nbb]=x-dx;
			xb2[nbb]=x;
			if(*nb == nbb) return;

		}
		fp=fc;
	}
	*nb = nbb;
}

float rtsafe(void (*funcd)(float, float *, float *), float x1, float x2,
	float xacc)
{
	void nrerror(char error_text[]);
	int j;
	float df,dx,dxold,f,fh,fl;
	float temp,xh,xl,rts;

	(*funcd)(x1,&fl,&df);
	(*funcd)(x2,&fh,&df);
	if ((fl > 0.0 && fh > 0.0) || (fl < 0.0 && fh < 0.0))
		nrerror("Root must be bracketed in rtsafe");
	if (fl == 0.0) return x1;
	if (fh == 0.0) return x2;
	if (fl < 0.0) {
		xl=x1;
		xh=x2;
	} else {
		xh=x1;
		xl=x2;
	}
	rts=0.5*(x1+x2);
	dxold=fabs(x2-x1);
	dx=dxold;
	(*funcd)(rts,&f,&df);
	for (j=1;j<=MAXIT;j++) {
		if ((((rts-xh)*df-f)*((rts-xl)*df-f) > 0.0)
			|| (fabs(2.0*f) > fabs(dxold*df))) {
			dxold=dx;
			dx=0.5*(xh-xl);
			rts=xl+dx;
			if (xl == rts) return rts;
		} else {
			dxold=dx;
			dx=f/df;
			temp=rts;
			rts -= dx;
			if (temp == rts) return rts;
		}
		if (fabs(dx) < xacc) return rts;
		(*funcd)(rts,&f,&df);
		if (f < 0.0)
			xl=rts;
		else
			xh=rts;
	}
	nrerror("Maximum number of iterations exceeded in rtsafe");
	return 0.0;
}
#undef MAXIT



static float fx(float x)
{
	return (x*x*x*x*x-3*x*x*x*x-3*x*x*x+7*x*x+2*x-1);
}

static void funcd(float x,float *fn, float *df)
{
	*fn = (x*x*x*x*x-3*x*x*x*x-3*x*x*x+7*x*x+2*x-1);
	*df = (5*x*x*x*x-12*x*x*x-9*x*x+14*x+2);
}

int main(void)
{
	int i,nb=NBMAX;
	float xacc,root,*xb1,*xb2;

	xb1=vector(1,NBMAX);
	xb2=vector(1,NBMAX);
	zbrak(fx,X1,X2,N,xb1,xb2,&nb);
	printf("\nRoots of bessj0:\n");
	printf("%21s %15s\n","x","f(x)");
	for (i=1;i<=nb;i++) {
		xacc=(1.0e-6)*(xb1[i]+xb2[i])/2.0;
		root=rtsafe(funcd,xb1[i],xb2[i],xacc);
		printf("root %3d %14.6f %14.6f\n",i,root,fx(root));
	}
	free_vector(xb2,1,NBMAX);
	free_vector(xb1,1,NBMAX);
	return 0;
}
#undef NRANSI
