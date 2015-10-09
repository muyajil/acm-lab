#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int t;
	cin >> t;
	vector <bool> table(t);
	vector <int> sums(t);
	int b;
	int n = t;
	while(t--)
	{
		cin >> b;
		if(b){
			table[t] = true;
		}
	}
	sums[0] = (table[0])? 0:1;
	for(int i = 1; i < n; i++)
	{
		if (table[i])
		{
			sums[i] = i - sums[i-1];
		} else {
			sums[i] = sums[i-1] + 1;
		}
	}
	int sum = 0;
	for (int j = 0; j < n; j++)
	{
		sum += sums[j];
	}
	cout << sum << endl;
}
