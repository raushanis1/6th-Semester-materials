/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

#define ERR 0.00001

int main()
{
	int n,i,j;
	double a[100][100],b[100],x[100],y[100],error;
	
	cout<<"Enter the no. of equations/variables :\n";
	cin>>n;
	cout<<"\nEnter the coefficient matrix :\n";
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<n;j++)
	  	  {
	  	  	cin>>a[i][j];
		  }
	  }
	
	cout<<"\nEnter the RHS values of equations :\n";
	for(i=0;i<n;i++)
	  {
	  	cin>>b[i];
	  	x[i]=0;
	  }
    
    double div=1e8;
    int flag=0;
    do
      {
      	error=0;
      	for(i=0;i<n;i++)
      	  {
      	  	y[i]=b[i]/a[i][i];
      	  	for(j=0;j<n;j++)
      	  	  {
      	  	  	if(j!=i)
      	  	  	  {
      	  	  	  	y[i]-=((a[i][j]/a[i][i])*x[j]);
				  }
			  }
	
			error=max(error,fabs(y[i]-x[i]));
			if(error>div)
			  {
			  	cout<<"Divergent system of equations\n";
			  	flag=1;
			  	break;
			  }
			
			div=error;
			x[i]=y[i];
			cout<<fixed<<setprecision(5)<<x[i]<<"  ";
		  }
		cout<<endl;
		if(flag==1)
		  break;
	  }while(error>ERR);
	
	return 0;
}
