#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//constant for Runge_Kutta 
#define N     2            
#define dist  pow(2,15)    
#define MAX   (pow(2,20)-1)*pow(2,15)

double array_r_se[2];
double array_r_em[2];          
double Xse[N],Yse[N],Xem[N],Yem[N];
 
void runge4_x_se(double x, double Xse[], double step);
void runge4_y_se(double x, double Yse[], double step);  
double f_x_se(double x, double Xse[], int i);            
double f_y_se(double x, double Yse[], int i);
void runge4_x_em(double x, double Xem[], double step);
void runge4_y_em(double x, double Yem[], double step);  
double f_x_em(double x, double Xem[], int i);            
double f_y_em(double x, double Yem[], int i);

main()
{
const double G= 6.673*pow(10,-11); 
const double m_s= 1.989*pow(10,30); 
const double m_e=  5.972*pow(10,24); 
const double m_m=  7.347*pow(10,22);
const double m_j=  1.898*pow(10,27);
const double r_se= 149597870700;
const double r_sj= 778500000000;
const double r_em= 384400000;
const double v_se= 29786.21;
const double v_em= 1018.18;

//orbit calculation

// (1) r_sm=|r_se+r_em|, (2) r_em


  FILE *out; //for the motion of the Moon from the Earth
  FILE *out2;//for the motion of the Moon from the Sun

  FILE *fft;//for the fft of the Moon from the Earth
  FILE *fft2;//for the fft of the Moon from the Sun
  FILE *fft_y;//for the fft of the Moon from the Earth
  FILE *fft2_y;//for the fft of the Moon from the Sun
  double t;
  
  int j;
  
  //make txt file for the motion graph and fft
  out=fopen("graphEM.txt", "w");
  out2=fopen("graphSM.txt","w");           
  
  fft=fopen("fftEM.txt","w"); //fft for Xem
  fft2=fopen("fftSM.txt","w");//fft for Xsm
  fft_y=fopen("fftEM_y.txt","w");//fft for Yem
  fft2_y=fopen("fftSM_y.txt","w");//fft for Ysm
  

  t   = 0.0; //initial time

  //x_se initial condition
  Xse[0]= r_se;//original function initial value of x_se
  Xse[1]= 0.0; //first derivative initial value of x_se

  //y_se initial codition
  Yse[0]=0.0;
  Yse[1]=v_se;                                    
 
  //x_em initial condition
  Xem[0]=r_em;
  Xem[1]=0.0;

  //y_em initial condition
  Yem[0]=0.0;
  Yem[1]=v_em;


  //put them into the 'txt' file
  fprintf(out, "%f\t%f\t%f\n", t, Xem[0],Yem[0]);
  fprintf(out2,"%f\t%f\t%f\n",t,Xem[0]+Xse[0],Yem[0]+Yse[0]);


  fprintf(fft,"%f\n",Xem[0]);
  fprintf(fft2,"%f\n",Xse[0]+Xem[0]);
  fprintf(fft_y,"%f\n",Yem[0]);
  fprintf(fft2_y,"%f\n",Yse[0]+Yem[0]);

  

  printf("%f\n",Xse[0]);
  for (j=1; j*dist<=MAX ;j++)                     
     {
       t=j*dist;
       runge4_x_se(t, Xse, dist);
       runge4_y_se(t, Yse, dist);
       runge4_x_em(t, Xem, dist);
       runge4_y_em(t, Yem, dist);
       
       fprintf(out, "%f\t%f\t%f\n", t,Xem[0], Yem[0]);
       fprintf(out2,"%f\t%f\t%f\n",t,Xem[0]+Xse[0],Yem[0]+Yse[0]);

       fprintf(fft,"%f\n",Xem[0]);
       fprintf(fft2,"%f\n",Xse[0]+Xem[0]);
       fprintf(fft_y,"%f\n",Yem[0]);
       fprintf(fft2_y,"%f\n",Yse[0]+Yem[0]);

     }
  fclose(out);
  fclose(out2);

  fclose(fft);
  fclose(fft2);
  fclose(fft_y);
  fclose(fft2_y);
}

// find x_se
void runge4_x_se(double x, double Xse[], double step)
{
  double h=step/2.0;           
  double t1_x_se[N], t2_x_se[N], t3_x_se[N],         
  k1_x_se[N], k2_x_se[N], k3_x_se[N],k4_x_se[N];    
  int i;

  //for finding r_se and r_em
  array_r_se[0]=sqrt(Xse[0]*Xse[0]+Yse[0]*Yse[0]);
  array_r_em[0]=sqrt(Xem[0]*Xem[0]+Yem[0]*Yem[0]);
 
  for (i=0;i<N;i++) t1_x_se[i]=Xse[i]+0.5*(k1_x_se[i]=step*f_x_se(x, Xse, i));
  for (i=0;i<N;i++) t2_x_se[i]=Xse[i]+0.5*(k2_x_se[i]=step*f_x_se(x+h, t1_x_se, i));
  for (i=0;i<N;i++) t3_x_se[i]=Xse[i]+ (k3_x_se[i]=step*f_x_se(x+h, t2_x_se, i));
  for (i=0;i<N;i++) k4_x_se[i]= step*f_x_se(x+step, t3_x_se, i);
  
  for (i=0;i<N;i++) Xse[i]+=(k1_x_se[i]+2*k2_x_se[i]+2*k3_x_se[i]+k4_x_se[i])/6.0;
}
 
