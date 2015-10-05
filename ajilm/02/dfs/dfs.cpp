#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs_visit(int visiting, vector<vector<int> > &graph, vector<int> &enter, vector<int> &leave, int timer){
  //this is when first visiting a node
  enter[visiting] = timer++;
  for(int i = 0; i < graph[visiting].size(); i++){
    int next_vertex = graph[visiting][i];
    if(enter[next_vertex] == -1){ //if not visited yet
      timer = dfs_visit(next_vertex, graph, enter, leave, timer); // timers new value is when returning from the next vertex
    }
  }
  leave[visiting] = timer++;
  return timer;
}

void dfs(vector<vector<int> > &graph, vector<int> &enter, vector<int> &leave){
  int timer = 0;
  for(int i = 0; i < enter.size(); i++){
    if(enter[i] == -1){ //not visited yet
      timer = dfs_visit(i, graph, enter, leave, timer); //time takes the value that returns from the first node
    }
  }
}

int main(){
  int num_testcases;
  cin >> num_testcases;
  for(int i = 0; i < num_testcases; i++){
    int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;
    vector<vector<int> > graph(num_vertices);
    //cout << "reading graph\n";
    for(int i = 0; i < num_edges; i++){
      int first, second; cin >> first >> second;
      graph[first].push_back(second);
      graph[second].push_back(first);
    }
    for(int i = 0; i < graph.size(); i++){
      sort(graph[i].begin(),graph[i].end());
    }
    vector<int> enter(num_vertices,-1);
    vector<int> leave(num_vertices,-1);
    dfs(graph,enter,leave);
    for(int i = 0; i < num_vertices; ++i) cout << enter[i] << " ";
		cout << "\n";

		for(int i = 0; i < num_vertices; ++i) cout << leave[i] << " ";
		cout << "\n";
  }
  return 0;
}
