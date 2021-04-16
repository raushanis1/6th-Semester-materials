/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

#define ERR 0.001
double tolerance=0.000000001;
int unbounded=0, t=0;
int infeasible = 0,alternate = 0,altIdx = 0;
double M=10000;

void makeTableau(vector<vector<double> > &A, vector<double> &B, vector<double> &expression, int rows, int columns, vector<vector<double> > &tableau, vector<vector<int> > &additional, int n)
{   // rows=m+2
    int m,i,j,k;
	m = rows-2;
	int slack=0,surplus=0,artificial=0;
	
	for(i=0;i<m;i++)
      {
        if(additional[0][i]==1) 
		  slack++;
        if(additional[0][i]==-1) 
		  surplus++;
        if(additional[1][i]==1) 
		  artificial++;
      }  
    
    for(i=0;i<rows;i++)
      {
        for(j=0;j<columns;j++)
          {
            tableau[i][j] = 0;
          }
      }
      
    for(i=0;i<n;i++)
      {
        tableau[0][i+2] = i+1;   //variable number
    
        tableau[1][i+2] = (-1)*expression[i]*expression[n];
        for(j=0;j<m;j++)
          {
            if(additional[1][j]==1)
              {
                tableau[1][i+2] += M*(-1)*A[j][i];
              }
          }

        for(j=0;j<m;j++)
          {
            tableau[j+2][i+2] = A[j][i];
          }
      }
    
    for(i=0;i<surplus;i++)
      {
        tableau[0][n+i+2] = 100+i+1;    //variable number for surplus variables
        tableau[1][n+i+2] = M;         
        k=0;
        for(j=0;j<m;j++)
          {
            if(additional[0][j]==-1) 
			  k++;
            if(k==(i+1))
              {
                tableau[j+2][n+i+2] = -1;
                break;
              }
          }
      }
    
    for(i=(n+surplus+2);i<columns-1;i++)
      {
        k=i-(surplus+n+2);

        if(additional[0][k] == 1)
          {
            tableau[0][i] = 200+k+1;    //slack variable numbering
            tableau[k+2][i] = 1;        // Basic variables in column 2
            tableau[k+2][0] = 200+k+1;
          }
        else if(additional[1][k] == 1)
          {
            tableau[0][i] = 300+k+1;    // artificial variable numbering
            tableau[k+2][i] = 1 ;       // Basic variables in column 2
            tableau[k+2][0] = 300+k+1;
          }
      }
    
    for(i=0;i<m;i++)
      {
        if(additional[1][i]==1) 
		  tableau[1][columns-1] -= M*B[i];
      }
	  
	for(i=2;i<rows;i++)
      {
        tableau[i][columns-1] = B[i-2];
      }
      
    cout<<endl;
}


void performSimplexIteration(vector<vector<double> > &tableau, int rows, int columns, int colIdx)
{
    int i,j,rowIdx;
    double minRatio,pivot,entCol;

    minRatio = 1000000;
    for(i=2;i<rows;i++)
      {
        if(tableau[i][colIdx] > 0)
          {
            if((tableau[i][columns-1]/tableau[i][colIdx]) < minRatio)
              {
                minRatio = tableau[i][columns-1]/tableau[i][colIdx];
                rowIdx = i;
              }
          }
      }

    pivot = tableau[rowIdx][colIdx];

    for(i=2;i<columns;i++)
      {
        tableau[rowIdx][i] = tableau[rowIdx][i]/pivot;
      }

    for(i=1;i<rows;i++)
      {
        if(i!=rowIdx)
          {
            entCol = tableau[i][colIdx];
            for(j=2;j<columns;j++)
              {
                tableau[i][j] -= entCol * tableau[rowIdx][j];
              }
          }
      }

    tableau[rowIdx][0] = tableau[0][colIdx];
}

