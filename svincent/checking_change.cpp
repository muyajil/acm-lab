#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int c;
		cin >> c;
		int m;
		cin >> m;
		vector<int> values(c);
		for (int i = 0 ; i < c ; i ++)
		{
			cin >> values[i];
		}
		vector<int> ts (m);
		int t_max = 0;
		for (int i = 0; i < m; i++)
		{
			cin >> ts[i];
			t_max = max(t_max, ts[i]);
		}
		vector<int> mins(t_max+1, -1);
		mins[0] = 0;
		for (int i = 1; i < t_max+1; i++)
		{
			int min_s = 100000;
			for(int j = 0; j < c; j++)
			{
				if (i - values[j] >= 0)
				{
					if (mins[i-values[j]] != -1)
					{
						min_s = min(min_s,mins[i-values[j]] + 1);
					}
				}
			}
			mins[i] = min_s;
		}
		for (int i = 0; i < m; i++)
		{
			if (mins[ts[i]] == -1 || mins[ts[i]] == 100000)
			{
				cout << "not possible" << endl;
			} else {
				cout << mins[ts[i]] << endl;
			}
		}
	}
}
