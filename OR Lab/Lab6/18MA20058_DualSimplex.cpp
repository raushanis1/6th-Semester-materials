/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include<bits/stdc++.h>
using namespace std;

int unbounded=0,infeasible=0;

void makeTableau(vector<vector<double> > &A, vector<double> &B, vector<double> &expression, int n, int m, vector<vector<double> > &tableau)
{
    int rows = m+2, columns = m+n+2;
    int i,j,k;
    for(i=0;i<rows;i++)
      {
        for(j=0;j<columns;j++)
          {
            tableau[i][j] = 0;
          }
      }

    for(i=1;i<=n;i++)
      {
        tableau[0][i] = i;
        tableau[1][i] = (-1)*expression[i-1]*expression[n];

        for(j=0;j<m;j++)
          {
            tableau[j+2][i] = A[j][i-1];
          }
      }

    for(i=n+1;i<=n+m;i++)
      {
        tableau[i-n+1][i] = 1;
        tableau[0][i] = 200+i-n;      // numbering slack variables
        tableau[i-n+1][0] = 200+i-n;
      }

    for(i=2;i<rows;i++)
      {
        tableau[i][columns-1] = B[i-2];
      }
}

void printTableau(vector<vector<double> > &tableau,int rows, int columns)
{
    int i,j,temp;
    cout<<endl;
    cout<<"  Basic  ";
    
    for(j=1;j<columns-1;j++)
      {
        temp = ((int)tableau[0][j])%100;
        if(tableau[0][j] > 200)
          {
            cout<<"  slack"<<temp<<" ";
          }
        else
          {
            cout<<"    X"<<temp<<"   ";
          }
      }
      
    cout<<"   Soln  \n";
    
    for(i=1;i<rows;i++)
      {
        if(i==1) 
          {
            cout<<"    Z    ";
          }
        else
          {
            temp = ((int)tableau[i][0])%100;
            if(tableau[i][0] > 200)
              {
              	cout<<"  slack"<<temp<<" ";
              }
            else
              {
              	cout<<"    X"<<temp<<"   ";
              }
          }
        for(j=1;j<columns;j++)
          {
		    cout<<setw(8)<<fixed<<setprecision(3)<<tableau[i][j]<<" ";   
          }
        cout<<endl;
      }
}

int performDualSimplexIteration(vector<vector<double> > &tableau,int rows,int columns)
{
    int i,j,rowIdx,colIdx;
    double minRatio=1000000,pivot,div,minNeg=0;

    for(i=2;i<rows;i++)
      {
        if(tableau[i][columns-1]<minNeg)
          {
            minNeg = tableau[i][columns-1];
            rowIdx = i;
          }
      }
      
    if(minNeg==0) 
	  return 0;       // Nothing more to optimize
	  
    else
      {
        for(j=1;j<columns-1;j++)
          {
            if(tableau[rowIdx][j]<0)
              {
                if((tableau[1][j]/tableau[rowIdx][j])<minRatio)
                  {
                    minRatio = tableau[1][j]/tableau[rowIdx][j];
                    colIdx = j;
                  }
              }
          }
          
        if(minRatio==1000000) 
		  return -1;           // Infeasible
		  
        else
          {
            pivot = tableau[rowIdx][colIdx]; 

            for(j=1;j<columns;j++)
              {
                tableau[rowIdx][j] = tableau[rowIdx][j]/pivot;
              }

            for(i=1;i<rows;i++)
              {
                if(i!=rowIdx)
                  {
                    div = tableau[i][colIdx];
                    for(j=1;j<columns;j++)
                      {
                        tableau[i][j] -= div * tableau[rowIdx][j];
                      }
                  }
              }

            tableau[rowIdx][0] = tableau[0][colIdx];
            return 1;
          }
      }

}

int applyDualSimplex(vector<vector<double> > &tableau,int rows,int columns)
{
    int temp,Iterations=0;
    
    while(1)
      {
        temp=performDualSimplexIteration(tableau,rows,columns);
        if(temp!=1) 
		  break;
        else 
		  Iterations++;
      }
      
    if(temp==-1) 
	  infeasible=1;

    return Iterations;
}

