/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

#define ERR 0.001
double tolerance=0.000000001;
int unbounded=0, t=0;

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
	cout<<"\n\nList of all Basic Feasible Solutions is : \n";
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
		  	  
		  	ans=max(ans,val);
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
}

void standard_form(vector<vector<double> > A, vector<double> B, vector<double> expression, int m, int n, double d)
{
	int i,j;
	cout<<fixed<<setprecision(2);
	cout<<"\n\nProblem in standard form is : \n";
	cout<<"Maximize Z = ";
	for(i=0;i<n-1;i++)
      {
        cout<<expression[i]<<"x"<<i+1<<" + ";
      }
    cout<<expression[n-1]<<"x"<<n<<" + "<<d;
    cout<<"\n\nSubject to equations : \n";
    for(i=0;i<m;i++)
      {
      	for(j=0;j<n+m-1;j++)
      	  {
      	  	cout<<A[i][j]<<"x"<<j+1<<" + ";
		  }
		cout<<A[i][j]<<"x"<<j+1;
		cout<<" = "<<B[i];
		cout<<endl;
	  }
	
}

void makeTableau(vector<vector<double> > &A, vector<double> &B, vector<double> &expression, int rows, int columns, vector<vector<double> > &tableau, double d)
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
	tableau[rows-1][columns-2]=d;
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
        tableau[i][columns-2] = B[i-2];
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


void applySimplex(vector<vector<double> > &tableau, vector<double> &expression, int rows, int columns, double d, int nb_it, int b_it, int tab_it)
{
    int i,j,n,m,idx1,idx2;
    n = columns-rows-1;
    m = columns-n-4;
    double minNeg,minRatio,pivot,div;
    while(1)
      {         
        minNeg = 0;
        for(i=2;i<columns-2;i++)
          {
            if(tableau[m+2][i]<minNeg)
              {
                minNeg = tableau[m+2][i];
                idx2 = i;                    // Pivot column index
              }
          }
        
        for(i=2;i<rows-1;i++)
          {
          	if(tableau[i][idx2]==0)
          	  {
          	  	tableau[i][columns-1]=1000000;
			  }
			else
			  {
			  	tableau[i][columns-1]=tableau[i][columns-2]/tableau[i][idx2];
			  }
		  }
		
		if(tab_it != -1 && tab_it==t)
		  {
		  	cout<<"\nTABLEAU AFTER ITERATION "<<t<<" :\n";
            printTableau(tableau,rows,columns);
            return;
		  }
		if(b_it != -1 && b_it==t)
		  {
		  	cout<<"\nLIST OF BASIC VARIABLES AND MIN RATIOS AFTER ITERATION "<<t<<" :\n\n";
		  	cout<<"  Xb  |  Ratios |\n";
		  	cout<<"-----------------\n";
		  	for(i=2;i<rows-1;i++)
		  	  {
		  	  	j=columns-1;
		  	  	if(tableau[i][j]<10 && tableau[i][j]>=0)
		  	  	  cout<<"  x"<<(int)tableau[i][1]<<"  | "<<fixed<<setprecision(4)<<tableau[i][columns-1]<<"  |\n";
		  	  	else if((tableau[i][j]<100 && tableau[i][j]>=10)|| (tableau[i][j]<0 && tableau[i][j]>-10))
		  	  	  cout<<"  x"<<(int)tableau[i][1]<<"  | "<<fixed<<setprecision(3)<<tableau[i][columns-1]<<"  |\n";
		  	  	else if((tableau[i][j]<1000 && tableau[i][j]>=100)|| (tableau[i][j]<=-10 && tableau[i][j]>-100))
		  	  	  cout<<"  x"<<(int)tableau[i][1]<<"  | "<<fixed<<setprecision(2)<<tableau[i][columns-1]<<"  |\n";
		  	  	else if((tableau[i][j]<10000 && tableau[i][j]>=1000)|| (tableau[i][j]<=-100 && tableau[i][j]>-10000))
		  	  	  cout<<"  x"<<(int)tableau[i][1]<<"  | "<<fixed<<setprecision(1)<<tableau[i][columns-1]<<"  |\n";
		  	  	else if(tableau[i][j]==1000000)
		  	  	  cout<<"  x"<<(int)tableau[i][1]<<"  | "<<"  inf   |\n";
		  	  	cout<<"-----------------\n";
			  }
			double ans=1000000;
			for(i=2;i<rows-1;i++)
              if(tableau[i][columns-1] >= 0 && tableau[i][columns-1] < ans)
              	ans = tableau[i][columns-1];  
			  
			cout<<"\nMinimum Ratio = "<<ans<<endl;
			return;
		  }
		if(nb_it!=-1 && nb_it==t)
		  {
		  	cout<<"\nLIST OF NON-BASIC VARIABLES AND NET EVALUATIONS AFTER ITERATION "<<t<<" :\n";
		  	cout<<"Xnb : ";
		  	for(i=2;i<columns-2;i++)
		  	  {
		  	  	int f=0;
		  	  	for(j=2;j<rows-1;j++)
		  	  	  {
		  	  	  	if(tableau[j][1]==tableau[1][i])
		  	  	  	  {
		  	  	  	  	f=1;
		  	  	  	  	break;
					  }
				  }
				if(f==0)
				  {
				  	cout<<"x"<<(int)tableau[1][i]<<"  ";
				  }
			  }
			
			cout<<"\nZj-Cj : ";
			for(i=2;i<columns-3;i++)
			  {
			  	cout<<tableau[rows-1][i]<<" , ";
			  }
			cout<<tableau[rows-1][i]<<endl;
			return;
		  }
		  
		/*cout<<"\nTABLEAU AFTER ITERATION "<<t<<" :\n";
        printTableau(tableau,rows,columns);*/

        if(fabs(minNeg) < tolerance) 
		  { 
		    //cout<<"\nNothing more to optimize ...\n";
		    break;                                      // Nothing more to optimize 
		  }
		  
        for(i=2;i<rows-1;i++)
          {
            if(tableau[i][idx2] > 0) 
			  break;
          }
        
        if(i==rows)            //unbounded
          {
            unbounded = 1;
            break;
          }
        
		else
		  { 
            minRatio = 1000000;
            
            for(i=2;i<rows-1;i++)
              {
              	if(tableau[i][columns-1] >= 0 && tableau[i][columns-1] < minRatio)
              	  {
              	  	minRatio = tableau[i][columns-1];
              	  	idx1 = i;
				  }
			  }

            pivot = tableau[idx1][idx2];
            
            /*cout<<"\nMinimum ratio in iteration "<<t<<" = "<<fixed<<setprecision(3)<<minRatio<<endl;
            cout<<"Pivot element in iteration "<<t<<" = "<<fixed<<setprecision(3)<<pivot<<endl;
            cout<<"Pivot row = Row "<<idx1+1<<"  and  Pivot column = Column "<<idx2+1<<endl;*/

            for(i=2;i<columns-1;i++)
              {
                tableau[idx1][i] = tableau[idx1][i]/pivot;
              }
            
            for(i=2;i<rows-1;i++)
              {
                if(i!=idx1)
                  {
                    div = tableau[i][idx2];
                    for(j=2;j<columns-1;j++)
                      {
                        tableau[i][j] -= div * tableau[idx1][j];
                      }
                  }
              }
        
            tableau[idx1][1] = tableau[1][idx2];
            tableau[idx1][0] = tableau[0][idx2];
            
            vector<double> C(columns-3);
            for(i=0;i<columns-3;i++)
              {
              	C[i]=0;
              	for(j=2;j<rows-1;j++)
              	  {
              	  	C[i]=C[i]+tableau[j][0]*tableau[j][i+2];
				  }
			  }
		
			for(j=2;j<columns-2;j++)
			  {
			  	tableau[rows-1][j]=C[j-2]-tableau[0][j];
			  }
			tableau[rows-1][columns-2]=C[columns-4]+d;
          }
        t++;
      }
}

