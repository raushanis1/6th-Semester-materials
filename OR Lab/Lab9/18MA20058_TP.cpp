/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/
    
#include<bits/stdc++.h>
using namespace std;
#define INF 10000
int epsilon=-2;

void printTable(vector<vector<pair<double,int> > > &table, int rows, int columns)
{
	cout<<endl<<endl;
	cout<<fixed<<setprecision(2);
	int i,j;
	cout<<"     ";
	for(i=1;i<columns;i++)
	  cout<<setw(14)<<"D"<<i<<"  ";
	cout<<setw(15)<<"  ai \n";
	
	for(i=0;i<rows-1;i++)
	  {
	  	cout<<"  O"<<i+1<<"  ";
	  	for(j=0;j<columns;j++)
	  	  {
	  	  	if(table[i][j].second ==0)
	  	  	  cout<<setw(15)<<table[i][j].first<<"  ";
	  	  	else if(table[i][j].second == epsilon)
	  	  	  cout<<setw(10)<<table[i][j].first<<" (eps) ";       // eps = epsilon (to solve degeneracy)
	  	  	else
	  	  	  cout<<setw(11)<<table[i][j].first<<" ("<<table[i][j].second<<") ";
		  }
		cout<<endl;
	  }
	
	cout<<"  bi  ";
	for(j=0;j<columns-1;j++)
	  cout<<setw(15)<<table[rows-1][j].first<<"  ";
	cout<<endl<<endl;
	
}

void print_phase2_table(vector<vector<pair<double,int> > > &table, int rows, int columns, vector<double> &u, vector<double> &v, vector<vector<double> > &opportunity_cost)
{
	cout<<endl<<endl;
	cout<<fixed<<setprecision(2);
	int i,j;
	cout<<"     ";
	for(i=1;i<columns;i++)
	  cout<<setw(14)<<"D"<<i<<"  ";
	cout<<setw(15)<<"  ai  ";
	cout<<setw(15)<<"  ui  \n";
	
	for(i=0;i<rows-1;i++)
	  {
	  	cout<<"  O"<<i+1<<"  ";
	  	for(j=0;j<columns;j++)
	  	  {
	  	  	if(table[i][j].second ==0 && j<columns-1)
	  	  	  cout<<setw(10)<<table[i][j].first<<" ["<<opportunity_cost[i][j]<<"] ";
	  	  	else if(table[i][j].second ==0)
	  	  	  cout<<setw(10)<<table[i][j].first<<"  ";
	  	  	else if(table[i][j].second == epsilon)
	  	  	  cout<<setw(10)<<table[i][j].first<<" (eps) ";       // eps = epsilon (to solve degeneracy)
	  	  	else
	  	  	  cout<<setw(11)<<table[i][j].first<<" ("<<table[i][j].second<<") ";
		  }
		cout<<setw(10)<<u[i];
		cout<<endl;
	  }
	
	cout<<"  bi  ";
	for(j=0;j<columns-1;j++)
	  cout<<setw(15)<<table[rows-1][j].first<<"  ";
	cout<<endl;
	cout<<"  vj  ";
	for(j=0;j<columns-1;j++)
	  cout<<setw(15)<<v[j]<<"  ";
	cout<<endl<<endl;
}

double cost_evaluate(vector<vector<pair<double,int> > > &table, int rows, int columns)
{
	double cost=0;
	int i,j;
	for(i=0;i<rows-1;i++)
	  {
	  	for(j=0;j<columns-1;j++)
	  	  {
	  	  	if(table[i][j].second!=epsilon)
	  	  	  cost+=table[i][j].first*table[i][j].second;
		  }
	  }
    return cost;
}

bool check_degeneracy(vector<vector<pair<double,int> > > &table, int rows, int columns)
{
	int i,j,m,n,count=0;
	n=rows-1; m=columns-1;
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  {
	  	  	if(table[i][j].second>0 || table[i][j].second==epsilon)
	  	  	  count++;
		  }
	  }
	if(count==m+n-1)
	  return false;
	return true;
}

