#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define MAXITS 1000
#define EPS 1.0e-5


void sor(double a[][101], double b[][101], double c[][101], double d[][101], double e[][101],double f[][101], double u[][102], int jmax, double rjac)

//Successive overrelaxation solution of equation (19.5.25) with Chebyshev acceleration. a, b, //c,
//d, e, and f are input as the coefficients of the equation, each dimensioned to the grid size
//[1..jmax][1..jmax]. u is input as the initial guess to the solution, usually zero, and returns
//with the final value. rjac is input as the spectral radius of the Jacobi iteration, or an estimate
//of it.

{


printf("a[100][100] is %f\n",a[100][100]);
printf("u[100][50] is %f\n",u[100][50]);
printf("u[100][100] is %f\n",u[100][100]);
printf("u[1][50] is %f\n",u[1][50]);


//void nrerror(char error_text[]);
int ipass,j,jsw,l,lsw,n;
double anorm,anormf=0.0,omega=1.0,resid;
//Double precision is a good idea for jmax bigger than about 25.
for (j=2;j<jmax;j++)
//Compute initial norm of residual and terminate iteration when norm has been reduced by
//a factor EPS.
for (l=2;l<jmax;l++)
anormf += fabs(f[j][l]); //Assumes initial u is zero.
for (n=1;n<=MAXITS;n++) {
anorm=0.0;
jsw=1;
for (ipass=1;ipass<=2;ipass++) { //Odd-even ordering.
lsw=jsw;
for (j=2;j<jmax;j++) {
for (l=lsw+1;l<jmax;l+=2) {
resid=a[j][l]*u[j+1][l]
+b[j][l]*u[j-1][l]
+c[j][l]*u[j][l+1]
+d[j][l]*u[j][l-1]
+e[j][l]*u[j][l]
-f[j][l];
anorm += fabs(resid);
u[j][l] -= omega*resid/e[j][l];
}
lsw=3-lsw;
}
jsw=3-jsw;
omega=(n == 1 && ipass == 1 ? 1.0/(1.0-0.5*rjac*rjac) :
1.0/(1.0-0.25*rjac*rjac*omega));
}
if (anorm < EPS*anormf) return;
}
//nrerror("MAXITS exceeded");
}

main()
{
	int jmax=100;
	double a[jmax+1][jmax+1];
	double b[jmax+1][jmax+1];
	double c[jmax+1][jmax+1];
	double d[jmax+1][jmax+1];
	double e[jmax+1][jmax+1];
	double f[jmax+1][jmax+1];
	double u[jmax+2][jmax+2];	
	double rjac=0;

	//the value of a,b,c,d,e,f
	int k,l;
	for(k=1;k<jmax+1;k++)
	{
		for(l=1;l<jmax+1;l++)
		{
			a[k][l]=1;
			b[k][l]=1;
			c[k][l]=1;
			d[k][l]=1;
			e[k][l]=-4;
			f[k][l]=0;
			
		}
	}
	//initial value
	int i;
	for(i=1;i<jmax+1;i++)
	{
		u[jmax][i]=10;
		
		printf("me? %f\n",u[100][i]);
		u[1][i]=-5;
		u[i][1]=0;
		u[i][100]=0;
		
		
	}
	
	sor(a,b,c,d,e,f,u,jmax,rjac);
	

	FILE *graph20;
	graph20=fopen("laplace[y][20].txt","w");
	int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph20,"%d %f\n",j,u[j][20]);
	}
	fclose(graph20);

	FILE *graph40;
	graph40=fopen("laplace[y][40].txt","w");
	//int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph40,"%d %f\n",j,u[j][40]);
	}
	fclose(graph40);

	FILE *graph60;
	graph60=fopen("laplace[y][60].txt","w");
	//int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph60,"%d %f\n",j,u[j][60]);
	}
	fclose(graph60);

	FILE *graph80;
	graph80=fopen("laplace[y][80].txt","w");
	//int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph20,"%d %f\n",j,u[j][80]);
	}
	fclose(graph80);

	FILE *graph10;
	graph10=fopen("laplace[y][10].txt","w");
	//int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph10,"%d %f\n",j,u[j][10]);
	}
	fclose(graph10);

	FILE *graph90;
	graph90=fopen("laplace[y][90].txt","w");
	//int j;
	for(j=1;j<jmax+1;j++)
	{
		fprintf(graph90,"%d %f\n",j,u[j][90]);
	}
	fclose(graph90);

}


