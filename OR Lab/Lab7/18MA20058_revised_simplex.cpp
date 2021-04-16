/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

int iter;

void makeTableau(vector<vector<double> > &A, vector<vector<double> > &B, vector<double> &expression, int rows, int columns, vector<vector<double> > &tableau)
{   // rows=m+3 , columns=n+m+4
    int n,i,j;
    n = columns-rows-1;  
    
    for(i=0;i<rows;i++)
      {
        for(j=0;j<columns;j++)
          {
            tableau[i][j] = 0;
          }
      }
	tableau[rows-1][columns-2]=0;
    for(j=2;j<n+2;j++)
      {
        tableau[0][j] = expression[j-2];            // Objective function coefficients in row 1
        tableau[rows-1][j] = -1*expression[j-2];    // Zj-Cj in row m+2
      }
    for(i=2;i<rows-1;i++)
      {
        tableau[i][1] = n+(i-1);           // Basic variables in column 2
      }
    for(i=2;i<columns-2;i++)
      {
        tableau[1][i] = i-1;               // All variables x1 to x(n+m) in row 2 
      }
      
    for(i=2;i<rows-1;i++)
      {
        for(j=2;j<columns-2;j++)
          {
            tableau[i][j] = A[i-2][j-2];
          }
        tableau[i][columns-2] = B[i-2][0];
      }
    cout<<endl;
}

void printTableau(vector<vector<double> > &tableau, int rows, int columns)
{
    int i,j;
    
    cout<<endl;
    for(i=0;i<columns;i++)
      cout<<"-----------";
    cout<<endl;

    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
          {
          	if(i==0)
          	  {
          	  	if(j==0 || j==columns-2)
          	  	  {
          	  	  	cout<<"         | ";
          	  	    continue;
				  }
				if(j==columns-1)
				  {
				  	cout<<"          | ";
          	  	    continue;
				  }
			  }
			if(i==rows-1 && (j==0))
			  {
			  	cout<<"         | ";
          	  	continue;
			  }
			if(i==rows-1 && (j==columns-1))
			  {
			  	cout<<"          | ";
          	  	continue;
			  }
          	if(i==1)
          	  {
          	  	if(j==0)
          	  	  {
          	  	  	cout<<"   Cb    | ";
				  }
				else if(j==1)
				  {
				  	cout<<"   Xb    | ";
				  }
				else if(j>=2 && j<columns-2)
				  {
				  	cout<<"   x"<<(int)tableau[i][j]<<"    | ";
				  }
				else if(j==columns-2)
				  {
				  	cout<<"   RHS   | ";
				  }
				else if(j==columns-1)
				  {
				  	cout<<"  Ratio   | ";
				  }
          	  	continue;
			  }
			
			if(j==1)
			  {
			  	if(i==0)
			  	  {
			  	  	cout<<"         | ";
				  }
			  	if(i>=2 && i<rows-1)
			  	  {
			  	  	cout<<"   x"<<(int)tableau[i][j]<<"    | ";
				  }
				else if(i==rows-1)
				  {
				  	cout<<"  Zj-Cj  | ";
				  }
				continue;
			  }
			
          	if(tableau[i][j]<10 && tableau[i][j]>=0)
        	  {
        	  	if(j==columns-1)
        	  	  cout<<fixed<<setprecision(6)<<tableau[i][j]<<"  | ";
        	  	else
        	  	  cout<<fixed<<setprecision(6)<<tableau[i][j]<<" | ";
			  }
        	else if((tableau[i][j]<100 && tableau[i][j]>=10)|| (tableau[i][j]<0 && tableau[i][j]>-10))
        	  {
        	  	if(j==columns-1)
        	  	  cout<<fixed<<setprecision(5)<<tableau[i][j]<<"  | ";
        	  	else
        	  	  cout<<fixed<<setprecision(5)<<tableau[i][j]<<" | ";
			  }
            else if((tableau[i][j]<1000 && tableau[i][j]>=100)|| (tableau[i][j]<=-10 && tableau[i][j]>-100))
              {
              	if(j==columns-1)
              	  cout<<fixed<<setprecision(4)<<tableau[i][j]<<"  | ";
              	else
              	  cout<<fixed<<setprecision(4)<<tableau[i][j]<<" | ";
			  }
            else if((tableau[i][j]<10000 && tableau[i][j]>=1000)|| (tableau[i][j]<=-100 && tableau[i][j]>-1000))
              {
              	if(j==columns-1)
              	  cout<<fixed<<setprecision(3)<<tableau[i][j]<<"  | ";
              	else
              	  cout<<fixed<<setprecision(3)<<tableau[i][j]<<" | ";
			  }
			else if((tableau[i][j]<100000 && tableau[i][j]>=10000)|| (tableau[i][j]<=-1000 && tableau[i][j]>-10000))
              {
              	if(j==columns-1)
              	  cout<<fixed<<setprecision(2)<<tableau[i][j]<<"  | ";
              	else
              	  cout<<fixed<<setprecision(2)<<tableau[i][j]<<" | ";
			  }
			else if((tableau[i][j]<1000000 && tableau[i][j]>=100000)|| (tableau[i][j]<=-10000 && tableau[i][j]>-100000))
              {
              	if(j==columns-1)
              	  cout<<fixed<<setprecision(1)<<tableau[i][j]<<"  | ";
              	else
              	  cout<<fixed<<setprecision(1)<<tableau[i][j]<<" | ";
			  }
            else if(tableau[i][j]==1000000)
              {
              	if(j==columns-1)
              	  cout<<"   inf    | ";
              	else
              	  cout<<"   inf   | ";
			  }
          }
        
        cout<<endl;
	    for(j=0;j<columns;j++)
	      cout<<"-----------";
	    cout<<endl;
    }
}

