#include <graphics.h>
#include <iostream>
#include <math.h>
#include <dos.h>
#include <time.h>
using namespace std;
int multi(float **, float *, float *);
int add(float *, float *, float *);
int identity(float **);
int inv(float **, int);
float det(float **, int);
float cofac(float **, int, int, int );
float cross(float *, float *, float *, int);
float cross(float *a, float *b, float *c, int d)
{
	int i, j;
	float m[4][4], *p[4], vec;
	for(i=0;i<4;i++)
	{
		p[i]=&m[i][0];
		m[1][i]=a[i];
		m[2][i]=b[i];
		m[3][i]=c[i];
	}
	vec=cofac(p, 0, d, 4);
	return vec;
}
int identity(float *trans[])
{
	int i, j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
			{
				trans[i][j]=1;
			}
			else
			{
				trans[i][j]=0;
			}
		}			
	}
}
int multi(float *trans[], float *vec, float *output)
{
	int i, j;
	for(i=0;i<4;i++)
	{
		output[i]=0;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			output[i]=output[i]+trans[i][j]*vec[j];
		}
	}
	return 0;
}
int add(float *m, float *n, float *p)
{
	int i;
	for(i=0;i<4;i++)
	{
		p[i]=m[i]+n[i];
	}
	return 0;
}
float cofac(float *m[], int a, int b, int size)
{
	int i, j, x=0, y=0;
	float n[3][3], k, *p[3];
	for(i=0;i<size;i++)
	{	
		y=0;
		if(i!=a)
		{
			p[x]=&n[x][0];
			for(j=0;j<size;j++)
			{
				if(j!=b)
				{
					//cout<<x<<y<<endl;
					//cout<<"Hey: "<<m[i][j]<<endl;
					n[x][y]=m[i][j];
					y=y+1;
				}
			}
			x=x+1;
		}
	}
	if((a+b)%2==0)
	{
		if(size==3)
		{
			k=(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
			return k;
		}
		k=det(p, size-1);
		return k;
	}
	else
	{
		if(size==3)
		{
			k=-(n[0][0]*n[1][1]-n[0][1]*n[1][0]);
			return k;
		}
		k=-det(p, size-1);
		return k;
	}
}
float det(float *m[], int size)
{
	int i, j;
	float k;
	k=0;
	for(j=0;j<size;j++)
	{
		k=k+m[0][j]*cofac(m, 0, j, size);
	}
	return k;
}
int inv(float *m[], int size)
{
	int i, j;
	float cof[4][4], de;
	de=det(m, size);
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			cof[j][i]=cofac(m, i, j, size);
		}
	}
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			m[i][j]=cof[i][j]/de;
		}
	}
	return 0;
}
int main()
{
	srand(time(0));
	float matrix[4][4], a[4], b[4], c[4];
	float *p1[4], *p2, *p3, *p4;
	int i, j;
	p2=&a[0];
	p3=&b[0];
	p4=&c[0];
	cout<<"Matrix taken in: "<<endl;
	for(i=0;i<4;i++)
	{
		a[i]=rand()%10;
		b[i]=rand()%10;
		c[i]=rand()%10;
		p1[i]=&matrix[i][0];
		for(j=0;j<4;j++)
		{
			matrix[i][j]=rand()%10;
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"Your cofactor matrix"<<endl;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<cofac(p1, i, j, 4)<<"\t";
		}
		cout<<endl;
	}
	cout<<"Your determinant is: "<<det(p1, 4)<<endl;;
	inv(p1, 4);
	cout<<"Your inverse here dude:"<<endl;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<"Vectors Program took in: "<<endl;
	for(i=0;i<4;i++)
	{
		cout<<"Vector 1: component "<<i+1<<" : "<<a[i]<<endl;
	}
	for(i=0;i<4;i++)
	{
		cout<<"Vector 2: component "<<i+1<<" : "<<b[i]<<endl;
	}
	for(i=0;i<4;i++)
	{
		cout<<"Vector 3: component "<<i+1<<" : "<<c[i]<<endl;
	}
	cout<<"Behold... the cross product! (sort of a lie...)"<<endl;
	for(i=0;i<4;i++)
	{
		cout<<"Component "<<i+1<<" : "<<cross(p2, p3, p4, i)<<endl;
	}
}
