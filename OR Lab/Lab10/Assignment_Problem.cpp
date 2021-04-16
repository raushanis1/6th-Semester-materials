/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/
    
/* Assignment Problem by Hungarian Method */

#include<bits/stdc++.h>
using namespace std;

#define INF 100000

void phase1(vector<vector<double> > &cost, vector<vector<double> > &table);
void phase2(vector<vector<double> > &cost, vector<vector<double> > &table);

void printTable(vector<vector<double> > &table)
{
	int i,j,n;
	n=table.size();
	cout<<"    ";
	for(i=1;i<=n;i++)
	  cout<<setw(4)<<"J"<<i<<" ";
	cout<<endl;
	for(i=0;i<n;i++)
	  {
	  	cout<<" W"<<i+1<<" ";
	  	for(j=0;j<n;j++)
	  	  {
	  	  	cout<<setw(5)<<table[i][j]<<" ";
	      }
	    cout<<endl;
	  }
    cout<<endl;
}

void printMark(vector<vector<int> > &mark)
{
	int n=mark.size();
	int i,j;
	cout<<"Table Info for symbols used :\nM --> Marked (Boxed)  ,  X --> Crossed out  ,  O --> Unmarked \n\n";
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<n;j++)
	  	  {
	  	  	if(mark[i][j]==2)
	  	  	  cout<<" M ";
	  	  	if(mark[i][j]==1)
	  	  	  cout<<" X ";
	  	  	else if(mark[i][j]==0)
	  	  	  cout<<" O ";
		  }
		cout<<endl;
	  }
	cout<<endl;
}

void optimal(vector<vector<double> > &cost, vector<vector<int> > &mark)
{
	double ans=0;
	int i,j,n;
	n=mark.size();
	vector<int> jobs_assigned(n);
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	    if(mark[i][j]==2)
	      {
	      	jobs_assigned[i]=j+1;
	      	ans+=cost[i][j];
		  }
    
    cout<<"\nThe minimum cost for assignment of the jobs is = "<<ans<<endl;
    cout<<"\nThis is obtained by assigning the jobs as follows :\n";
    for(i=0;i<n;i++)
      cout<<"Worker "<<i+1<<" -> Job "<<jobs_assigned[i]<<endl;
	
}

void phase1(vector<vector<double> > &cost, vector<vector<double> > &table)
{
	int n=table.size();
	int i,j;
	vector<double> row_min(n,INF),col_min(n,INF);
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	  	if(table[i][j]<row_min[i])
	  	  row_min[i]=table[i][j];      // finding row minimums
	
	cout<<"\nTable and Row minimums :\n\n";
	cout<<"    ";
	for(i=1;i<=n;i++)
	  cout<<setw(4)<<"J"<<i<<" ";
	cout<<"  Row min "<<endl;

	for(i=0;i<n;i++)
	  {
	  	cout<<" W"<<i+1<<" ";
	  	for(j=0;j<n;j++)
	  	  {
	  	  	cout<<setw(5)<<table[i][j]<<" ";
	      }
	    cout<<"    "<<row_min[i]<<endl;
	  }
    cout<<endl; 
	
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	    table[i][j]-=row_min[i];     // subtracting row minimums from the corresponding rows
	
	cout<<"\nUpdated table after subtracting Row minimums :\n\n";
	printTable(table);
	
	for(j=0;j<n;j++)
	  for(i=0;i<n;i++)
	    if(table[i][j]<col_min[j])
		  col_min[j]=table[i][j];         // finding column minimums
	
	cout<<"\nTable and Column minimums :\n\n";
	cout<<"        ";
	for(i=1;i<=n;i++)
	  cout<<setw(4)<<"J"<<i<<"  ";
	cout<<endl;

	for(i=0;i<n;i++)
	  {
	  	cout<<"    W"<<i+1<<"  ";
	  	for(j=0;j<n;j++)
	  	  {
	  	  	cout<<setw(5)<<table[i][j]<<"  ";
	      }
	    cout<<endl;
	  }
	cout<<" Col min";
	cout<<setw(5)<<col_min[0]<<" ";
	for(j=1;j<n;j++)
	  cout<<setw(5)<<" "<<col_min[j]<<" ";
    cout<<endl;
	
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	    table[i][j]-=col_min[j];     // subtracting row minimums from the corresponding rows
	
	cout<<"\nUpdated table after subtracting Column minimums :\n\n";
	printTable(table);
    
    phase2(cost,table); 
}