void optimal_soln(vector<vector<double> > &tableau, vector<double> &expression, int rows, int columns, double d)
{
	int i,j,n,m,temp;
	n = columns-rows-1;
    m = columns-n-4;
    
	if(unbounded == 0)
      {
	    cout<<"\nThe maximum value of the objective function : Z = ";
	    for(i=0;i<n-1;i++)
	      {
	        cout<<setprecision(2)<<expression[i]<<"x"<<i+1<<" + ";
	      }
	    cout<<setprecision(2)<<expression[n-1]<<"x"<<n<<"  is = ";
	    cout<<fixed<<setprecision(6)<<tableau[m+2][n+m+2]<<endl<<"\nObtained for the following values of xi :"<<endl;
		cout<<"[ ";
	    for(i=1;i<n;i++)
	      {
	      	int flag=0;
	        for(j=2;j<m+2;j++)
	          {
	            temp = tableau[j][1]; 
	            if(i == temp)
	              {
	                cout<<fixed<<setprecision(6)<<tableau[j][m+n+2]<<" , ";
	                flag=1;
	                break;
	              }
	          }
	        if(flag==0)
	          cout<<"0.000000 , ";
	      }
	    
	    int flag=0;
		for(j=2;j<m+2;j++)
		  {
		    temp = tableau[j][1]; 
		    if(n == temp)
		      {
		        cout<<fixed<<setprecision(6)<<tableau[j][m+n+2]<<" ";
		        flag=1;
		        break;
		      }
		  }
		if(flag==0)
		  cout<<"0.000000 ";
	    cout<<"]\n";
    
      }
    
    else
      {
      	cout<<"\nThe system is unbounded !!\n";
	  }	
}