void NWCmethod(vector<vector<pair<double,int> > > &table, int rows, int columns)
{
	int i,j,n,m;
	n=rows-1; m=columns-1;
	vector<double> source(n),dest(m);
	double sum=0;
	for(i=0;i<n;i++)
	  { 
	    source[i]=table[i][columns-1].first;
	    sum+=source[i];
	  }
	for(j=0;j<m;j++)
	  {
	  	dest[j]=table[rows-1][j].first;
	  	sum+=dest[j];
	  }  
	
	vector<vector<int> > X(n,vector<int>(m,0));
	X[0][0]=min(source[0],dest[0]);
	sum-=2*X[0][0];
	source[0]-=X[0][0]; dest[0]-=X[0][0];
	
    if(source[0]==0)
      {
      	for(j=0;j<m;j++)
  	  	  {
  	  	  	if(X[0][j]==0)
  	  	  	  X[0][j]=-1;
		  }
	  }
	if(dest[0]==0)
	  {
	  	for(i=0;i<n;i++)
  	  	  {
  	  	  	if(X[i][0]==0)
  	  	  	  X[i][0]=-1;
		  }
	  }
	
	while(sum>0)
	  {
	  	int k=-1,l=-1;
	  	for(i=0;i<n;i++)
	  	  {
	  	  	for(j=0;j<m;j++)
	  	  	  {
	  	  	  	if(X[i][j]==0)
	  	  	  	  {
	  	  	  	  	k=i; l=j;
	  	  	  	  	break;
				  }
			  }
			if(k!=-1 && l!=-1)
			  break;
		  }
		
		X[k][l]=min(source[k],dest[l]);
		sum-=2*X[k][l];
	    source[k]-=X[k][l]; dest[l]-=X[k][l];
	    
	    if(source[k]==0)
	      {
	      	for(j=0;j<m;j++)
	  	  	  {
	  	  	  	if(X[k][j]==0)
	  	  	  	  X[k][j]=-1;
			  }
		  }
		if(dest[l]==0)
		  {
		  	for(i=0;i<n;i++)
	  	  	  {
	  	  	  	if(X[i][l]==0)
	  	  	  	  X[i][l]=-1;
			  }
		  }
	  }
	
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  {
	  	  	if(X[i][j]!=-1)
	  	  	  {
	  	  	  	table[i][j].second=X[i][j];
			  }
		  }
	  }
	
	bool check = check_degeneracy(table,rows,columns);
	if(check)
	  {
	  	vector<pair<double,pair<int,int> > > v;
	  	for(i=0;i<n;i++)
	  	  {
	  	  	for(j=0;j<m;j++)
	  	  	  {
	  	  	  	if(table[i][j].second==0 && table[i][j].first>0)
	  	  	  	  v.push_back(make_pair(table[i][j].first,make_pair(i,j)));
			  }
		  }
	  	sort(v.begin(),v.end());
	  	i=v[0].second.first; j=v[0].second.second;
	  	table[i][j].second=epsilon;
	  }
	cout<<"\nTable after NWC rule :";
	printTable(table,rows,columns);
	cout<<"\nShipping Cost for this allocation = "<<cost_evaluate(table,rows,columns)<<endl;
	
}

int most_allocated_row(vector<vector<pair<double,int> > > &table, int rows, int columns)
{
	int i,j,r=-1,maxi=-1,count;
	for(i=0;i<rows-1;i++)
	  {
	  	count=0;
	  	for(j=0;j<columns-1;j++)
	  	  {
	  	  	if(table[i][j].second!=0)
	  	  	  count++;
		  }
		if(count>maxi)
		  {
		  	maxi=count;
		  	r=i;
		  }
	  }
	return r;	
}

void find_min_negative(vector<int> &index, vector<vector<double> > &opportunity_cost)
{
	double min_cost=opportunity_cost[0][0];
	int x=-1,y=-1,i,j,n,m;
	n=opportunity_cost.size(); m=opportunity_cost[0].size();   // nxm matrix
	for(i=0;i<n;i++)
	  {
	  	for(j=0;j<m;j++)
	  	  {
	  	  	if(opportunity_cost[i][j]<=min_cost)
	  	  	  {
	  	  	  	min_cost=opportunity_cost[i][j];
	  	  	  	x=i; y=j;
			  }
		  }
	  }
    if(min_cost<0)
      {
      	index[0]=x; index[1]=y; index[2]=1;
	  }
	else
	  {
	  	index[0]=-1; index[1]=-1; index[2]=0;
	  }
}

