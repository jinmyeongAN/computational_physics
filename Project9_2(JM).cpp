#include <iostream>
#include <cmath>
using namespace std;

#define pi 3.141592653589793238

float max2(int, float**, int&, int&);
bool check(int, float**);

int main()
{
	
	float** A = new float*[3];
	float** X = new float*[3];
	int n=3;
	int r, s;
	float theta, buf, buf1, buf2, buf3;

	for(int i = 0; i < 3; i++)
		A[i] = new float[3];
	A[0][0]=1;
	A[1][0]=2;
	A[2][0]=-1;
	A[0][1]=2;
	A[1][1]=-3;
	A[2][1]=5;
	A[0][2]=-1;
	A[1][2]=5;
	A[2][2]=-1;
	
	


	for(int i = 0; i < n; i++)
	{
		X[i] = new float[n];
		for(int j = 0; j < n; j++)
		{
			if(i == j)
				X[i][j] = 1;
			else
				X[i][j] = 0;
		}
	}


	while(1)
	{
		if(max2(n, A, r, s) < 0.01F)
			break;
		if(A[r][r] == A[s][s])
			theta = pi/4;
		else
			theta = atan(2*A[r][s]/(A[r][r] - A[s][s]))/2;
		buf1 = A[r][r];
		buf2 = A[s][s];
		buf3 = A[r][s];
		for(int i = 0; i < n; i++)
		{
			if(i == r)
			{
				A[r][r] = buf1*pow(cos(theta), 2) + buf2*pow(sin(theta), 2) + 2*buf3*cos(theta)*sin(theta);
				A[r][s] = 0;
				A[s][r] = 0;
			}
			else if(i == s)
				A[s][s] = buf1*pow(sin(theta), 2) + buf2*pow(cos(theta), 2) - 2*buf3*cos(theta)*sin(theta);
			else
			{
				buf = A[i][r];
				A[i][r] = A[i][r]*cos(theta) + A[i][s]*sin(theta);
				A[r][i] = A[i][r];
				A[i][s] = A[i][s]*cos(theta) - buf*sin(theta);
				A[s][i] = A[i][s];
			}
		}
		for(int i = 0; i < n; i++)
		{
			buf = X[i][r];
			X[i][r] = X[i][r]*cos(theta) + X[i][s]*sin(theta);
			X[i][s] = X[i][s]*cos(theta) - buf*sin(theta);
		}
	}

	for(int i = 0; i < n; i++)
		cout << "I" << i + 1 << " = " << A[i][i] << "\t";

	cout << endl;
	
	for(int i = 0; i < n; i++)
	{
		cout << "X" << i + 1 << " = (" << X[0][i];
		
		for(int j = 1; j < n; j++)
			cout << ", " << X[j][i];

		cout << ")  ";
	}

	cout << endl;

	return 0;
}

bool check(int size, float** mat)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(mat[i][j] != mat[j][i])
				return false;
		}
	}
	return true;
}

float max2(int size, float** mat, int &r, int &s)
{
	float max = fabs(mat[0][1]);
	r = 0;
	s = 1;
	for(int i = 0; i < size; i++)
	{
		for(int j = i + 1; j < size; j++)
		{
			if(max < fabs(mat[i][j]))
			{
				max = fabs(mat[i][j]);
				r = i;
				s = j;
			}
		}
	}
	return max;
}