double f_x_se(double x, double Xse[], int i)
{
const double G= 6.673*pow(10,-11); 
const double m_s= 1.989*pow(10,30); 
const double m_e=  5.972*pow(10,24); 
const double m_m=  7.347*pow(10,22);
const double m_j=  1.898*pow(10,27);
const double r_se= 149597870700;
const double r_sj= 778500000000;
const double r_em= 384400000;
const double v_se= 29786.21;
const double v_em= 1018.18;

  if (i==0) return(Xse[1]);
  if (i==1) return(-G*m_s*Xse[0]/(array_r_se[0]*array_r_se[0]*array_r_se[0]));
      
  if (i>1) exit(2);
}

// find y_se
void runge4_y_se(double x, double Yse[], double step)
{
  double h=step/2.0;           
  double t1_y_se[N], t2_y_se[N], t3_y_se[N],         
  k1_y_se[N], k2_y_se[N], k3_y_se[N],k4_y_se[N];    
  int i;
 
  for (i=0;i<N;i++) t1_y_se[i]=Yse[i]+0.5*(k1_y_se[i]=step*f_y_se(x, Yse, i));
  for (i=0;i<N;i++) t2_y_se[i]=Yse[i]+0.5*(k2_y_se[i]=step*f_y_se(x+h, t1_y_se, i));
  for (i=0;i<N;i++) t3_y_se[i]=Yse[i]+ (k3_y_se[i]=step*f_y_se(x+h, t2_y_se, i));
  for (i=0;i<N;i++) k4_y_se[i]= step*f_y_se(x+step, t3_y_se, i);
  
  for (i=0;i<N;i++) Yse[i]+=(k1_y_se[i]+2*k2_y_se[i]+2*k3_y_se[i]+k4_y_se[i])/6.0;
}
 
double f_y_se(double x, double Yse[], int i)
{
const double G= 6.673*pow(10,-11); 
const double m_s= 1.989*pow(10,30); 
const double m_e=  5.972*pow(10,24); 
const double m_m=  7.347*pow(10,22);
const double m_j=  1.898*pow(10,27);
const double r_se= 149597870700;
const double r_sj= 778500000000;
const double r_em= 384400000;
const double v_se= 29786.21;
const double v_em= 1018.18;  

  if (i==0) return(Yse[1]);
  if (i==1) return(-G*m_s*Yse[0]/(array_r_se[0]*array_r_se[0]*array_r_se[0]));
      
  if (i>1) exit(2);
}

// find x_em
void runge4_x_em(double x, double Xem[], double step)
{
  double h=step/2.0;           
  double t1_x_em[N], t2_x_em[N], t3_x_em[N],         
  k1_x_em[N], k2_x_em[N], k3_x_em[N],k4_x_em[N];    
  int i;
 
  for (i=0;i<N;i++) t1_x_em[i]=Xem[i]+0.5*(k1_x_em[i]=step*f_x_em(x, Xem, i));
  for (i=0;i<N;i++) t2_x_em[i]=Xem[i]+0.5*(k2_x_em[i]=step*f_x_em(x+h, t1_x_em, i));
  for (i=0;i<N;i++) t3_x_em[i]=Xem[i]+ (k3_x_em[i]=step*f_x_em(x+h, t2_x_em, i));
  for (i=0;i<N;i++) k4_x_em[i]= step*f_x_em(x+step, t3_x_em, i);
  
  for (i=0;i<N;i++) Xem[i]+=(k1_x_em[i]+2*k2_x_em[i]+2*k3_x_em[i]+k4_x_em[i])/6.0;
}
 
double f_x_em(double x, double Xem[], int i)
{
const double G= 6.673*pow(10,-11); 
const double m_s= 1.989*pow(10,30); 
const double m_e=  5.972*pow(10,24); 
const double m_m=  7.347*pow(10,22);
const double m_j=  1.898*pow(10,27);
const double r_se= 149597870700;
const double r_sj= 778500000000;
const double r_em= 384400000;
const double v_se= 29786.21;
const double v_em= 1018.18;

  if (i==0) return(Xem[1]);
  if (i==1) return(-G*m_e*Xem[0]/(array_r_em[0]*array_r_em[0]*array_r_em[0]));
      
  if (i>1) exit(2);
}

// find y_em
void runge4_y_em(double x, double Yem[], double step)
{
  double h=step/2.0;           
  double t1_y_em[N], t2_y_em[N], t3_y_em[N],         
  k1_y_em[N], k2_y_em[N], k3_y_em[N],k4_y_em[N];    
  int i;
 
  for (i=0;i<N;i++) t1_y_em[i]=Yem[i]+0.5*(k1_y_em[i]=step*f_y_em(x, Yem, i));
  for (i=0;i<N;i++) t2_y_em[i]=Yem[i]+0.5*(k2_y_em[i]=step*f_y_em(x+h, t1_y_em, i));
  for (i=0;i<N;i++) t3_y_em[i]=Yem[i]+ (k3_y_em[i]=step*f_y_em(x+h, t2_y_em, i));
  for (i=0;i<N;i++) k4_y_em[i]= step*f_y_em(x+step, t3_y_em, i);
  
  for (i=0;i<N;i++) Yem[i]+=(k1_y_em[i]+2*k2_y_em[i]+2*k3_y_em[i]+k4_y_em[i])/6.0;
}
 
double f_y_em(double x, double Yem[], int i)
{
const double G= 6.673*pow(10,-11); 
const double m_s= 1.989*pow(10,30); 
const double m_e=  5.972*pow(10,24); 
const double m_m=  7.347*pow(10,22);
const double m_j=  1.898*pow(10,27);
const double r_se= 149597870700;
const double r_sj= 778500000000;
const double r_em= 384400000;
const double v_se= 29786.21;
const double v_em= 1018.18;  

  if (i==0) return(Yem[1]);
  if (i==1) return(-G*m_e*Yem[0]/(array_r_em[0]*array_r_em[0]*array_r_em[0]));
      
  if (i>1) exit(2);
}