void get_loop_corners(int x, int y, vector<vector<pair<double,int> > > &table, vector<pair<int,int> > &corners)
{
	int n,m,i,j;
	n=table.size()-1; m=table[0].size()-1;
	pair<int,int> A,B,C,D;
	A=make_pair(x,y);
	vector<int> col,row;
	for(i=0;i<n;i++)
	  {
	  	if(table[i][y].second!=0 && i!=x)
	  	  col.push_back(i);
	  }
	for(j=0;j<m;j++)
	  {
	  	if(table[x][j].second!=0 && j!=y)
	  	  row.push_back(j);
	  }
	for(i=0;i<col.size();i++)
	  {
	  	for(j=0;j<row.size();j++)
	  	  {
	  	  	if(table[col[i]][row[j]].second!=0)
	  	  	  {
	  	  	  	D=make_pair(col[i],y); C=make_pair(col[i],row[j]); B=make_pair(x,row[j]);
	  	  	  	corners[0]=A; corners[1]=B; corners[2]=C; corners[3]=D;
	  	  	  	return;
			  }
		  }
	  }
    return;
}

void MODI_method(vector<vector<pair<double,int> > > &table)
{
	int i,j,n,m;
	n=table.size()-1; m=table[0].size()-1;
	int count=0;
	while(1)
	  {
	  	vector<double> u(n,INF),v(m,INF);
	  	int row=most_allocated_row(table,n+1,m+1);
	  	u[row]=0;
	  	queue<pair<int,int> > q;
	  	q.push(make_pair(row,-1));
	  	while(!q.empty())
	  	  {
	  	  	pair<int,int> top;
	  	  	top=q.front();
	  	  	q.pop();
	  	  	if(top.first!=-1)
	  	  	  {
	  	  	  	for(i=0;i<m;i++)
	  	  	  	  {
	  	  	  	  	if(table[top.first][i].second!=0 && v[i]==INF)
	  	  	  	  	  {
	  	  	  	  	  	q.push(make_pair(-1,i));
	  	  	  	  	  	v[i]=table[top.first][i].first-u[top.first];
					  }
				  }
			  }
			else
			  {
			  	for(i=0;i<n;i++)
			  	  {
			  	  	if(table[i][top.second].second!=0 && u[i]==INF)
	  	  	  	  	  {
	  	  	  	  	  	q.push(make_pair(i,-1));
	  	  	  	  	  	u[i]=table[i][top.second].first-v[top.second];
					  }
				  }
			  }
		  }
	    
	    vector<vector<double> > opportunity_cost(n,vector<double>(m));
	    for(i=0;i<n;i++)
	      {
	      	for(j=0;j<m;j++)
	      	  {
	      	  	opportunity_cost[i][j]=table[i][j].first-u[i]-v[j];
			  }
		  }
		
	    print_phase2_table(table,n+1,m+1,u,v,opportunity_cost);          
	    
	    vector<int> index(3);
	    find_min_negative(index,opportunity_cost);
	    if(index[2]==0)
	      {
	      	cout<<"\nOptimal allocation found !! All dij >= 0 \n";
	      	return;
		  }
	    
	    cout<<"Minimum negative opportunity cost dij found at : ("<<index[0]<<","<<index[1]<<")  with dij = "<<opportunity_cost[index[0]][index[1]]<<endl;
	    vector<pair<int,int> > corners(4);
	    get_loop_corners(index[0],index[1],table,corners);
	    cout<<"Closed loop from this cell : ("<<corners[0].first<<","<<corners[0].second<<") -> ("<<corners[1].first<<","<<corners[1].second<<") -> ("<<corners[2].first<<","<<corners[2].second<<") ";
	    cout<<"-> ("<<corners[3].first<<","<<corners[3].second<<")\n";
	    int min_val=min(table[corners[1].first][corners[1].second].second,table[corners[3].first][corners[3].second].second);
	    if(table[corners[0].first][corners[0].second].second == epsilon) table[corners[0].first][corners[0].second].second = min_val;
	    else if(table[corners[0].first][corners[0].second].second != epsilon) table[corners[0].first][corners[0].second].second += min_val;
	    if(table[corners[2].first][corners[2].second].second == epsilon) table[corners[2].first][corners[2].second].second = min_val;
	    else if(table[corners[2].first][corners[2].second].second != epsilon) table[corners[2].first][corners[2].second].second += min_val;
	      
	    table[corners[1].first][corners[1].second].second -= min_val;
	    table[corners[3].first][corners[3].second].second -= min_val;
	    
	    printTable(table,n+1,m+1);
	    
	    bool check = check_degeneracy(table,n+1,m+1);
		if(check)
		  {
		  	vector<pair<double,pair<int,int> > > v;
		  	for(i=0;i<n;i++)
		  	  {
		  	  	for(j=0;j<m;j++)
		  	  	  {
		  	  	  	if(table[i][j].second==0 && table[i][j].first>0)
		  	  	  	  v.push_back(make_pair(table[i][j].first,make_pair(i,j)));
				  }
			  }
		  	sort(v.begin(),v.end());
		  	i=v[0].second.first; j=v[0].second.second;
		  	table[i][j].second=epsilon;
		  }
	  }
	return; 
}


