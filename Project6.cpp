#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <memory>
#include <functional>
#include <fstream>

using namespace std;

void four1(double *data, const int n, const int isign) {
	int nn,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
	if (n<2 || n&(n-1)) throw("n must be power of 2 in four1");
	nn = n << 1;
	j = 1;
	for (i=1;i<nn;i+=2) {
		if (j > i) {
			swap(data[j-1],data[i-1]);
			swap(data[j],data[i]);
		}
		m=n;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax=2;
	while (nn > mmax) {
		istep=mmax << 1;
		theta=isign*(6.28318530717959/mmax);
		wtemp=sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi=sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=nn;i+=istep) {
				j=i+mmax;
				tempr=wr*data[j-1]-wi*data[j];
				tempi=wr*data[j]+wi*data[j-1];
				data[j-1]=data[i-1]-tempr;
				data[j]=data[i]-tempi;
				data[i-1] += tempr;
				data[i] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;
	}
}

void four1(vector<double> &data, const int isign) {
	four1(&data[0],data.size()/2,isign);
}

void realft(vector<double> &data, const int isign) {
	int i,i1,i2,i3,i4,n=data.size();
	double c1=0.5,c2,h1r,h1i,h2r,h2i,wr,wi,wpr,wpi,wtemp;
	double theta=3.141592653589793238/double(n>>1);
	if (isign == 1) {
		c2 = -0.5;
		four1(data,1);
	} else {
		c2=0.5;
		theta = -theta;
	}
	wtemp=sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi=sin(theta);
	wr=1.0+wpr;
	wi=wpi;
	for (i=1;i<(n>>2);i++) {
		i2=1+(i1=i+i);
		i4=1+(i3=n-i1);
		h1r=c1*(data[i1]+data[i3]);
		h1i=c1*(data[i2]-data[i4]);
		h2r= -c2*(data[i2]+data[i4]);
		h2i=c2*(data[i1]-data[i3]);
		data[i1]=h1r+wr*h2r-wi*h2i;
		data[i2]=h1i+wr*h2i+wi*h2r;
		data[i3]=h1r-wr*h2r+wi*h2i;
		data[i4]= -h1i+wr*h2i+wi*h2r;
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
	}
	if (isign == 1) {
		data[0] = (h1r=data[0])+data[1];
		data[1] = h1r-data[1];
	} else {
		data[0]=c1*((h1r=data[0])+data[1]);
		data[1]=c1*(h1r-data[1]);
		four1(data,-1);
	}
}

int main(void)
{
	ofstream File("test.txt");	


	double i,j,k;
	double N,s;
	cout<<"N: "<<endl;
	cin>>N;
	cout<<"d="<<20/(N-1)<<endl;
	cout<<"s: "<<endl;
	cin>>s;
	vector<double> arr(N);
	vector<double> f(N);
	
	for(i=0;i<N;i++)
	{
		arr[i]=exp(-20*20*i*i/(N-1)/(N-1)/(s*s))*sin(i*20/(N-1));
		cout<<"test, exp: "<<exp(-20*20*i*i/255/255/100)<<endl;
		cout<<"exp: "<<exp(-20*20*i*i/(N-1)/(N-1)/(s*s))<<endl;
		cout<<"sin: "<<sin(i*20/(N-1))<<endl;
		cout<<arr[i]<<endl;
	} 

	realft(arr,1);

	for(k=0;k<N;k++)
	{
		cout<<"realft: "<<k<<": "<<arr[k]<<endl;
	} 

	for(j=0;j<N;j++)
	{
		if(j<N/2+1)
		{
			f[j]=j/(N*20*2/(N-1)); //to connect arr[] and f[] properly, muliply 2
			File<<f[j]<<" "<<arr[j]<<endl;
		}		
		
		else
		{
			f[j]=(j-N)/(N*20*2/(N-1)); //to connect arr[] and f[] properly, muliply 2
			File<<f[j]<<" "<<arr[j]<<endl;
		}
	}

	File.close();
	
}

