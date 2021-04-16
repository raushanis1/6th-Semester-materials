/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

#define ERR 0.001

int n,m,i,j,k,flag;
double error;
vector<vector<double> > a;
vector<double> b,x;

vector<double> Gauss_seidel(vector<vector<double> > A, vector<double> X, vector<double> b)
{
	int t;
	
	vector<vector<double> > A_new(m,vector<double> (m+1));
	for(i=0;i<m;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  A_new[i][j]=A[i][j];
	  	A_new[i][m]=b[i];
	  }
	
	for(i=0;i<m;i++)
	  {
	  	double div=A_new[i][i];
	  	for(j=0;j<=m;j++)
	  	  A_new[i][j]/=div;
	  	
	  	for(j=i+1;j<m;j++)
	  	  {
	  	  	float mult=A_new[j][i]/A_new[i][i];
	  	  	for(k=i;k<=m;k++)
	  	  	  {
	  	  	  	A_new[j][k]=A_new[j][k] - (mult)*A_new[i][k];
			  }
		  }
	  }
	  
	for(i=0;i<m;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  {
	  	  	A[i][j]=A_new[i][j];
		  }
		b[i]=A_new[i][m];
	  }
	
	
	vector<double> Y(m);
	for(t=0;t<1000;t++)
	  {
	  	for(i=0;i<m;i++)
	  	  {
	  	  	Y[i]=b[i]/A[i][i];
	  	  	for(j=0;j<m;j++)
	  	  	  {
	  	  	  	if(j==i)
	  	  	  	  continue;
	  	  	  	Y[i]-=((A[i][j]/A[i][i])*X[j]);
			  }
			X[i]=Y[i];
		  }
	  }
	  
	return X;
}

int main()
{

	cout<<"Enter the number of variables and equations :\n";
	cin>>n>>m;
    cout<<fixed<<setprecision(5);
	
	a=vector<vector<double> > (m, vector<double> (n));
	b=vector<double> (m);
	x=vector<double> (n, 0);

	cout<<"\nEnter the coefficent matrix A :\n";    
	for(i=0;i<m;i++) 
	  for(j=0;j<n;j++) 
		cin>>a[i][j];
		 
	cout<<"\nEnter the RHS of all equations :\n";
	for(i=0;i<m;i++)
	  cin>>b[i];
	
	int mask,r,z,k;
	int count=0;
	for(mask=0;mask< (1 << n) ;mask++)
	  {
	  	if(__builtin_popcount(mask) != n-m)
		  continue;
		
		vector<vector<double> > A;
		
		for(i=0;i<m;i++) 
		  {
			vector<double> row;
			for(j=0;j<n;j++) 
			  {
				if(mask & (1 << j))
				  continue;
				else
				  row.push_back(a[i][j]);
			  }
			assert(row.size()== m);
			A.push_back(row);
		  }
		
		vector<double> X(m,0);
		X=Gauss_seidel(A,X,b);
		
		vector<double> sol;
		k=0;
		for(i=0;i<n;i++) 
		  {
			if(mask & (1<<i)) 
			  sol.push_back(0);
			
			else
			  {
			    sol.push_back(X[k]);
			    k++;
			  }
		  }
		  
		bool diverge = false;
		vector<double> b_ans(m, 0);
		for(i=0;i<m;i++) 
		  {
			for(j=0;j<n;j++) 
			  b_ans[i] += a[i][j]*sol[j];
			
			if(fabs(b_ans[i]-b[i]) > ERR)
			  diverge = true;
		  }
		  
		if (diverge) 
		  {
			continue;
		  }
		
		int flag=0;
		for(i=0;i<n;i++)
		  {
		  	if(sol[i]<0)
		  	  {
		  	  	flag=1;
		  	  	break;
			  }
		  }
		
		if(flag==0)
		  {
		  	count++;
		  	int check=0;
		  	for(i=0;i<n;i++)
		  	  {
		  	  	if(isnan(sol[i]))
		  	  	  {
		  	  	  	check=1;
		  	  	  	break;
				  }
			  }
			if(check==1)
			  continue;
			  
			cout<<"\nFeasible Basic Solution :\n";
		  	for(i=0;i<n;i++)
		  	  cout<<sol[i]<<" ";
		  	cout<<endl;
		  }
		
		else
		  {
		  	count++;
		  }
		
	  }
	
	if(count==0)
	  {
	  	cout<<"\nNo Basic Solution... All solutions diverge\n";
	  }
	
	return 0;
}
