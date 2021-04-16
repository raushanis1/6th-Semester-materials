/** NAME: Raushan Sharma
    ROLL: 18MA20058  **/

#include <bits/stdc++.h>
using namespace std;

vector<vector<double> > A;
vector<double> b, obj_coeff;
bool MAX = false, TERMINATE = false, UNBOUNDED = false, INFEASIBLE = false, all_integer;
int cut = 0;
const int M = 1000;

void print_tableau(vector<vector<double> > table) 
{
	int m=(int)table.size() - 2;
	int n=(int) table[0].size() - m - 4;
	
	for(int r = 0; r < m + 2; r++) 
	  {
		for(int c = 0; c < n + m + 4; c++)
			cout <<setw(9)<< table[r][c] << "   ";
		cout << endl;
	  }
	cout << endl;
}

vector<vector<double> > simplex(vector<vector<double> > &table) 
{
	int m = (int) table.size() - 2;
	int n = (int) table[0].size() - m - 4;
	vector<vector<double> > new_table(m + 2, vector<double> (n + m + 4, 0));
	
	for(int c = 2; c < 2 + n + m; c++) 
	{
		double cj = obj_coeff[c - 2];
		double zj = 0;
		for(int r = 1; r < 1 + m; r++) 
			zj += table[r][0]*table[r][c];
		table[m + 1][c] = cj - zj;          // cj-zj
	}
	
	double max_pos_val = -1, pivot_col = -1;
	int incoming_variable = -1;
	for (int c = 2; c < 2 + n + m; c++) 
	{
		if (table[m + 1][c] > max_pos_val) 
		  {
			max_pos_val = table[m + 1][c];
			pivot_col = c;
			incoming_variable = c - 1;
		  }
	}
	if (max_pos_val <= 0 || pivot_col == -1) 
	  {
		TERMINATE = true;
		return new_table;
	  }

	double min_ratio = 1e5;
	int pivot_row = -1;
	int departing_variable = -1;
	for (int r = 1; r < 1 + m; r++) 
	{
		if (table[r][pivot_col] == 0) continue;
		table[r][n + m + 3] = table[r][n + m + 2]/table[r][pivot_col];
		if (table[r][n + m + 3] < 0) continue;
		if (table[r][n + m + 3] < min_ratio) 
		  {
			min_ratio = table[r][n + m + 3];
			pivot_row = r;
			departing_variable = table[r][1];
		  }
	}
	
	if (pivot_row == -1) 
	  {
		UNBOUNDED = true;
		return new_table;
	  }
	double pivot = table[pivot_row][pivot_col];


	for (int c = 2; c < 2 + n + m; c++)
		new_table[0][c] = obj_coeff[c - 2];

	for (int r = 1; r < 1 + m; r++) 
		new_table[r][1] = table[r][1];

	new_table[pivot_row][1] = incoming_variable;
	for (int r = 1; r < 1 + m; r++)
		new_table[r][0] = obj_coeff[new_table[r][1] - 1];
	
	for (int c = 2; c < 2 + n + m + 1; c++)
		new_table[pivot_row][c] = table[pivot_row][c]/pivot;


	for (int r = 1; r < 1 + m; r++) 
	  {
		if (r == pivot_row) continue;
		double factor = table[r][pivot_col];
		for (int c = 2; c < 2 + n + m + 1; c++)
			new_table[r][c] = table[r][c] - factor*new_table[pivot_row][c];
	  }
	
	new_table[m + 1][2 + n + m] = 0;
	for (int r = 1; r < 1 + m; r++)
		new_table[m + 1][2 + n + m] += new_table[r][0]*new_table[r][2 + n + m];

	return new_table;
}

