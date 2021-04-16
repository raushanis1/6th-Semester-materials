/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

/** Program on Game Theory. A Two-player Zero sum game **/
    
#include<bits/stdc++.h>
using namespace std;

#define ERR 0.001
int infeasible=0, alternate=0, altIdx=0, unbounded=0, t=0;
double M=10000, INF=1000000, NEG=-1000000, tolerance=0.000000001;
bool saddle=false;

void find_saddle_pt(vector<vector<double> >&table)
{
	int n,m,i,j;
	n=table.size(); m=table[0].size();
	vector<double> row_min(n,INF),col_max(m,NEG);
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  {
	  	  	if(table[i][j]<row_min[i])
	  	  	  row_min[i]=table[i][j];
	  	  	if(table[i][j]>col_max[j])
	  	  	  col_max[j]=table[i][j];
		  }
	  }
	
	cout<<"\nTable with Row minimums and Column maximums :\n\n";
	cout<<"        ";
	for(i=1;i<=m;i++)
	  cout<<setw(4)<<"B"<<i<<" ";
	cout<<"  Row min "<<endl;

	for(i=0;i<n;i++)
	  {
	  	cout<<"     A"<<i+1<<" ";
	  	for(j=0;j<m;j++)
	  	  {
	  	  	cout<<setw(5)<<table[i][j]<<" ";
	      }
	    cout<<"    "<<row_min[i]<<endl;
	  }
	cout<<" Col max";
	cout<<setw(5)<<col_max[0]<<" ";
	for(j=1;j<m;j++)
	  cout<<setw(4)<<" "<<col_max[j]<<" ";
    cout<<endl; 
	
	double row_maxi_min=NEG,col_mini_max=INF;
	int col_idx,row_idx;
	for(i=0;i<n;i++)
	  if(row_min[i]>row_maxi_min)
	    {
	    	row_maxi_min=row_min[i];
	    	row_idx=i;
		}
	for(j=0;j<m;j++)
	  if(col_max[j]<col_mini_max)
	    {
	    	col_mini_max=col_max[j];
	    	col_idx=j;
		}
	
	cout<<"\nMaximum of the row minimums = "<<row_maxi_min<<endl;
	cout<<"Minimum of the col maximums = "<<col_mini_max<<endl;
		
	if(row_maxi_min == col_mini_max)
	  {
	  	saddle=true;
	  	cout<<"\nThis is a Stable game. Saddle point exists, with value of the game = "<<col_mini_max;
	  	cout<<"\nFor this, A plays his strategy = A"<<row_idx+1<<endl;
	  	cout<<"          B plays his strategy = B"<<col_idx+1<<endl;
	  	return;
	  }
	cout<<"\nThis is an Unstable game. Saddle point does not exist. So we have to go for mixed strategies ...\n";
	cout<<"We now apply BigM method to solve the corresponding optimization problem for A and B\n";
}

void makeTableau(vector<vector<double> >&A, vector<double>&B, vector<double>&expression, int rows, int columns, vector<vector<double> >&tableau, vector<vector<int> >&additional, int n)
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