void phase2(vector<vector<double> > &cost, vector<vector<double> > &table)
{
	int n=table.size();
	int i,j,k,x,y,t,idx,count,squares_marked=0;
	vector<vector<int> >mark(n,vector<int>(n,0));
	vector<int> cols_marked,rows_marked;

    for(t=0;t<n;t++)
      {
		for(i=0;i<n;i++)          // Row scanning
		  {
		  	count=0; idx=-1;
		  	for(j=0;j<n;j++)
		  	  {
		  	  	if(table[i][j]==0 && mark[i][j]==0)
		  	  	  {
		  	  	  	count++; idx=j;
				  }
			  }
			if(count==1)
			  {
			  	mark[i][idx]=2;
			  	squares_marked++;
			  	cols_marked.push_back(idx);
			  	for(k=0;k<n;k++)
			  	  if(k!=i)
			  	    mark[k][idx]=1;
			  }
		  }
      }
	
	cout<<"\nMark matrix after row scanning :\n\n";
	printMark(mark);
	
	for(t=0;t<n;t++)
	  {
		for(j=0;j<n;j++)          // Column Scanning
		  {
		  	count=0; idx=-1;
		  	for(i=0;i<n;i++)
		  	  {
		  	  	if(table[i][j]==0 && mark[i][j]==0)
		  	  	  {
		  	  	  	count++; idx=i;
				  }
			  }
			if(count==1)
			  {
			  	mark[idx][j]=2;
			  	squares_marked++;
			  	rows_marked.push_back(idx);
			  	for(k=0;k<n;k++)
			  	  if(k!=j)
			  	    mark[idx][k]=1;
			  }
		  }
      }
	
	cout<<"\nMark matrix after column scanning :\n\n";
	printMark(mark);
	
	cout<<"\nNumber of squares marked = "<<squares_marked<<endl;
	
	if(squares_marked==n)
	  {
	  	cout<<"\nOptimal reached ...\n";
	  	optimal(cost,mark);
	  	return;
	  }
	cout<<"\nOptimal not yet reached ...\n";
	
	double min_undeleted=INF;
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<n;j++)
	  	  {
	  	  	if(mark[i][j]==0)
	  	  	  {
	  	  	  	if(table[i][j]<min_undeleted)
	  	  	  	  min_undeleted=table[i][j];
			  }
		  }
	  }
	cout<<"\nMinimum undeleted element = "<<min_undeleted<<endl;
	
	if(min_undeleted==0)
	  {
	  	cout<<"\nAs minimum undeleted element = 0, so marking some 0s by arbitrarily breaking ties ...\n";
	  	for(i=0;i<n;i++)
	  	  {
	  	  	for(j=0;j<n;j++)
	  	  	  {
	  	  	  	if(table[i][j]==0 && mark[i][j]==0)
	  	  	  	  {
	  	  	  	  	mark[i][j]=2; squares_marked++;
	  	  	  	  	cols_marked.push_back(j);
	  	  	  	  	rows_marked.push_back(i);
	  	  	  	  	for(k=0;k<n;k++)
	  	  	  	  	  if(k!=j)
	  	  	  	  	    mark[i][k]=1;
	  	  	  	  	for(k=0;k<n;k++)
			  	      if(k!=i)
			  	        mark[k][j]=1;
			  	    break;
				  }
			  }
		  }
		
		cout<<"\nNew marked matrix after arbitrary assignment :\n\n";
		printMark(mark);
		
		if(squares_marked==n)
		  {
		  	cout<<"\nOptimal reached ...\n";
		  	optimal(cost,mark);
		  	return;
		  }
	  }
	
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	    if(mark[i][j]==0)
		  table[i][j]-=min_undeleted;             // subtracting min_undeleted element from all undeleted ones
	
	for(i=0;i<rows_marked.size();i++)
	  {
	  	for(j=0;j<cols_marked.size();j++)
	  	  {
	  	  	x=rows_marked[i]; y=cols_marked[j];
	  	  	table[x][y]+=min_undeleted;           // adding min_undeleted element at all intersection points
		  }
	  }
	
	cout<<"\nUpdated table for the next iteration :\n\n";
	printTable(table);
	
	phase1(cost,table);	                          // Repeating phase 1 method with the new matrix obtained
}

int main()
{
	int i,j,n,workers,jobs;
	cout<<"Enter the number of workers : "; cin>>workers;
	cout<<"\nEnter the number of jobs : "; cin>>jobs;      
	n=max(workers,jobs);
	vector<int> dummy_workers,dummy_jobs;
	if(n>workers)
	  {
	  	for(i=workers+1;i<=n;i++)
	  	  dummy_workers.push_back(i);
	  }
	if(n>jobs)
	  {
	  	for(i=jobs+1;i<=n;i++)
	  	  dummy_jobs.push_back(i);
	  }
	vector<vector<double> > cost(n,vector<double>(n,0)),table(n,vector<double>(n));
	cout<<"\nEnter the cost matrix :\n";
	for(i=0;i<workers;i++)
	  for(j=0;j<jobs;j++)
	  	cin>>cost[i][j];
	
	for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	    table[i][j]=cost[i][j];
	
	cout<<"\nInput Table :\n\n";
	printTable(table);
    
    phase1(cost,table);
    if(n>workers)
      {
      	cout<<"\nwhere the following are dummy workers : ";
		for(i=0;i<dummy_workers.size();i++)
		  cout<<" W"<<dummy_workers[i]<<"  ";
	  }
	if(n>jobs)
	  {
	  	cout<<"\nwhere the following are dummy jobs : ";
		for(i=0;i<dummy_jobs.size();i++)
		  cout<<" J"<<dummy_jobs[i]<<"  ";
	  }
	
	return 0;
}

