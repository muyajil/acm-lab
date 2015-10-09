#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<vector<int> > &graph, vector<int> &depths, queue<int> &q, int start)
{
	for(int i = 0; i < graph[start].size(); i++)
	{
		int p = graph[start][i];
		if (depths[p] == -1)
		{
			depths[p] = depths[start] + 1;
			q.push(p);
		}
	}
	if (q.size() != 0)
	{
		int v = q.front();
		q.pop();
		bfs(graph, depths, q, v);
	}
}

int main()
{
	int c;
	cin >> c;
	while(c--)
	{
		int n;
		int m;
		int v;
		cin >> n;
		vector<vector<int> > graph(n);
		cin >> m;
		cin >> v;
		for (int i = 0; i < m; i++)
		{
			int a;
			int b;
			cin >> a;
			cin >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		vector<int> depths(n, -1);
		queue<int> q;
		depths[v] = 0;
		bfs(graph, depths, q, v);
		for (int i = 0; i < n-1; i++)
		{
			cout << depths[i] << " ";
		}
		cout << depths[n-1] << endl;
	}
	return 0;
}
