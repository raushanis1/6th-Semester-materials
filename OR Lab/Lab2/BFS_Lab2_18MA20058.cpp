/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

#define ERR 0.001

vector<double> Gauss_seidel(vector<vector<double> > A, vector<double> X, vector<double> b)
{
	int t,i,j,k;
	int m=X.size();
	
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

void solve(vector<vector<double> > a, vector<double> b, vector<double> expression,int m, int n,int ch)
{
	int i,j,flag,mask,r,z,k;
	int count=0;
	double ans=-1*1e8;
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
			  
			cout<<"\nBasic Feasible Solution :\n";
		  	for(i=0;i<n;i++)
		  	  cout<<sol[i]<<" ";
		  	cout<<endl;
		  	
		  	double val=0;
		  	for(i=0;i<n-m;i++)
		  	  val+=expression[i]*sol[i];
		  	  
		  	if(ch==1)
		  	  cout<<"Value of Z at this point = "<<val<<endl<<endl;
		  	else if(ch==2)
		  	  cout<<"Value of Z at this point = "<<-1*val<<endl<<endl;
		  	ans=max(ans,val);
		  }
		
		else
		  {
		  	count++;
		  }
		
	  }
	
	if(ch==1)
	  cout<<"Optimum value of Z = "<<ans<<endl;
	else
	  cout<<"Optimum value of Z = "<<-1*ans<<endl;
	
	if(count==0)
	  {
	  	cout<<"\nNo Basic Solution... All solutions diverge\n";
	  }
}

int main()
{
	int n,m,i,j;
	cout<<"Enter the number of variables: ";
	cin>>n;
	cout<<"Enter the number of constraint equations: ";
	cin>>m;
    cout<<fixed<<setprecision(5);
	vector<vector<double> > A(m,vector<double> (n+m));
	vector<double> B(m),sign(m),expression(n);
	
	cout<<"Enter coefficient matrix for constraints : \n\n";
    for(i=0;i<m;i++)
      for(j=0;j<n;j++)
        cin>>A[i][j];
    
    cout<<"Enter the signs of each constraint. \nEnter 1 if it is <= type, and 2 if it is >= type : \n";
    for(i=0;i<m;i++)
      cin>>sign[i];
    
    cout<<"Enter the RHS vector for constraints :\n";
    for(i=0;i<m;i++)
	  cin>>B[i];
    
    for(i=0;i<m;i++)
      {
      	if(sign[i]==2)
      	  {
      	  	for(j=0;j<n;j++)
      	  	  {
      	  	  	A[i][j]=-1*A[i][j];
			  }
			B[i]=-1*B[i];
		  }
	  }
	
	for(i=0;i<m;i++)            //adding slack variables
      {    
        for(j=n;j<n+m;j++)
          {
            A[i][j]=0;
          }
        A[i][i+n]=1;
      }
    
    cout<<"Enter the coefficients of objective function :\n";
    for(i=0;i<n;i++)
      {
        cin>>expression[i];
      }
    int ch;
    cout<<"Enter 1 if it is a maximization problem, and enter 2 if it is a minimization problem : ";
    cin>>ch;
    if(ch==2)
      {
      	for(i=0;i<n;i++)
      	  expression[i]=-1*expression[i];
	  }
	
	solve(A,B,expression,m,n+m,ch);
	
	return 0;	
}