int applySimplex(vector<vector<double> > &tableau, int rows, int columns)
{
    int i,j,n,m,idx1,idx2;

    t=0;
    double minNeg,minRatio,pivot,div;
    while(1)
      {         
        minNeg = 0;
        for(i=2;i<columns-1;i++)
          {
            if(tableau[1][i]<minNeg)
              {
                minNeg = tableau[1][i];
                idx2 = i;                    // Pivot column index
              }
          }

        if(fabs(minNeg) < tolerance) 
		  { 
		    //cout<<"\nNothing more to optimize ...\n";
		    break;                                      // Nothing more to optimize 
		  }
		  
        for(i=2;i<rows;i++)
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
          	t++;
          	performSimplexIteration(tableau,rows,columns,idx2);
		  }
      }
    
    for(i=2;i<rows;i++)
      {
        if(tableau[i][0]>300)   //artificial variable remaining in Basic soln
          {
            if(fabs(tableau[i][columns-1]) > tolerance)
              {
                infeasible = 1;
              }
          }
      }
      
    if(infeasible != 1)
      {
        for(i=2;i<columns-1;i++)
          {
            if(fabs(tableau[1][i]) < tolerance)
              {
                for(j=2;j<rows;j++)
                  {
                    if(tableau[0][i]==tableau[j][0]) 
					  break;
                  }
                  
                if(j==rows)
                  {
                    alternate = 1;
                    altIdx = i;
                  }
              }
          }
      }
      
    return t;
}


int main()
{

	int n,i,j,m,input,flag;
	cout<<"Enter the number of variables: ";
	cin>>n;
	cout<<"Enter the number of constraint equations: ";
	cin>>m;

    vector<vector<double> > A(m,vector<double> (n));
    vector<double> B(m),expression(n+1),type(m);
    vector<vector<int> > additional(2,vector<int> (m));

    cout<<"Enter coefficient matrix for constraints : \n\n";
    for(i=0;i<m;i++)
      for(j=0;j<n;j++)
        cin>>A[i][j];
    
    int var_count=n;
    cout<<"Enter the type of each constraint. Type (1 for <= type) , (2 for >= type) , (3 for = type) :\n";
    for(i=0;i<m;i++)
      {
      	cin>>type[i];
      	if(type[i]==1)
      	  { 
      	    additional[0][i] = 1;   // additional[0] stores coefficients of slack and surplus variables
            additional[1][i] = 0;   // additional[1] stores coefficients of artificial variables
            var_count++;
		  }
      	else if(type[i]==2)
      	  { 
      	    additional[0][i] = -1;   
            additional[1][i] = 1;   
            var_count+=2;
		  }
      	else if(type[i]==3)
      	  { 
      	    additional[0][i] = 0;   
            additional[1][i] = 1;   
            var_count++;
		  }
	  }
	
	vector<vector<double> > tableau(m+2,vector<double> (var_count+3));

    cout<<"\nEnter the RHS vector for constraints :\n";
    for(i=0;i<m;i++)
	  cin>>B[i];

    cout<<"\nEnter the coefficients of objective function :\n";
    for(i=0;i<n;i++)
      {
        cin>>expression[i];
      }
    cout<<"\nEnter 1 if it is a maximization problem, and enter -1 if it is a minimization problem : ";
    cin>>expression[n];
    
	makeTableau(A,B,expression,m+2,var_count+3,tableau,additional,n);
    applySimplex(tableau,m+2,var_count+3);
    
    if(unbounded==1)
      {
        cout<<"The solution is unbounded\n";
      }
    else if(infeasible==1)
      {
        cout<<"The LPP is infeasible\n";
      }
    else 
      {
        
        if(expression[n]==1)
          {
            cout<<"The maximum value of the expression "; 
          }
        else
          {
            cout<<"The minimum value of the expression ";
          }
        for(i=0;i<n-1;i++)
          {
          	cout<<setprecision(2)<<expression[i]<<"x"<<i+1<<" + ";
          }
        cout<<setprecision(2)<<expression[n-1]<<"x"<<n<<"  is = ";
        cout<<fixed<<setprecision(6)<<expression[n]*tableau[1][var_count+2]<<endl<<"\nObtained for the following values of xi :"<<endl;
        cout<<"[ ";
        int temp;
        for(i=1;i<n;i++)
	      {
	      	int flag=0;
	        for(j=2;j<m+2;j++)
	          {
	            temp = tableau[j][0]; 
	            if(i == temp)
	              {
	                cout<<fixed<<setprecision(6)<<tableau[j][var_count+2]<<" , ";
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
		    temp = tableau[j][0]; 
		    if(n == temp)
		      {
		        cout<<fixed<<setprecision(6)<<tableau[j][var_count+2]<<" ";
		        flag=1;
		        break;
		      }
		  }
		if(flag==0)
		  cout<<"0.000000 ";
	    cout<<"]\n";
        
      }
    
	return 0;
}
