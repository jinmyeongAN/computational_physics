#include<stdio.h>
#include<math.h>

float fun(float x,float y)
{
    float f;
    f=-cos(x);
    return f;
}
main()
{
    FILE *f;
    f=fopen("Euler.txt","w");
    float a,b,c,x,x2,y,y2,h,t,k,k2;
    printf("\nEnter x0,y00,y0,h,xn: ");
    scanf("%f%f%f%f%f",&a,&b,&c,&h,&t);
    x=a;
    y=b;
    y2=c;
    printf("\n  x\t  y\n");
    while(x<=t)
    {
        k=h*fun(x,y);
        y=y+k;

	k2=h*y;
	y2=y2+k2;

        x=x+h;
	x2=x+h;
	printf("%f %f %f %f\n",x,y,x2,y2);
        fprintf(f,"%0.3f\t%0.3f\n",x2,y2);
    }
    fclose(f);
}
