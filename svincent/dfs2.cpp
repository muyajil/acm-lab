#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t;

void dfs_visit(int p, vector<vector<int> > &graph, vector<int> &start, vector<int> &end)
{
	start[p] = t++;
	for (int i = 0; i < graph[p].size(); i++)
	{
		int y = graph[p][i];
		if(start[y] == -1) dfs_visit(y, graph, start, end);
	}
	end[p] = t++;
}

void dfs(vector<vector<int> > &graph, vector<int> &start, vector<int> &end)
{
	for (int i = 0; i < graph.size(); i++)
	{
		if (start[i] == -1) dfs_visit(i, graph, start, end);
	}
}

int main()
{
	int c;
	cin >> c;
	while(c--)
	{
		t = 0;
		int n;
		int m;
		cin >> n;
		vector<vector<int> > graph(n);
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			int k;
			int l;
			cin >> k;
			cin >> l;
			graph[k].push_back(l);
			graph[l].push_back(k);
		}
		for (int i = 0; i < n; i++)
		{
			sort(graph[i].begin(), graph[i].end());
		}
		vector<int> start_times(n, -1);
		vector<int> end_times(n, -1);
		dfs(graph, start_times, end_times);
		for(int i = 0; i < n-1; i++){
			cout << start_times[i] << " ";
		}
		cout << start_times[n-1] << endl;
		for(int i = 0; i < n-1; i++)
		{
			cout << end_times[i] << " ";
		}
		cout << end_times[n-1] << endl;
	}
}
