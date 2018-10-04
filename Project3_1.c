#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

int f(int col,int row,int**A)
{	int i,j;
	int sum=0;
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			A[i][j]=(i+1)*(i+1)+(j+1)*(j+1)-(i+1)*(j+1);
			sum=sum+A[i][j];
			
		}
		
	}
	return sum;
}

int main()
{
	
	int **arr;
	int m,n;
	int i,j,answer;

	scanf("%d %d",&m,&n);

	arr=(int **)malloc(m*sizeof(int *));
	
	for(i=0;i<m;i++)
	{
		arr[i]=(int *)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
		{
			arr[i][j]=0;
		}
		
	}
	
	int summation=f(n,m,arr);
	FILE *in;
	in=fopen("array.txt","w");
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(in,"%d ",arr[i][j]);
		}
		fprintf(in,"\n");
	}
	fprintf(in,"Sum= %d",summation);
	fclose(in);
		
}


