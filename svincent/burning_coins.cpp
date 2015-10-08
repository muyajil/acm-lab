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
		cin >> n;
		if ( n == 0 )
		{
			cout << 0 << endl;
			return 0;
		}
		vector<int> coins(n*n);
		for (int i = 0; i < n; i++)
		{
			cin >> coins[i*n+i];
		}
		for (int i = 0; i < n-1; i++)
		{
			coins[i*n+(i+1)] = max(coins[i*n+i], coins[(i+1)*n+(i+1)]);
		}
		for (int i = n-3; i >= 0; i--)
		{
			for (int j = i+2; j < n; j++)
			{
				coins[i*n+j] = max( min( coins[i*n+i] + coins[(i+2)*n+j], coins[i*n+i] + coins[(i+1)*n+(j-1)]),
						    min( coins[j*n+j] + coins[i*n+(j-2)], coins[j*n+j] + coins[(i+1)*n+(j-1)]) );
			}
		}
		cout << coins[n-1] << endl;
	}
	return 0;
}
