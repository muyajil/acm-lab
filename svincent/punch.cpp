#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		int k;
		cin >> n; /* max = 100 */
		cin >> k; /* max = 10000 */
		vector<int> costs (n);
		vector<int> volumes (n);
		for (int i = 0; i < n; i++)
		{
			cin >> costs[i] >> volumes[i];
		}
		int lits = k+1;
		vector<int>tableau(n*lits); /* cost of cheapest punch */
		vector<int>tab2(n*lits);
		for (int i = 0; i < n; i++)
		{
			tableau[i*lits] = 0;
		}
		for (int j = 1; j < lits; j++)
		{
			// TODO: optimize this
			int q = (j % volumes[0])? j/volumes[0]+1 : j/volumes[0];
			tableau[j] = q * costs[0];
		}
		for (int i = 1; i < n; i++)
		{
			for (int j = 1; j < lits; j++)
			{
				if (j - volumes[i] >= 0)
					tableau[i*lits+j] = min(tableau[i*lits+(j-volumes[i])] + costs[i], tableau[(i-1)*lits+j]);
				}
				else {
					tableau[i*lits+j] = tableau[(i-1)*lits+j];
				}
			}
		}
		int count = 0;
		int m = n-1;
		int lit = k;
		vector<bool> flags(n);
		while (lit > 0 && m >= 0)
		{
			if (tableau[m*lits+lit] == tableau[(m-1)*lits+lit])
			{
				m--;
			} else {
				flags[m] = true;
				lit = lit - volumes[m];
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (flags[i])
			{
				count++;
			}
		}

		cout << tableau[(n-1)*lits+k] << " " << count << endl;
	}
}