vector<vector<double> > MatrixMultiplication(vector<vector<double> > &M, vector<vector<double> > &N, int n)
{
  int i,j,k;
  vector<vector<double> > R(n,vector<double>(n));
  
  for(i=0;i<n;i++) 
    for(j=0;j<n;j++)
      {
		R[i][j]=0;
		for(k=0;k<n;k++)
		  R[i][j]+=M[i][k]*N[k][j];
      }
  return R;
}


void VectorMultiply(vector<double> &C, vector<vector<double> > &M, vector<double> &C1, int n)
{
  int i,j;
  for(i=0;i<n;i++)
    {
      C[i]=0;
      for(j=0;j<n;j++)
	    C[i]+=M[i][j]*C1[j];       // C = M*C1
    }
}

void ShowMat(vector<vector<double> > &A, int m, int n)
{
  int i,j;
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
        cout<<A[i][j]<<"\t";
	  cout<<endl;			
    }
}


void inverse(vector<vector<double> > &A, vector<vector<double> > &B, int n)    // function to calculate B = A_inv          
{
  vector<vector<double> > M(n,vector<double>(n)), E(n,vector<double>(n));
  vector<double> C(n),C1(n);
  double temp;
  int i,j;
  
  for(i=0;i<n;i++) 			       //E=M=I
    for(j=0;j<n;j++)
      if(i==j)
		{
		  E[i][j]=1;
		  M[i][j]=1;
		}
      else
		{
		  E[i][j]=0;
		  M[i][j]=0;
		}
		
  for(i=n-1;i>=0;i--)
    { 			                   
      for(j=0;j<n;j++)
	    C1[j]=A[j][i];	         // C1 = ith column of A          
	    
      VectorMultiply(C,M,C1,n);  // C = M*C1     Calculated e		
      temp=C[i];                 // temp = e_r	
				
      for(j=0;j<n;j++)
		{		                    
		  if(j==i) 
		    C[j]=1/temp;	
		  else 
		    C[j]=(-1)*(C[j]/temp);    // Calculated eta
		}
	
		
      for(j=0;j<n;j++)
		{			                
		  if(i!=n-1)
		    {
		      if((i+1)==j)
			    E[j][i+1]=1;
		      else
			    E[j][i+1]=0;
		    } 
		  E[j][i]=C[j];
		}
		
      M=MatrixMultiplication(E,M,n);
	  	
    }
    
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      B[i][j]=M[i][j];		
}