int main()
{

	int n,i,j,m,input,flag,temp;
	cout<<"Enter the number of variables: ";
	cin>>n;
	cout<<"Enter the number of constraint equations: ";
	cin>>m;

    vector<vector<double> > A(m,vector<double> (n+m)),tableau(m+3,vector<double> (n+m+4));
    vector<double> B(m),expression(n);

    cout<<"Enter coefficient matrix for constraints : \n\n";
    for(i=0;i<m;i++)
      for(j=0;j<n;j++)
        cin>>A[i][j];

    for(i=0;i<m;i++)
      {
        for(j=n;j<n+m;j++)      //adding slack variables
          {
            A[i][j]=0;
          }
        A[i][i+n]=1;
      }

    cout<<"\nEnter the RHS vector for constraints :\n";
    for(i=0;i<m;i++)
	  cin>>B[i];
    
    int ch;
    cout<<"\nEnter 1 if it is a maximization problem, and enter 2 if it is a minimization problem : ";
    cin>>ch;

    cout<<"\nEnter the coefficients of objective function :\n";
    for(i=0;i<n;i++)
      {
        cin>>expression[i];
        if(ch==2)
          expression[i] = -1*expression[i];
      }
    double d;
    cout<<"\nEnter the constant term in objective function (enter 0 if there is no constant) : ";
    cin>>d;
    if(ch==2)
      d=-1*d;
      
	while(1)
	{
	 
		cout<<"\n#########################################################################################################\n";
	    cout<<"\nNow, enter which option you want to see : \n";
	    cout<<"(1) List of all Basic Feasible Solutions"<<endl;
	    cout<<"(2) Expressing the Problem in Standard Form"<<endl;
	    cout<<"(3) Number of Iterations needed to solve the problem"<<endl;
	    cout<<"(4) List of all Non-basic variables along with net evaluations after some iteration"<<endl;
	    cout<<"(5) List of Basic variables along with min ratios after some iteration"<<endl;
	    cout<<"(6) Simplex Tableau after some iteration"<<endl;
	    cout<<"(7) Optimal Solution"<<endl;
	    cout<<"(8) Nothing. Exit"<<endl;
	    cout<<"\n#########################################################################################################\n";
	    
	    int menu;
	    cin>>menu;
	    
	    if(menu==8)
	      return 0;
	    if(menu==1)
	      {
	      	solve(A,B,expression,m,n+m,ch);
	      	continue;
		  }
		if(menu==2)
		  {
		  	standard_form(A,B,expression,m,n,d);
		  	continue;
		  }
	    if(menu==3)
	      {
	      	t=0;
	      	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
    		if(unbounded==1)
    		  cout<<"\nThe system is unbounded !! "<<endl;
    		else
	      	  cout<<"\nNo. of iterations required = "<<t<<endl;
	      	continue;
		  }
		if(menu==4)
		  {
		  	int it;
		  	cout<<"\nEnter the iteration no. for which you want to see the list of non-basic variables : ";
		  	cin>>it;
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
		  	if(it>t)
		  	  {
		  	  	cout<<"No. of iterations required is = "<<t<<endl;
		  	  	cout<<"Please enter an iteration number lesser than or equal to "<<t<<" : ";
		  	  	cin>>it;
			  }
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,it,-1,-1);
		  }
		
		if(menu==5)
		  {
		  	int it;
		  	cout<<"\nEnter the iteration no. for which you want to see the list of basic variables and min ratios : ";
		  	cin>>it;
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
		  	if(it>t)
		  	  {
		  	  	cout<<"No. of iterations required is = "<<t<<endl;
		  	  	cout<<"Please enter an iteration number lesser than or equal to "<<t<<" : ";
		  	  	cin>>it;
			  }
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,it,-1);
		  }
		
		if(menu==6)
		  {
		  	int it;
		  	cout<<"\nEnter the iteration no. for which you want to see the Simplex Tableau : ";
		  	cin>>it;
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
		  	if(it>t)
		  	  {
		  	  	cout<<"No. of iterations required is = "<<t<<endl;
		  	  	cout<<"Please enter an iteration number lesser than or equal to "<<t<<" : ";
		  	  	cin>>it;
			  }
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,it);
		  }
		
		if(menu==7)
		  {
		  	t=0;
		  	makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    		applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
    		optimal_soln(tableau,expression,m+3,n+m+4,d);
		  }
    }
	  
    /*makeTableau(A,B,expression,m+3,n+m+4,tableau,d);
    applySimplex(tableau,expression,m+3,n+m+4,d,-1,-1,-1);
    optimal_soln(tableau,expression,m+3,n+m+4,d);*/
    
	return 0;
}
