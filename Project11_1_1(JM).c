#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "nrutil.h"

void polint(float xa[], float ya[], int n, float x, float *y, float *dy)
//Given arrays xa[1..n] and ya[1..n], and given a value x, this routine returns a value y, //and
//an error estimate dy. If P(x) is the polynomial of degree N − 1 such that P(xai) = yai, i =
//1,..., n, then the returned value y = P(x).

{
int i,m,ns=1;
float den,dif,dift,ho,hp,w;
float *c,*d;
dif=fabs(x-xa[1]);
c=vector(1,n);
d=vector(1,n);
for (i=1;i<=n;i++) { //Here we find the index ns of the closest table entry,
if ( (dift=fabs(x-xa[i])) < dif) {
ns=i;
dif=dift;
}
c[i]=ya[i]; //and initialize the tableau of c’s and d’s.
d[i]=ya[i];

}
*y=ya[ns--]; //This is the initial approximation to y.

for (m=1;m<n;m++) { //For each column of the tableau,
for (i=1;i<=n-m;i++) { //we loop over the current c’s and d’s and update
ho=xa[i]-x; //them.
hp=xa[i+m]-x;
w=c[i+1]-d[i];
if ( (den=ho-hp) == 0.0) nrerror("Error in routine polint");
//This error can occur only if two input xa’s are (to within roundoff) identical.
den=w/den;
d[i]=hp*den; //Here the c’s and d’s are updated.
c[i]=ho*den;
}
*y += (*dy=(2*ns < (n-m) ? c[ns+1] : d[ns--]));
//After each column in the tableau is completed, we decide which correction, c or d,
//we want to add to our accumulating value of y, i.e., which path to take through the
//tableau—forking up or down. We do this in such a way as to take the most “straight
//line” route through the tableau to its apex, updating ns accordingly to keep track of
//where we are. This route keeps the partial approximations centered (insofar as possible)
//on the target x. The last dy added is thus the error indication.
}
free_vector(d,1,n);
free_vector(c,1,n);
}


main()
{
	float xa[12];
	float ya[12];
	int n=11;
	float pi=3.141592;
	float x;

	printf("X is ");
	scanf("%f",&x);

	float y;
	float dy;
	int i,j;	
	
	xa[0]=0;
	ya[0]=0;
	for(i=1;i<12;i++)
	{
		xa[i]=(i-1)*2*pi/10;
	}

	for(j=1;j<12;j++)
	{
		ya[j]=sin(xa[j]);
	}

	polint(xa,ya,n,x,&y,&dy);

	printf("the answer of linear interpolation is %f\n",y);

	printf("the exact number is %f\n",sin(x));
}