vector<double> BigM(vector<vector<double> > A, vector<double> b, vector<int> initial_basis, int n, int m, int extra_var) 
{
    vector<double> values(n, 0);

    vector<vector<double> > table(m + 2, vector<double> (n + extra_var + 4, 0));
    for (int c = 2; c < 2 + n + extra_var; c++)
        table[0][c] = obj_coeff[c - 2];

    for (int r = 1; r < 1 + m; r++)
        table[r][1] = initial_basis[r - 1];
   
    for (int r = 1; r < 1 + m; r++)
        table[r][0] = obj_coeff[table[r][1] - 1];

    for (int r = 1; r < 1 + m; r++) 
	  {
        for (int c = 2; c < 2 + n + extra_var; c++) 
            table[r][c] = A[r - 1][c - 2];
      }

    for (int r = 1; r < 1 + m; r++)
        table[r][2 + n + extra_var] = b[r - 1];


    vector<vector<vector<double> > > tables;
    tables.push_back(table);
    for (int iter = 0; iter <= 50; iter++) 
	  {
        vector<vector<double> > new_table = simplex(tables[iter]);
        if (TERMINATE || UNBOUNDED)
            break;

        tables.push_back(new_table);
      }
    vector<vector<double> > final_table = tables[(int) tables.size() - 1];
    for (int r = 1; r < 1 + m; r++) 
	  {
        if (final_table[r][0] == -M)
            INFEASIBLE = true;
      }

    if (cut != 0) cout << "Simplex Table after new Gomory Cut : \n";
    else cout << "\n Initial Optimal Simplex Table :  \n";
    print_tableau(final_table);

    if (INFEASIBLE)
         cout<<"\nThe LPP INFEASIBLE !!\n\n";
    
    else if (UNBOUNDED)
        cout<<"\nThe LPP is UNBOUNDED !!\n\n";
    
    else 
	{
        int fact = (MAX) ? 1 : -1;
        double objective_value = fact*final_table[m + 1][2 + n + extra_var];
        cout << "\nOptimum value of LPP : " << objective_value << endl;
        cout << "The optimum occurs at : ";
        for (int r = 1; r < 1 + m; r++) 
		  {
            if (final_table[r][1] <= n) 
			  {
                values[final_table[r][1] - 1] = final_table[r][2 + n + extra_var];
              }
          }
        for (int i = 0; i < n; i++) 
		  {
            cout << "x" << i + 1 << " = " << values[i] << "   ";
          }
        cout << "\n\n";
    }

    all_integer = true;
    int frac_var = -1; double max_frac_part = 0;
    for (int i = 0; i < (int) values.size(); i++) 
	  {
        if (min(ceil(values[i]) - values[i], values[i] - floor(values[i])) > 0.001) 
		  {
            all_integer = false;
            if (values[i] - floor(values[i]) > max_frac_part) 
			  {
                frac_var = i + 1;
                max_frac_part = values[i] - floor(values[i]);
              }
          }
      }

    vector<double> new_constraint_coeff(n + extra_var);

    if (frac_var == -1) 
	  {
        return new_constraint_coeff;
      }

    int frac_var_row = -1;
    for (int r = 1; r < 1 + m; r++) 
	  {
        if (abs(final_table[r][1] - frac_var) < 0.01) 
		  {
            frac_var_row = r;
          }
      }
    for (int c = 2; c < 2 + n + extra_var; c++) 
	  {
        new_constraint_coeff[c - 2] = final_table[frac_var_row][c] - floor(final_table[frac_var_row][c]);
        if (new_constraint_coeff[c - 2] >= 0.999) 
		  {
            new_constraint_coeff[c - 2] = 0;
          }
      }
    double new_RHS = final_table[frac_var_row][2 + n + extra_var] - floor(final_table[frac_var_row][2 + n + extra_var]);
    if (new_RHS >= 0.999) 
	  {
        new_RHS = 0;
      }
    new_constraint_coeff.push_back(new_RHS);
    cut++;
    return new_constraint_coeff;
}

