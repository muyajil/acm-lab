#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

int main(){
        int num_test; cin >> num_test;
        while(num_test--) {
                //begin parsing graph
                int num_vertices, num_edges; cin >> num_vertices >> num_edges;
                vector<vector<int> > graph(num_vertices);
                for (int i = 0; i < num_edges; i++) {
                        int first, second; cin >> first >> second;
                        graph[first].push_back(second);
                        graph[second].push_back(first);
                }
                //end parsing graph

                vector<int> groups(num_vertices,-1); //vector for storing num_groups per vertex
                //begin inding num_groups
                int group_nr = 0;
                for(int i = 0; i < num_vertices; i++) {
                        if(groups[i] < 0) { //if the vertex was not yet visited
                                //begin bfs from this node
                                //all the reachable nodes are in the same group
                                queue<int> q; //stack
                                q.push(i); //push current node onto stack
                                while(!q.empty()) {
                                        int cur = q.front(); //get next node
                                        groups[cur] = group_nr;
                                        for(int i = 0; i < graph[cur].size(); i++) { //for all neighbours
                                                if(groups[graph[cur][i]] < 0) { //if vertex was not visited yet
                                                        groups[graph[cur][i]] = group_nr;
                                                        q.push(graph[cur][i]); //push onto stack
                                                }
                                        }
                                        q.pop(); //pop last node
                                }
                                //end bfs for one node
                                group_nr++; //next bfs will have other group_nr
                        }
                }
                int num_groups = group_nr;
                //end finding num_groups
                vector<int> vertices(num_groups); //number of vertices per group
                vector<int> edges(num_groups); //number of edges per group
                vector<int> faces(num_groups); //number of faces per group
                for(int i = 0; i < num_vertices; i++) { //for all vertices
                        vertices[groups[i]]+=1; //add one vertex to the respective group
                        edges[groups[i]] += graph[i].size(); //add all the edges to neighbours to the respective group
                }
                for(int i = 0; i < num_groups; i++) { //for all groups
                        edges[i]/=2;
                        faces[i]=2-vertices[i]+edges[i]; //apply eulers formula
                }
                int num_faces = accumulate(faces.begin(), faces.end(), 0); //sum all faces
                num_faces-=(num_groups-1); //subtract outer regions that were added too much
                cout << num_faces << endl;
        }
}
