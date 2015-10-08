#include <iostream>
#include <vector>
using namespace std;

void dfs(int class_cnt, vector<vector<int> > &graph, vector<int> &parts, int j)
{
	parts[j] = class_cnt;
	for (int i = 0; i < graph[j].size(); i++)
	{
		int t = graph[j][i];
		if (parts[t] == -1)
		{
			dfs(class_cnt, graph, parts, t);
		}
	}
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int v;
		int e;
		cin >> v;
		vector<vector<int> > graph(v);
		cin >> e;
		for (int j = 0; j < e; j++)
		{
			int temp;
			int temp2;
			cin >> temp;
			cin >> temp2;
			graph[temp].push_back(temp2);
			graph[temp2].push_back(temp);
		}
		vector<int> partitions(v, -1);
		vector<int> nnodes(v);
		int class_cnt = 0;
		for(int j = 0; j < v; j++)
		{
			nnodes[j] = graph[j].size();
			if (partitions[j] == -1)
			{
				dfs(class_cnt, graph, partitions,j);
				class_cnt++;
			}
		}
		vector<int> nodes(class_cnt, 0);
		vector<int> edges(class_cnt, 0);
		for (int j = 0; j < v; j++)
		{
			int part = partitions[j];
			nodes[part] += 1;
			edges[part] += nnodes[j];
		}
		int faces = 0;
		for(int j = 0; j < class_cnt; j++)
		{
			edges[j] /= 2;
			faces += 2 - nodes[j] + edges[j];
		}
		faces -= class_cnt-1;
		cout << faces << endl;
	}
	return 0;
}