int main() 
{
	cout << fixed << setprecision(2);
	int i,j,n,m;
	cout << "Enter the number of variables : ";
 	cin >> n;
	cout << "\nEnter the number of constraints : "; 
	cin >> m;
	b.resize(m); A.resize(m);
	int ch;
	cout << "\nEnter 1 if it is a maximization problem, 0 otherwise : "; 
	cin >> ch;
	if (ch == 1)
	  MAX = true;
	cout << "\nEnter the coefficients of the variables in objective function : ";
	for (int i = 0; i < n; i++) 
	  {
		double coeff; 
		cin >> coeff;
		if (!MAX) 
		  coeff *= -1;            // If it is a minimization problem, then take negative of all coefficients
		obj_coeff.push_back(coeff);
	  }

    int extra_var = 0;
    vector<int> initial_basis;
    vector<int> slack_eqns, surplus_eqns, artificial_eqns;
    vector<int> slack_idx, surplus_idx, artificial_idx;
    for (int i = 0; i < m; i++) 
	{
        cout << "\nEnter the coefficients of variables in constraint "<<i+1<<" : ";
        vector<double> coeff_here(n);
        for (int j = 0; j < n; j++) 
		  {
            cin >> coeff_here[j];
            A[i].push_back(coeff_here[j]);
          }
        int type;
        cout<<"\nEnter the type of constraint (1 for <= type , 2 for >= type , 0 for = type) : ";
        cin >> type;
        if (type == 1) 
		  {
        	extra_var++;
        	slack_eqns.push_back(i + 1);
        	slack_idx.push_back(n + extra_var);
        	initial_basis.push_back(n + extra_var);
          } 
        else if (type == 2) 
		  {
        	extra_var++;
        	surplus_eqns.push_back(i + 1);
        	surplus_idx.push_back(n + extra_var);

        	extra_var++;
        	artificial_eqns.push_back(i + 1);
        	artificial_idx.push_back(n + extra_var);
        	initial_basis.push_back(n + extra_var);
          }
        else 
		  {
        	extra_var++;
        	artificial_eqns.push_back(i + 1);
        	artificial_idx.push_back(n + extra_var);
        	initial_basis.push_back(n + extra_var);
          }
        cout << "\nEnter RHS of the constraint : "; cin >> b[i];
    }
    
    while (obj_coeff.size() != n + extra_var)
    	obj_coeff.push_back(0);
    
    
    vector<int>::iterator it;
    for(it=artificial_idx.begin();it!=artificial_idx.end();it++)
      {
      	obj_coeff[*it -1] = -M;
	  }
    
    for (int r = 0; r < m; r++) 
	  {
    	while (A[r].size() != n + extra_var)
    		A[r].push_back(0);
      }
    for (int i = 0; i < (int) slack_idx.size(); i++) 
	  {
    	A[slack_eqns[i] - 1][slack_idx[i] - 1] = 1;
      }
    for (int i = 0; i < (int) surplus_idx.size(); i++) 
	  {
    	A[surplus_eqns[i] - 1][surplus_idx[i] - 1] = -1;
      }
    for (int i = 0; i < (int) artificial_idx.size(); i++) 
	  {
    	A[artificial_eqns[i] - 1][artificial_idx[i] - 1] = 1;
      }

    all_integer = false;
    
    do {
        vector<double> new_constraint_coeff = BigM(A, b, initial_basis, n, m, extra_var);
        for (int i = 0; i < A.size(); i++) 
		  {
            A[i].push_back(0); A[i].push_back(0);         /// 2 new variables will be added
          }
        b.push_back(new_constraint_coeff[(int) new_constraint_coeff.size() - 1]);
        new_constraint_coeff.pop_back();
        extra_var += 2;
        new_constraint_coeff.push_back(-1); new_constraint_coeff.push_back(1);
        initial_basis.push_back(n + extra_var);
        m += 1;
        A.push_back(new_constraint_coeff);
        obj_coeff.push_back(0);
        obj_coeff.push_back(-M);

        TERMINATE = false, UNBOUNDED = false, INFEASIBLE = false;
    } while (!all_integer);

    return 0;
}
