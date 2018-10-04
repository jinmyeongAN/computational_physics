/*
*    Adams-Bashforth four-step explicit Multistep method.
*    RUNGE-KUTTA (ORDER 4) ALGORITHM is used to compute w1 
*
*    TO APPROXIMATE THE SOLUTION TO THE INITIAL VALUE PROBLEM:
*               Y' = F(T,Y), A<=T<=B, Y(A) = ALPHA,
*    AT (N+1) EQUALLY SPACED NUMBERS IN THE INTERVAL [A,B].
*
*    INPUT:   ENDPOINTS A,B; INITIAL CONDITION ALPHA; INTEGER N.
*
*    OUTPUT:  APPROXIMATION W TO Y AT THE (N+1) VALUES OF T.
*/

#include<stdio.h>
#include<math.h>
#include<iostream> 

#define true 1
#define false 0
#define MAX_N 2000

static   double F(double, double);

using namespace std;

int main()
{
      double A,B,ALPHA,H,T,W[MAX_N], K1,K2,K3,K4;
      int I,N;

      A = 0.0;
      B = 2.0;
      N = 10;

      cout.setf(ios::fixed,ios::floatfield);
      cout.precision(10);

      /* STEP 1 */
      H = (B - A) / N;
      T = A;
      W[0] = 1.0; // initial value

      /* STEP 2 --- Use order 4 RK method to get w1, w2, w3 */
      /// NOTE: The "for" loop starts with I = 1. 
      for (I=1; I<=3; I++) 
      {
         /* STEP 3 */
         /* Compute K1, K2 RESP. */
         K1 = H*F(T, W[I-1]);
         K2 = H*F(T + H/2.0, W[I-1] + K1/2.0);
         K3 = H*F(T + H/2.0, W[I-1] + K2/2.0);
         K4 = H*F(T + H, W[I-1] + K3);

         /* STEP 4 */
         /* COMPUTE W(I) */
         W[I] = W[I-1] + 1/6.0*(K1 + 2.0*K2 + 2.0*K3 + K4);

         /* COMPUTE T(I) */ 
         T = A + I * H;

         /* STEP 5 */
         cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
      }

      /* STEP 6---Use Adam-Bashforth 4-step explicit method */
      for(I = 4; I <= N; I++)
      {
          K1 = 55.0*F(T, W[I-1]) - 59.0*F(T-H, W[I-2]) + 37.0*F(T-2.0*H, W[I-3]) - 9.0*F(T-3.0*H, W[I-4]);
          W[I] = W[I-1] + H/24.0*K1;

          /* COMPUTE T(I) */ 
          T = A + I * H;

          /* STEP 7 */
          cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
      }

      return 0;
}
/*  Change function F for a new problem   */
double F(double T, double Y)
{
   double f; 

   f = exp(-T)-2Y;
   return f;
}


