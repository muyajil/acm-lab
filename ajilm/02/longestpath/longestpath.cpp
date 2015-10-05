#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> find_furthest_vertex(vector<vector<int> > &graph, int starting_vertex){
        queue<int> queue;
        queue.push(starting_vertex);
        vector<int> depth(graph.size(), -1); depth[starting_vertex] = 1;
        while(!queue.empty()){
                int cur_vertex = queue.front();
                for(int i = 0; i < graph[cur_vertex].size(); i++){
                        int next_vertex = graph[cur_vertex][i];
                        if(depth[next_vertex] < 0){
                                depth[next_vertex] = depth[cur_vertex]+1;
                                queue.push(next_vertex);
                        }
                }
                queue.pop();
        }
        int furthest_vertex = 0;
        for(int i = 0; i < depth.size(); i++){
                if(depth[i]>=depth[furthest_vertex]){
                        furthest_vertex = i;
                }
        }
        vector<int> furthest(2);
        furthest[0] = furthest_vertex;
        furthest[1] = depth[furthest_vertex];
        return furthest;
}

int main(){
        int num_test; cin >> num_test;
        while(num_test--){
                int num_vertices; cin >> num_vertices;
                vector<vector<int> > graph(num_vertices);

                //begin graph reading
                for(int i = 0; i < num_vertices-1; i++){
                        int first, second; cin >> first >> second;
                        graph[first].push_back(second);
                        graph[second].push_back(first);
                }
                //end graph reading

                //start bfs from node 0
                vector<int> furthest_from_zero = find_furthest_vertex(graph,0);
                //start bfs from furthest node
                vector<int> longest_path = find_furthest_vertex(graph,furthest_from_zero[0]);
                cout << longest_path[1] << endl;
        }
}
