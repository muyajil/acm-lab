#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<vector<int> > &graph, int starting_vertex, vector<int> &depth){
  depth[starting_vertex] = 0;
  queue<int> vertex_queue;
  vertex_queue.push(starting_vertex);
  while(!vertex_queue.empty()){
    int curr_vertex = vertex_queue.front();
    for(int i = 0; graph[curr_vertex].size(); i++){
      int next_vertex = graph[curr_vertex][i];
      if (depth[next_vertex] == -1){
        depth[next_vertex] = depth[curr_vertex]+1;
        vertex_queue.push(next_vertex);
      }
    }
    vertex_queue.pop();
  }
}

int main(){
  int num_test; cin >> num_test;
  while(num_test--){
    int num_vertices, num_edges, starting_vertex;
    cin >> num_vertices >> num_edges >> starting_vertex;
    vector<vector<int> > graph(num_vertices);
    for (int i = 0; i < num_edges; i++){
      int first, second;
      cin >> first >> second;
      graph[first].push_back(second);
      graph[second].push_back(first);
    }
    vector<int> depth(num_vertices,-1);
    //bfs(graph,starting_vertex, depth);

    depth[starting_vertex] = 0;
    queue<int> vertex_queue;
    vertex_queue.push(starting_vertex);
    while(!vertex_queue.empty()){
      int curr_vertex = vertex_queue.front();
      for(int i = 0; graph[curr_vertex].size(); i++){
        int next_vertex = graph[curr_vertex][i];
        if (depth[next_vertex] == -1){
          depth[next_vertex] = depth[curr_vertex]+1;
          vertex_queue.push(next_vertex);
        }
      }
      vertex_queue.pop();
    }

    
    cout << endl;
    for(int i = 0; i < depth.size(); i++){
      cout << depth[i] << " ";
    }
  }
}