void printTableau(vector<vector<double> > &tableau)
{
    int i,j,temp,rows,columns;
    rows=tableau.size(); columns=tableau[0].size();
    cout<<"  Basic  ";
    for(j=2;j<columns-1;j++)
      {
        temp = ((int)tableau[0][j])%100;
        if(tableau[0][j] > 300)
          cout<<" artif"<<temp<<" "; 
        else if(tableau[0][j] > 200)
          cout<<"  slack"<<temp<<" ";
        else if(tableau[0][j]>100)
          cout<<" surplus"<<temp<<" ";
        else
          cout<<"    X"<<temp<<"   ";
      }
    cout<<"Solution \n";
    for(i=1;i<rows;i++)
      {
        if(i==1) 
          cout<<"    Z    ";
        else
          {
            temp = ((int)tableau[i][0])%100;
            if(tableau[i][0] > 300)
              cout<<"  artif"<<temp<<" ";
            else if(tableau[i][0] > 200)
              cout<<"  slack"<<temp<<" ";
            else if(tableau[i][0]>100)
              cout<<" surplus"<<temp<<" ";
            else
              cout<<"    X"<<temp<<"   ";
          }
        for(j=2;j<columns;j++)
		  cout<<setw(8)<<fixed<<setprecision(2)<<tableau[i][j];  
        cout<<endl;
      }
    cout<<endl<<endl;
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
      	cout<<"\nSimplex Tableau after iteration "<<t<<" :\n\n";
	    printTableau(tableau);
		         
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

void BigM(vector<vector<double> >&table, int player)
{
	int m,n,i,j;
	n=table.size(); m=table[0].size();                    // n = #rows in payoff table , m = #cols in payoff table 
	vector<vector<double> > A(m,vector<double> (n));      // No. of variables = n , No. of constraints = m  
    vector<double> B(m),expression(n+1,0),type(m);
    vector<vector<int> > additional(2,vector<int> (m));
    
    for(i=0;i<m;i++)
      {
      	A[i][0]=1;
      	for(j=1;j<n;j++)
      	  {
      	  	A[i][j]=table[n-1][i]-table[j-1][i];
		  }
		B[i]=table[n-1][i];
		type[i]=1; 
	  }
	expression[0]=1; expression[n]=1;
	
	int var_count=n;
    for(i=0;i<m;i++)
      {
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
	makeTableau(A,B,expression,m+2,var_count+3,tableau,additional,n);
    applySimplex(tableau,m+2,var_count+3);
    
    if(unbounded==1)
      {
        cout<<"The solution is unbounded\n";
      }
    else if(infeasible==1)
      {
        cout<<"The Game is infeasible\n";
      }
    else 
      {
      	if(player==1)
          {
          	cout<<"The optimal value of the game for A is : ";
          	cout<<fixed<<setprecision(6)<<expression[n]*tableau[1][var_count+2]<<endl;
		  }
        else if(player==2)
          {
          	cout<<"The optimal value of the game for B is : ";
            cout<<fixed<<setprecision(6)<<(-1)*expression[n]*tableau[1][var_count+2]<<endl;
		  }
          
        int temp;
        vector<double> values;
        for(i=1;i<n;i++)
	      {
	      	int flag=0;
	        for(j=2;j<m+2;j++)
	          {
	            temp = tableau[j][0]; 
	            if(i == temp)
	              {
	                values.push_back(tableau[j][var_count+2]);
	                flag=1;
	                break;
	              }
	          }
	        if(flag==0)
	          values.push_back(0);

	      }
	    
	    int flag=0;
		for(j=2;j<m+2;j++)
		  {
		    temp = tableau[j][0]; 
		    if(n == temp)
		      {
		        values.push_back(tableau[j][var_count+2]);
		        flag=1;
		        break;
		      }
		  }
		if(flag==0)
		  values.push_back(0);

        double prob=0;
        for(i=1;i<values.size();i++)
          prob+=values[i];
        values.push_back(1.0-prob);
        
        cout<<"\nWith probabilities for strategies : [  ";
        if(player==1)
          {
          	for(i=1;i<values.size()-1;i++)
              cout<<"A"<<i<<" : "<<values[i]<<" , ";
            cout<<"A"<<i<<" : "<<values[i];
		  }
		
		else
		  {
		  	for(i=1;i<values.size()-1;i++)
              cout<<"B"<<i<<" : "<<values[i]<<" , ";
            cout<<"B"<<i<<" : "<<values[i];
		  }
        
        cout<<"]\n";
      }
    
}

int main()
{
	int n,m,i,j;
	cout<<"Enter the number of strategies of A : ";
	cin>>n;
	cout<<"\nEnter the number of strategies of B : ";
	cin>>m;
	vector<vector<double> > table(n,vector<double>(m)), transpose(m,vector<double>(n));
	cout<<"\nEnter the pay-off matrix for A : \n\n";
	for(i=0;i<n;i++)
	  for(j=0;j<m;j++)
	    { 
		  cin>>table[i][j];      // nxm table
	      transpose[j][i]=-table[i][j];
	    }
	cout<<"\nPayoff Table for A :\n\n";
	cout<<"    ";
	for(j=1;j<=m;j++)
	  cout<<setw(4)<<"B"<<j<<" ";
	cout<<endl;
	for(i=0;i<n;i++)
	  {
	  	cout<<" A"<<i+1<<" ";
	  	for(j=0;j<m;j++)
	  	  {
	  	  	cout<<setw(5)<<table[i][j]<<" ";
	      }
	    cout<<endl;
	  }
    cout<<endl;
	
    find_saddle_pt(table);
    if(saddle==true)
      return 0;
    cout<<"\n-------------------------------------------------------------";
    cout<<"\nSolving the game for player A \n";
    cout<<"-------------------------------------------------------------";
    BigM(table,1);
    cout<<"\n-------------------------------------------------------------";
    cout<<"\nNow solving the game for player B \n";
    cout<<"-------------------------------------------------------------";
    BigM(transpose,2);
    
	return 0;
}

/**

2
2
5 2
3 4

2
4
-2 3 5 2
5 -1 -2 0

2
4
4 0 6 -2
2 6 1 7

4
4
-1 0 4 -1
5 1 3 1
-2 0 -1 4
-3 -2 4 5

**/