int main()
{

	int i,j,n,m,iter;
	
	cout<<"Enter the number of variables: ";
	cin>>n;
	cout<<"Enter the number of constraint equations: ";
	cin>>m;
	
	vector<vector<double> > A(m,vector<double> (n));
	vector<vector<double> > tableau(m+2,vector<double> (n+m+2)), tempTableau(m+2,vector<double> (n+m+2));
    vector<double> B(m),expression(n+1),type(m);
    vector<vector<int> > additional(2,vector<int> (m));
    
    cout<<"Enter coefficient matrix for constraints : \n\n";
    for(i=0;i<m;i++)
      for(j=0;j<n;j++)
        cin>>A[i][j];
        
    cout<<"\nEnter the type of each constraint. Type (1 for <= type) , (2 for >= type) , (3 for = type) :\n";
    for(i=0;i<m;i++)
      {
      	cin>>type[i];
	  }
    
    cout<<"\nEnter the RHS vector for constraints :\n";
    for(i=0;i<m;i++)
	  cin>>B[i];
	
	for(i=0;i<m;i++)
	  {
	  	if(type[i]==2)
	  	  {
	  	  	for(j=0;j<n;j++)
              {
                A[i][j] *= -1;
              } 
            B[i] *= -1;
		  }
	  }
	  
	cout<<"\nEnter the coefficients of objective function :\n";
    for(i=0;i<n;i++)
      {
        cin>>expression[i];
      }
    cout<<"\nEnter 1 if it is a maximization problem, and enter -1 if it is a minimization problem : ";
    cin>>expression[n]; expression[n] *= -1;

    makeTableau(A,B,expression,n,m,tableau);
    iter = applyDualSimplex(tableau,m+2,m+n+2);
    
    int ch,it;
    while(1)
      {
      	cout<<"\n#############################################################\n\n";
	    cout<<"Enter 1 to view intitial tableau\n";
	    cout<<"Enter 2 to see the list of basic and non-basic variables of ith iteration\n";
	    cout<<"Enter 3 to print table of ith iteration\n";
	    cout<<"Enter 4 to view the optimal solution\n";
	    cout<<"Enter 5 to view the final tableau\n";
	    cout<<"Enter 6 to Exit\n";
        cout<<"\n#############################################################\n";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<endl<<endl;
        if(ch==1)
          {
          	cout<<"Initial Tableau : \n\n";
            makeTableau(A,B,expression,n,m,tempTableau);
            printTableau(tempTableau,m+2,m+n+2);
          }
        else if(ch==2)
          {
          	cout<<"Enter the iteration number : ";
            cin>>it;
            int x=it;
            if(it<=iter)
              {
                makeTableau(A,B,expression,n,m,tempTableau);
                while(it--)
                  {
                     performDualSimplexIteration(tempTableau,m+2,m+n+2); 
                  }
            
                set<double> s;
                set<double>::iterator itr;
                cout<<"\nBasic variables after iteration "<<x<<" :\n";
                for(i=2;i<m+2;i++)
                  {
                  	int temp;
                  	temp = ((int)tempTableau[i][0])%100;
                  	s.insert(tempTableau[i][0]);
		            if(tempTableau[i][0] > 200)
		              {
		              	cout<<"  slack"<<temp<<" "<<" = "<<setw(8)<<fixed<<setprecision(3)<<tempTableau[i][m+n+1]<<endl;
		              }
		            else
		              {
		              	cout<<"    X"<<temp<<"   "<<" = "<<setw(8)<<fixed<<setprecision(3)<<tempTableau[i][m+n+1]<<endl;
		              }
				  }
				cout<<"\n\nNon-Basic variables after iteration "<<x<<" :\n";
				for(j=1;j<m+n+1;j++)
				  {
				  	itr=s.find(tempTableau[0][j]);
				  	if(itr==s.end())
				  	  {
				  	  	int temp;
                  	    temp = ((int)tempTableau[0][j])%100;
                  	    if(tempTableau[0][j] > 200)
			              {
			              	cout<<"  slack"<<temp<<"  ";
			              }
			            else
			              {
			              	cout<<"    X"<<temp<<"   ";
			              }
					  }
				  }
				cout<<endl;
              }
            else
              {
              	cout<<"Number of iterations needed = "<<iter;
              	cout<<"\nPlease enter iteration number lesser than or equal to "<<iter;
              }
		  }
        else if(ch==3)
          {
            cout<<"Enter the iteration number : ";
            cin>>it;
            int x=it;
            if(it<=iter)
              {
                makeTableau(A,B,expression,n,m,tempTableau);
                while(it--)
                  {
                     performDualSimplexIteration(tempTableau,m+2,m+n+2); 
                  }
                cout<<"Tableau after iteration "<<x<<": \n\n";
                printTableau(tempTableau,m+2,m+n+2);
              }
            else
              {
              	cout<<"Number of iterations needed = "<<iter;
              	cout<<"\nPlease enter iteration number lesser than or equal to "<<iter;
              }
          }
        else if(ch==4)
          {
            if(unbounded==1)
              {
                cout<<"\nThe expression is unbounded\n";
              }
            else if(infeasible==1)
              {
                cout<<"\nThe LPP is infeasible\n";
              }
            else 
              {
                
                if(expression[n]==-1)
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
                cout<<fixed<<setprecision(6)<<expression[n]*tableau[1][m+n+1]<<endl<<"\nObtained for the following values of xi :"<<endl;
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
			                cout<<fixed<<setprecision(6)<<tableau[j][m+n+1]<<" , ";
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
				        cout<<fixed<<setprecision(6)<<tableau[j][m+n+1]<<" ";
				        flag=1;
				        break;
				      }
				  }
				if(flag==0)
				  cout<<"0.000000 ";
			    cout<<"]\n"; 
              }
          }
        else if(ch==5)
          {
          	cout<<"Final Tableau : \n\n";
            printTableau(tableau,m+2,m+n+2);
          }
        else if(ch==6)
		  {
		  	cout<<"Exiting ....";
		  	break;
		  }
	    
	    else
	      cout<<"\nPlease enter a valid choice ...\n";
      }

	return 0;
}