void Mult(vector<vector<double> > &R, vector<vector<double> > &A, vector<vector<double> > &B, int a, int b, int c)
{
  int i,j,k;
  for(i=0;i<a;i++)
    {
      for(j=0;j<c;j++)
		{                                    // R = AB
		  R[i][j]=0;                         
		  for(k=0;k<b;k++)
		    R[i][j]+=A[i][k]*B[k][j];
		}
    }
}

int Entering(vector<vector<double> > &A, vector<vector<double> > &M, vector<double> &Z, vector<int> &T, int m, int n)
{
  vector<vector<double> > Y(1,vector<double>(m)), Cb(1,vector<double>(m));
  int i,j;
  
  for(i=0;i<m;i++)
    Cb[0][i]=Z[T[i+n]];
  
  Mult(Y,Cb,M,1,m,m);
  double min=1;
  int index=-1;
  for(i=0;i<n;i++)
    {
      double sum=0;
      for(j=0;j<m;j++)
	    sum+=A[j][T[i]]*Y[0][j];
      sum-=Z[T[i]];
      if((sum<0)&&(sum<min))
		{
		  sum=min;
		  index=i;
		}
    }
  return index;
}

int Departing(vector<vector<double> > &A, vector<vector<double> > &B, vector<vector<double> > &M1, vector<vector<double> > &Xb, vector<int> &T, int m, int n, int e)
{
  int i;
  Mult(Xb,M1,B,m,m,1);
  vector<vector<double> > Alj(m,vector<double>(1)), Pj(m,vector<double>(1));
  
  for(i=0;i<m;i++)
    {
      Pj[i][0]=A[i][T[e]];
    }
  Mult(Alj,M1,Pj,m,m,1);
  int index=-1;
  double min=0,sum;
  for(i=0;i<m;i++)
    {
	    if((Alj[i][0]<=0) || (Xb[i][0]<=0))
	      continue;
	    else
	      {
			sum=Xb[i][0]/Alj[i][0];
			if((index==-1)||(sum<min))
			  {
			    min=sum;
			    index=i;
			  }
	      }
    }
  return index;
}

void Result(vector<double> &Z, vector<int> &T, vector<vector<double> > &Xb, int m, int n)
{
  double res=0;
  int i,j,f;
  
  for(i=0;i<m;i++)
    res+=Xb[i][0]*Z[T[n+i]];
  cout<<"\nOptimum Solution is Z = "<<fixed<<setprecision(5)<<res<<endl<<endl;
  cout<<"Occuring at the values : \n";
  for(i=0;i<n;i++)
    {
      f=0;
      cout<<"x["<<i+1<<"] = ";
      for(j=0; j<m; j++)
		if(T[n+j]==i)
		  {
		  	cout<<fixed<<setprecision(5)<<Xb[j][0]<<endl;
		    f=1;
		  }
      if(f==0)
        cout<<fixed<<setprecision(5)<<0.00000<<endl;
    }
}

void Revised_Simplex(vector<vector<double> > &A, vector<vector<double> > &B, vector<double> &Z, int m, int n, int it, int show)
{
  					
  vector<int> T(n+m);          // T= Vector storing positions of NBV and BV in order
  int i,j;
  for(i=0;i<n+m;i++)
    T[i]=i;
  vector<vector<double> > M(m,vector<double>(m)), M1(m,vector<double>(m)), Xb(m,vector<double>(1));    
  
  for(i=0;i<m;i++)
    for(j=0;j<m;j++)
      if(i==j)
	    M[i][j]=1;
      else
	    M[i][j]=0;
  
  iter=1;
  while(1)
    {

      inverse(M,M1,m);               // M1 = M^(-1)
     
      if(it!=-1)
        {
        	if(iter==it)
        	  {
        	  	cout<<"\nList of Basic variables for iteration "<<it<<" :\n";
        	  	for(i=n;i<n+m-1;i++)
        	  	  cout<<"x["<<T[i]+1<<"] , ";
        	  	cout<<"x["<<T[n+m-1]+1<<"]\n";
        	  	
        	  	cout<<"\nList of Non-Basic variables for iteration "<<it<<" :\n";
        	  	for(i=0;i<n-1;i++)
        	  	  cout<<"x["<<T[i]+1<<"] , ";
        	  	cout<<"x["<<T[n-1]+1<<"]\n";
        	  	
        	  	return;
			  }
		}
      
      int e;
      e=Entering(A,M1,Z,T,m,n);			
      if(e<0)
		{
		  Mult(Xb,M1,B,m,m,1);       // Xb = M1*B
		  if(show==1)
		    Result(Z,T,Xb,m,n);
		  return;
		}
		
      int d;
      d=Departing(A,B,M1,Xb,T,m,n,e);
      if(d<0)
		{
		  cout<<"\nInfeasible\n";
		  return;
		}
		
      for(i=0;i<m;i++)
	    M[i][d]=A[i][T[e]];
      d+=n;
      int temp;
      temp=T[d];
      T[d]=T[e];
      T[e]=temp;
      
      iter++;
    }
}

