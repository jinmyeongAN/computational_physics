#include "stdio.h"
#include "stdlib.h"
#include "math.h"

main()
{
	double u10=0,u20=0,u40=0,u60=0,u80=0,u90=0;
	int i,j;
	double pi=3.141592;
	double A1,A2,B;
	
	FILE *f10;
	f10=fopen("analytic10.txt","w");
	FILE *f20;
	f20=fopen("analytic20.txt","w");
	FILE *f40;
	f40=fopen("analytic40.txt","w");
	FILE *f60;
	f60=fopen("analytic60.txt","w");
	FILE *f80;
	f80=fopen("analytic80.txt","w");
	FILE *f90;
	f90=fopen("analytic90.txt","w");

	for(j=1;j<100;j++)	
	{			
		for(i=1;i<100;i++)
		{
			A1=(-20/(i*pi))*(cos(i*pi)-1)*exp(i*pi)-(cos(i*pi)-1)*10/(i*pi);
			A2=A1/(exp(2*i*pi)-1);
			B=(-20/pi)-A2;
			
			//the analytic u value of u[y][10]
			u10=u10+sin(10*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
			u20=u20+sin(20*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
			u40=u40+sin(40*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
			u60=u60+sin(60*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
			u80=u80+sin(80*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
			u90=u90+sin(90*i*pi/100)*(A2*exp(i*pi*j/100)+B*exp(-i*pi*j/100));
		}

		
		fprintf(f10,"%d %18.10f\n",j,u10);
		u10=0;
		fprintf(f20,"%d %18.10f\n",j,u20);
		u20=0;
		fprintf(f40,"%d %18.10f\n",j,u40);
		u40=0;
		fprintf(f60,"%d %18.10f\n",j,u60);
		u60=0;
		fprintf(f80,"%d %18.10f\n",j,u80);
		u80=0;
		fprintf(f90,"%d %18.10f\n",j,u90);
		u90=0;
	}
	fclose(f10);
	fclose(f20);
	fclose(f40);
	fclose(f60);
	fclose(f80);
	fclose(f90);
}

