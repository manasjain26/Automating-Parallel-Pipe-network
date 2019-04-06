#include<iostream>
#include<cmath>
#include <limits>
// library containing all mathematical functions like log etc.
using namespace std;
// all quantities are in their SI units
    double nu=0.000001; // kinematic viscosity
	int rho=1000; // density
	double pi=3.14159265359; 
	double g=9.81; // gravity

struct pipe
{
	double d;
	double l;
	double epsilon;

};
double reyno(double velocity, double diameter)
{
	return (velocity*diameter)/nu;
}
double head_loss_calc(double disc, double area, double rel_roughness, double dia, double length,int x)
{
	double velocity = disc/area;
	double reynolds_no = reyno(velocity,dia);
	double friction_factor = 1.1508804*pow(log((rel_roughness/3.7)+(5.74/pow(reynolds_no,0.9))),-2);
	cout<<"final friction factor of pipe "<<x<<" is "<<friction_factor<<endl;
	return (friction_factor*length*velocity*velocity/(2*g*dia));

}
double friction_factor_calculator(double hf,double rel_rough,double d,double len)
{

	int k=0;

	double temp1=0;
	double variable = std::numeric_limits<double>::infinity();
	for(double f=0.01;f<0.1;f=f+0.0000001)
	{
		double v=pow((2*hf*g*d)/(f*len),0.5);
		double re=v*d/nu;
		double temp=1.1508804*pow(log((rel_rough/3.7)+(5.74/pow(re,0.9))),-2);
		double variable1=abs(temp-f);

		if(variable1<variable)
		{
			variable =variable1;
			temp1=temp;
		}
		k++;
	}
	//cout<<variable<<endl<<"friction factor of other pipe is "<<temp1<<endl<<k<<endl;
	return temp1;
}

int main()
{
	
	int n; // no of parallel pipes
	cin>>n;
	double Q; // total discharge
	cin>>Q;
	pipe a[n];   // array of structure pipe corresponding to n no of pipes
	for(int i=0;i<n;i++)
	{
		cin>>a[i].d>>a[i].l>>a[i].epsilon;
	}
	
	double A[n],rel_roughness[n];
	for(int i=0;i<n;i++)
	{
		A[i]=(pi/4.0)*(a[i].d)*(a[i].d);
		rel_roughness[i]=a[i].epsilon/a[i].d;
	}
   
	double q[n],v[n],re[n],f[n],hf[n];
	double q1[n];
	q[0]=Q/n;
	 
	for(int i=0;i<20;i++)       // here we have iterated the discharge value 5 number of times (no of iterations can be increased also)
	{
      double qtotal=q[0];
	v[0]=q[0]/A[0];
	re[0]=reyno(v[0],a[0].d);
	f[0]=1.1508804*pow(log((rel_roughness[0]/3.7)+(5.74/pow(re[0],0.9))),-2);
	//cout<<"friction factor of pipe 1 "<<f[0]<<endl;

	hf[0]=(f[0]*(a[0].l)*v[0]*v[0])/(2*g*(a[0].d));
	
	for(int i=1;i<n;i++)
	{
		f[i]=friction_factor_calculator(hf[0],rel_roughness[i],a[i].d,a[i].l);
		v[i]=pow((2*hf[0]*g*a[i].d)/(f[i]*a[i].l),0.5);
		q[i]=A[i]*v[i];
		qtotal=qtotal+q[i];
	}
	

	for(int i=0;i<n;i++)
	{
		q1[i]=(q[i]*Q)/qtotal;
		//cout<<"Discharge in pipe "<<i+1<<" is "<<q1[i]<<endl;  // (this can be uncommented to see the variation in discharge values after each iteration)
	}
	q[0]=q1[0];
}
for(int i=0;i<n;i++)
	{
		
		cout<<"Discharge in pipe "<<i+1<<" is "<<q1[i]<<endl;
	}



	for(int i=0;i<n;i++)
	{
		cout<<"Head loss in pipe "<<i+1<<" is "<<head_loss_calc(q1[i],A[i],rel_roughness[i],a[i].d,a[i].l,i+1)<<endl;
	}

}