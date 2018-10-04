
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
#define N     2            
#define dist  0.001        
#define MAX   70.0          
 
FILE *output;              
 
void runge4(double x, double y[], double step);  
double f(double x, double y[], int i);            
main()
{
  double t, y[N];
  int j;
 
  output=fopen("result.txt", "w");           
 
  t   = 0.0;
  y[0]= 1.0;
  y[1]= 0.0;                                    
 
  fprintf(output, "%f\t%f\n", t, y[0]);
 
  for (j=1; j*dist<=MAX ;j++)                     
     {
       t=j*dist;
       runge4(t, y, dist);
       fprintf(output, "%f\t%f\t%f\n", t, y[1], y[0]);
     }
  fclose(output);
}
void runge4(double x, double y[], double step)
{
  double h=step/2.0,           
  t1[N], t2[N], t3[N],         
  k1[N], k2[N], k3[N],k4[N];    
  int i;
 
  for (i=0;i<N;i++) t1[i]=y[i]+0.5*(k1[i]=step*f(x, y, i));
  for (i=0;i<N;i++) t2[i]=y[i]+0.5*(k2[i]=step*f(x+h, t1, i));
  for (i=0;i<N;i++) t3[i]=y[i]+ (k3[i]=step*f(x+h, t2, i));
  for (i=0;i<N;i++) k4[i]= step*f(x+step, t3, i);
  
  for (i=0;i<N;i++) y[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6.0;
}
 
double f(double x, double y[], int i)
{
  if (i==0) return(y[1]);
  if (i==1) return(-sqrt(y[0]*y[0]+y[1]*y[1])*cos(x));
      
  if (i>1) exit(2);
}
