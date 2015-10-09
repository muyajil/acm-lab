#include <iostream>
#include <vector>
using namespace std;

struct node
{
	int value;
	int start;
	int end;
	bool visited;
	vector<int> neighbors;
}

vector<node> nodes;
int time;

void dfs(int i)
{
	nodes[i].start = time++;
	int len = nodes[i].neighbors.size();
	for (int j = 0; j < len; j++)
	{
		if (!nodes[neighbors[j]].visited)
		{
			dfs(neighbors[j]);
		}
	}
	nodes[i].end = time++;
}

int main()
{
	time = 0;
	int c;
	cin >> c;
	while(c--)
	{
		int nnodes;
		int nedges;
		cin >> nnodes;
		cin >> nedges;

		nodes(nnodes);
		for (int i = 0; i < nnodes; i++)
		{
			nodes.push_back(node());
			nodes[i].value = i;
		}
		for (int i = 0; i < nedges; i ++)
		{
			int s;
			int e;
			cin >> s;
			cin >> e;
			nodes[s].neighbors.push_back(e);
		}
		for (int i = 0; i < nnodes; i++)
		{
			sort(nodes[i].neighbors.begin(), nodes[i].neighbors.begin()+nodes[i].neighbors.size());
		}
	}
}
