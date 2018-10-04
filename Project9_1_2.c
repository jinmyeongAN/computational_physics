#include <math.h>
#include "stdio.h"
#include "nrutil.h"
#define TINY 1.0e-20 //A small number.
void ludcmp(float a[][4], int n, int *indx, float *d)

{
int i,imax,j,k;
float big,dum,sum,temp;
float *vv; //vv stores the implicit scaling of each row.
vv=vector(1,n);
*d=1.0; //No row interchanges yet.
for (i=1;i<=n;i++) { //Loop over rows to get the implicit scaling informabig=0.0;
//tion.
for (j=1;j<=n;j++)
if ((temp=fabs(a[i][j])) > big) big=temp;
if (big == 0.0) nrerror("Singular matrix in routine ludcmp");
//No nonzero largest element.
vv[i]=1.0/big; //Save the scaling.
}
for (j=1;j<=n;j++) { //This is the loop over columns of Crout’s method.
for (i=1;i<j;i++) { //This is equation (2.3.12) except for i = j.
sum=a[i][j];
for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
a[i][j]=sum;
}
big=0.0; //Initialize for the search for largest pivot element.
for (i=j;i<=n;i++) { //This is i = j of equation (2.3.12) and i = j + 1 ...N
sum=a[i][j]; //of equation (2.3.13).
for (k=1;k<j;k++)
sum -= a[i][k]*a[k][j];
a[i][j]=sum;
if ( (dum=vv[i]*fabs(sum)) >= big) {
//Is the figure of merit for the pivot better than the best so far?
big=dum;
imax=i;
}
}
if (j != imax) { //Do we need to interchange rows?
for (k=1;k<=n;k++) { //Yes, do so...
dum=a[imax][k];
a[imax][k]=a[j][k];
a[j][k]=dum;
}
*d = -(*d); //...and change the parity of d.
vv[imax]=vv[j]; //Also interchange the scale factor.
}
indx[j]=imax;
if (a[j][j] == 0.0) a[j][j]=TINY;
//If the pivot element is zero the matrix is singular (at least to the precision of the
//algorithm). For some applications on singular matrices, it is desirable to substitute
//TINY for zero.
if (j != n) { //Now, finally, divide by the pivot element.
dum=1.0/(a[j][j]);
for (i=j+1;i<=n;i++) a[i][j] *= dum;
}
} //Go back for the next column in the reduction.
free_vector(vv,1,n);
}
void lubksb(float a[][4], int n, int *indx, float b[])
{
int i,ii=0,ip,j;
float sum;
for (i=1;i<=n;i++) { //When ii is set to a positive value, it will become the
//index of the first nonvanishing element of b. We now
//do the forward substitution, equation (2.3.6). The
//only new wrinkle is to unscramble the permutation
//as we go.
ip=indx[i];
sum=b[ip];
b[ip]=b[i];
if (ii)
for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
else if (sum) ii=i; //A nonzero element was encountered, so from now on we
b[i]=sum; //will have to do the sums in the loop above.
}
for (i=n;i>=1;i--) { //Now we do the backsubstitution, equation (2.3.7).
sum=b[i];
for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
b[i]=sum/a[i][i]; //Store a component of the solution vector X.
} //All done!
}



main()
{
	float a[4][4]={{0,0,0,0},{0,2,3,-1},{0,6,-3,5},{0,1,7,-1}};
	float b[4]={0,2,-5,3};
	int indx[4];
	int n=3;
	float *d;

	ludcmp(a,n,indx,d);
	lubksb(a,n,indx,b);

	printf("the solution is \n");
	printf("%f\n",b[1]);
	printf("%f\n",b[2]);
	printf("%f\n",b[3]);

	
	




}



