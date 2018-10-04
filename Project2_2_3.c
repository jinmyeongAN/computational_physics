#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void f1(int C[][3],int D[][3])
{
	int E[3][3]={0,};
	int i,j,k,l=0;
	for(i=0;i<3;i++)
	{
		for(k=0;k<3;k++)
		{
			
			for(j=0;j<3;j++)
			{
				l+=C[i][j]*D[j][k];
			}
			E[i][k]=l;	
			l=0;	
			printf("%d ",E[i][k]);
		}
		printf("\n");
	}
	printf("is AB.\n");
}

void f2(int C[][3],int D[][3])
{
	int E[3][3]={0,};
	int i,j,k,l=0;
	for(i=0;i<3;i++)
	{
		for(k=0;k<3;k++)
		{
			
			for(j=0;j<3;j++)
			{
				l+=D[i][j]*C[j][k];
			}
			E[i][k]=l;	
			l=0;	
			printf("%d ",E[i][k]);
		}
		printf("\n");
	}
	printf("is BA.");
}


int main()
{
	int A[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	int B[3][3]={{2,3,4},{5,6,7},{8,9,10}};

	f1(A,B);
	f2(A,B);

	return 0;
}


