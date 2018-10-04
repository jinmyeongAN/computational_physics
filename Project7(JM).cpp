#include <fstream>
#include <iostream>
#include <math.h>
#include <cmath>
#include <sstream>

using namespace std;


double f(double x)
{
	return exp(-x*x)/sqrt(3.141592);
}

void F_make(double u[],double F[])
{
	for(int i=0;i<100;i++)//about delta_x	
	{
		F[i]=1*u[i];
	}
}

void ftcs(double u[],double arr[])// the function of ftcs
{
	ofstream File("1graph2_3.txt",ios::app);

	int i;
	arr[0]=u[0];
	arr[99]=u[99];

	for(i=1;i<100-1;i++)//about delta_x
	{
		double first=u[i+1]-u[i-1];
		double second=-1*0.05/(2*0.1);//about delta_x and delta_y
		arr[i]= u[i]+first*second;
		
		File<<-5+i*0.1<<" "<<arr[i]<<endl;//about delta_x
	}

	File.close();
	
	for(int j=0;j<100;j++)//about delta_x
	{	
	swap(u[j],arr[j]);//for repeatation
	}

}

void tslwm(double u[],double arr2[],double arr3[],double F[])// the function of tslwm
{
	ofstream File2("2graph2_3.txt",ios::app);

	for(int i=0;i<100-1;i++)//about delta_x	
	{	
		arr2[i]=(u[i+1]+u[i])/2-(F[i+1]-F[i])*0.05/(2*0.1);//delta_t and delta_x
	}
	arr2[99]=u[99];//delta

	F_make(arr2,F);
	arr3[0]=u[0];

	for(int j=1;j<100;j++)//about delta_x
	{
		arr3[j]=u[j]-(F[j]-F[j-1])*0.05/0.1;//about delta_t and delta_x

		File2<<-5+j*0.1<<" "<<arr3[j]<<endl;//about delta_x
	}
	
	File2.close();
	
	for(int k=0;k<100;k++)//about delta_x
	{	
	swap(u[k],arr3[k]);//for repeatation
	}

	


	
	/*ofstream File2("test6.txt",ios::app);

	arr2[0]=u[0];
	arr2[999]=u[999];
	
	double a=1*0.1/0.01;//delta_t and delta_x

	for(int i=1;i<1000-1;i++)//about delta_x
	{
		double b,c,d,e;
		b=(u[i+1]+u[i])/2;
		c=a*(u[i+1]-u[i])/2;
		d=(u[i]+u[i-1])/2;
		e=a*(u[i]-u[i-1])/2;
		//arr2[i]=u[i]-a*((u[i+1]+u[i])/2-a*(u[i+1]-u[i])/2-(u[i]+u[i-1])/2+a*(u[i]-u[i-1])/2);

		arr2[i]=u[i]-(b-c-d+e)*a;
		File2<<-5+i*0.01<<" "<<arr2[i]<<endl;//about delta_x
	
	}
	
	File2.close();

	for(int j=0;j<1000;j++)//about delta_x
	{	
	swap(u[j],arr2[j]);//for repeatation
	}
	*/

}

int main()
{
	double x_0=-5,t_0=0,v=1,delta_x=0.1,delta_t=0.05;
	int d=2000; //about delta_x
	double u[d];//array u[]
	double arr[d];//the array for repeatation(ftcs)
	double arr2[d];//the array of repeatation(tslwm)
	double arr3[d];//the array (tslwm)
	double F[d];//the array (tslwm)
	ofstream outFile("1graph2_3.txt");
	for(int j=0;j<10/delta_x;j++)
	{
		u[j]=f(x_0+j*delta_x);//assign initial value		
		
		outFile<<-5+j*delta_x<<" "<<u[j]<<endl;//insert to the txt file
	}
	outFile.close();

	
	int k;
	for(k=0;k<5;k++)//time step
	{
		ftcs(u,arr);
	}

	ofstream outFile2("2graph2_3.txt");
	for(int j=0;j<10/delta_x;j++)
	{
		u[j]=f(x_0+j*delta_x);//assign initial value		
		
		outFile2<<-5+j*delta_x<<" "<<u[j]<<endl;//insert to the txt file
	}
	outFile2.close();	

	int l;
	
	F_make(u,F);
	for(l=0;l<5;l++)//time step
	{
		tslwm(u,arr2,arr3,F);
	}

}
