#include<stdio.h>
#include<math.h>
#include<iostream> 
#include<fstream>

#define true 1
#define false 0
#define MAX_N 2000

static   double F(double, double);

using namespace std;

int main()
{
      double A,B,ALPHA,H,T,W[MAX_N],K1,K2,K3,K4;
      int I,N;

      A = 0.0;
      B = 2.0;
      N = 100;

      cout.setf(ios::fixed,ios::floatfield);
      cout.precision(10);

      
      H = (B - A) / N;
      T = A;
      W[0] = 1.0;
     
      ofstream outFile("Adam.txt");
    
      for (I=1; I<=3; I++) 
      {
         
         K1 = H*F(T, W[I-1]);
         K2 = H*F(T + H/2.0, W[I-1] + K1/2.0);
         K3 = H*F(T + H/2.0, W[I-1] + K2/2.0);
         K4 = H*F(T + H, W[I-1] + K3);

         W[I] = W[I-1] + 1/6.0*(K1 + 2.0*K2 + 2.0*K3 + K4);

         
         T = A + I * H;

         
         cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
	 outFile<<T<<" "<<W[I]<<endl;
      }

//Adam-Bashforth 4-step
      for(I = 4; I <= N; I++)
      {
	
          K1 = 55.0*F(T, W[I-1]) - 59.0*F(T-H, W[I-2]) + 37.0*F(T-2.0*H, W[I-3]) - 9.0*F(T-3.0*H, W[I-4]);
          W[I] = W[I-1] + H/24.0*K1;
//Moulton method 
	  K2=9.0*F(T+H, W[I]) + 19.0*F(T, W[I-1]) - 5.0*F(T-H, W[I-2]) + F(T-2.0*H, W[I-3]);
	  W[I] = W[I-1] + H/24.0*K2;

          
        
          T = A + I * H;

       
          cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
	  outFile<<T<<" "<<W[I]<<endl;	
      }

	  outFile.close();

      return 0;
}

double F(double T, double Y)
{
   double f; 

   f = -Y;
   return f;
}


