#include <iostream>
#include <vector>
using namespace std;

int m;

void lp_dsf(int start, int src, vector<vector<int> > &graph, vector<int> &max_e, vector<int> &maxs)
{
	int len = graph[start].size();
	int max1 = 0;
	int max2 = 0;
	for(int i = 0; i < len; i++)
	{
		int node = graph[start][i];
		if(src == node)
		{
			continue;
		}
		lp_dsf(node, start, graph, max_e, maxs);
		if (max_e[node] > max1)
		{
			max2 = max1;
			max1 = max_e[node];
		} else if (max_e[node] > max2)
		{
			max2 = max_e[node];
		}
	}
	maxs[start] = max1 + max2 + 1;
	max_e[start] = max1 + 1;
        m = max(max(maxs[start], max_e[start]),m);
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		m = 0;
		int n;
		cin >> n;
		vector<vector<int> >graph(n);
		for (int i = 0; i < n-1; i++)
		{
			int s;
			int t;
			cin >> s;
			cin >> t;
			graph[s].push_back(t);
			graph[t].push_back(s);
		}
		vector<int> max_e (n);
		vector<int> maxs (n);
		lp_dsf(0,-1,graph, max_e, maxs);
		cout << m << endl;
	}
	return 0;
}
