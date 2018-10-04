#include "nrutil.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

void spline(float xaa[], float yaa[], int n, float yp1, float ypn, float y2a[])
//Given arrays x[1..n] and y[1..n] containing a tabulated function, i.e., yi = f(xi), with
//x1 < x2 <...< xN , and given values yp1 and ypn for the first derivative of the interpolating
//function at points 1 and n, respectively, this routine returns an array y2a[1..n] that contains
//the second derivatives of the interpolating function at the tabulated points xi. If yp1 and/or
//ypn are equal to 1 × 1030 or larger, the routine is signaled to set the corresponding boundary
//condition for a natural spline, with zero second derivative on that boundary.

{
int i,k;
float p,qn,sig,un,*u;
u=vector(1,n-1);
if (yp1 > 0.99e30) y2a[1]=u[1]=0.0;
else { //or else to have a specified first derivative.
y2a[1] = -0.5;
u[1]=(3.0/(xaa[2]-xaa[1]))*((yaa[2]-yaa[1])/(xaa[2]-xaa[1])-yp1);
}
//printf("X is %f\n",xa[1]);
for (i=2;i<=n-1;i++) { //This is the decomposition loop of the tridiagonal algorithm.
//y2 and u are used for temporary
//storage of the decomposed
//factors.
sig=(xaa[i]-xaa[i-1])/(xaa[i+1]-xaa[i-1]);
p=sig*y2a[i-1]+2.0;
y2a[i]=(sig-1.0)/p;
u[i]=(yaa[i+1]-yaa[i])/(xaa[i+1]-xaa[i]) - (yaa[i]-yaa[i-1])/(xaa[i]-xaa[i-1]);
u[i]=(6.0*u[i]/(xaa[i+1]-xaa[i-1])-sig*u[i-1])/p;
}
//printf("X is %f\n",xa[1]);
if (ypn > 0.99e30) //The upper boundary condition is set either to be
qn=un=0.0; //“natural”
else { //or else to have a specified first derivative.
qn=0.5;
un=(3.0/(xaa[n]-xaa[n-1]))*(ypn-(yaa[n]-yaa[n-1])/(xaa[n]-xaa[n-1]));
}
//printf("X is %f\n",xa[1]);
y2a[n]=(un-qn*u[n-1])/(qn*y2a[n-1]+1.0);
//printf("X is %f\n",xa[1]);
for (k=n-1;k>=1;k--) //This is the backsubstitution loop of the tridiagonal
y2a[k]=y2a[k]*y2a[k+1]+u[k]; //algorithm.
free_vector(u,1,n-1);
//printf("X is %f\n",xa[1]);
}

//It is important to understand that the program spline is called only once to
//process an entire tabulated function in arrays xi and yi. Once this has been done,
//values of the interpolated function for any value of x are obtained by calls (as many
//as desired) to a separate routine splint (for “spline interpolation”):

void splint(float xa[], float ya[], float y2a[], int n, float x, float *y)
//Given the arrays xa[1..n] and ya[1..n], which tabulate a function (with the xai’s in order),
//and given the array y2a[1..n], which is the output from spline above, and given a value of
//x, this routine returns a cubic-spline interpolated value y.

{
void nrerror(char error_text[]);
int klo,khi,k;
float h,b,a;
klo=1; //We will find the right place in the table by means of
//bisection. This is optimal if sequential calls to this
//routine are at random values of x. If sequential calls
//are in order, and closely spaced, one would do better
//to store previous values of klo and khi and test if
//they remain appropriate on the next call.
khi=n;

while (khi-klo > 1) {
k=(khi+klo) >> 1;
if (xa[k] > x) khi=k;
else klo=k;
} //klo and khi now bracket the input value of x.

h=xa[khi]-xa[klo];

if (h == 0.0) nrerror("Bad xa input to routine splint"); //The xa’s must be disa=(xa[khi]-x)/h;
//tinct.
b=(x-xa[klo])/h; //Cubic spline polynomial is now evaluated.
*y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;

}


main()
{
	float xa[12];
	float ya[12];
	int n=11;
	float yp1=cos(xa[1]);
	float ypn=cos(xa[11]);
	float y2a[12];
	float pi=3.141592;
	
	float x;
	printf("X is ");
	scanf("%f",&x);
	float y;
	int i,j;	
	
	for(i=1;i<12;i++)
	{
		xa[i]=(i-1)*2*pi/10;
	}

	for(j=1;j<12;j++)
	{
		ya[j]=sin(xa[j]);
	}

	spline(xa,ya,n,yp1,ypn,y2a);
	splint(xa,ya,y2a,n,x,&y);

	printf("the answer of cubic-splined is %f\n",y);
	printf("the exact number is %f\n",sin(x));

}