int main()
{
	
	int n,m,i,j;
	cout<<"Enter the number of variables : ";
	cin>>n;
	cout<<"\nEnter the number of constraints : ";
	cin>>m;
	  
	vector<double> Z(n+m);
	vector<vector<double> > A(m,vector<double>(n+m)), B(m,vector<double>(1)), tableau(m+3,vector<double> (n+m+4));
	  
	cout<<"\nEnter the coefficient matrix for constraints :\n\n";
	for(i=0;i<m;i++)
	  {
	    for(j=0;j<n;j++)
	      cin>>A[i][j];
	    for(j=n;j<n+m;j++)
	      {
	        if(j==(i+n))
	          A[i][j]=1;
	        else
	          A[i][j]=0;
		  }
	  }
	  
	cout<<"\nEnter the RHS vector for constraints :\n";
	for(i=0;i<m;i++)
	  cin>>B[i][0];
	  
	cout<<"\nEnter the coefficients of objective function :\n";
	for(i=0;i<n;i++)
	  {
		cin>>Z[i];
	  }
	for(i=n;i<n+m;i++)
	  Z[i]=0;
	
	bool check=false;
	for(i=0;i<m;i++)
	  if(B[i][0]<=0)
	    {
	    	check=true;
	    	break;
		}
	
	if(check)
	  {
	  	makeTableau(A,B,Z,m+3,n+m+4,tableau);
	    cout<<"\n\nInitial Tableau :\n\n";
	    printTableau(tableau,m+3,n+m+4);
	    cout<<endl<<endl;
	  	cout<<"\nThe LPP is unbounded !!\n";
	  	return 0;
	  }
	  
	while(1)
	  {
	  	cout<<"\n#########################################################################################################\n";
	    cout<<"\nNow, enter which option you want to see : \n";
	    cout<<"(1) Initial Tableau"<<endl;
	    cout<<"(2) List of basic and Non-basic variables for ith iteration"<<endl;
	    cout<<"(3) Optimal Solution"<<endl;
	    cout<<"(4) Nothing. Exit"<<endl;
	    cout<<"\n#########################################################################################################\n";
	    
	    int menu;
	    cin>>menu;
	    
	    if(menu==4)
	      {
	      	cout<<"\nExiting...\n";
	      	return 0;
		  }
	      
	    if(menu==1)
	      {
	      	makeTableau(A,B,Z,m+3,n+m+4,tableau);
	      	cout<<"\n\nInitial Tableau :\n\n";
	      	printTableau(tableau,m+3,n+m+4);
	      	cout<<endl<<endl;
	      	continue;
		  }
	    
	    if(menu==2)
	      {
	      	int it;
	      	cout<<"\nEnter the iteration number : ";
	      	cin>>it;
	      	Revised_Simplex(A,B,Z,m,n,-1,-1);
	      	if(it>iter)
	      	  cout<<"\nNo. of iterations required is = "<<iter<<"\nSo please enter an iteration number <= "<<iter<<endl;
	      	else 
	      	  Revised_Simplex(A,B,Z,m,n,it,-1);
	      	continue;
		  }
		
		if(menu==3)
		  {
		  	Revised_Simplex(A,B,Z,m,n,-1,1);
		  	continue;
		  }
		
		else
		  {
		  	cout<<"Invalid choice !!\n";
		  	continue;
		  }
	  }  
	  
	return 0;
}