int main()
{
	int i,j,n,m;
	cout<<"Enter the number of supply sources : "; cin>>n;
	cout<<"\nEnter the number of demand destinations : "; cin>>m;
	vector<double> source(n),dest(m);
	double sum1=0,sum2=0; int flag=0;
	cout<<"\nEnter the values of supply from the sources :\n\n";
	for(i=0;i<n;i++)
	  {
	  	cin>>source[i];
	  	sum1+=source[i];
	  }
	cout<<"\nEnter the values of demand at the destinations :\n\n";
	for(i=0;i<m;i++)
	  {
	  	cin>>dest[i];
	  	sum2+=dest[i];
	  }
	  
	if(sum1>sum2)
	  {
	  	m++;
	  	dest.push_back(sum1-sum2);
	  	flag=1;
	  }
	else if(sum2>sum1)
	  {
	  	n++;
	  	source.push_back(sum2-sum1);
	  	flag=-1;
	  }
	  
	vector<vector<pair<double,int> > > table(n+1,vector<pair<double,int> >(m+1,{0,0}));
	
	cout<<"\nEnter the matrix containing per unit cost of shippings :\n\n";
	
	if(flag==0)                       // No dummy source/destination needed
	  {
	  	for(i=0;i<n;i++)
	  	  for(j=0;j<m;j++)
	  	    cin>>table[i][j].first;
	  	
	  	for(i=0;i<n;i++)
	  	  table[i][m].first=source[i];
	  	for(j=0;j<m;j++)
	  	  table[n][j].first=dest[j];
	  }
	
	else if(flag==1)
	  {
	  	for(i=0;i<n;i++)
	  	  for(j=0;j<m-1;j++)
	  	    cin>>table[i][j].first;
	  	for(i=0;i<n;i++)
	  	  table[i][m-1].first=0;            // Balancing the table by introducing a dummy destination
	  	  
	  	for(i=0;i<n;i++)
	  	  table[i][m].first=source[i];
	  	for(j=0;j<m;j++)
	  	  table[n][j].first=dest[j];
	  }
	
	else if(flag==-1)
	  {
	  	for(i=0;i<n-1;i++)
	  	  for(j=0;j<m;j++)
	  	    cin>>table[i][j].first;
	  	for(j=0;j<m;j++)
	  	  table[n-1][j].first=0;            // Balancing the table by introducing a dummy source
	  	  
	  	for(i=0;i<n;i++)
	  	  table[i][m].first=source[i];
	  	for(j=0;j<m;j++)
	  	  table[n][j].first=dest[j];
	  }
	
	cout<<"\nInput Table :";
	printTable(table,n+1,m+1);
	
	NWCmethod(table,n+1,m+1);
    MODI_method(table);
    
    cout<<"\nThe Optimal (minimum) transportation cost is = "<<cost_evaluate(table,n+1,m+1)<<endl;
    
	return 0;
}

