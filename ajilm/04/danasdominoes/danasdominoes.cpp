#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>

/*

Idea: Complete Search
We will construct a graph of the dominos.
The graph will have max_spots+1 nodes, each node representing a spot count.
An edge will be added in the graph between node i and node j if there is a stone with spots i and j.
After that we will search the graph for a cycle, namely a Hamiltonian Cycle, a cycle that visits each node exactly once.
*/


using namespace std;

int num_dominos, max_spots;

bool backtrack(int current, int length, vector<vector<int> > &graph, vector<int> &visited){
    //iterate through all the neighbours (i.e. through all the stones that have #current spots)
    for(int i = 0; i < graph[current].size(); i++){
        int next = graph[current][i]; //get the next node (i.e. the other number on the stone)
        if((next == 0) && (length == max_spots)) return true; //if the other number is 0 again, and the cycle is long enough, were finished
        if(!visited[next]){ //test if we already have this spot count in the cycle
            visited[next] = 1; 
            if(backtrack(next, length+1, graph, visited)) return true; //backtrack with the next node as starting point and the length incremented
            visited[next] = 0; //if backtrack returns false we cannot use this edge (i.e. this stone)
        }
    }
    return false;
}

int main(){
	int num_test; cin >> num_test;
	while(num_test--){
	    cin >> num_dominos >> max_spots; //read params
	    vector<vector<int> > graph(max_spots+1);
	    while(num_dominos--){
	        int first, second; cin >> first >> second; //read domino
	        graph[first].push_back(second);
	        graph[second].push_back(first);
	    }
	    
	    if(max_spots == 1){ //not possible with max spots only 1
	        cout << "no\n";
	        continue;
	    }
	    
	    vector<int> visited(max_spots+1, 0); //keep track of visited nodes
	    visited[0] = 1;
	    // we start the search from the node representing 0 spots, it does not matter which node we pick, because we need to visit all of them
	    if(backtrack(0,0,graph,visited)){
	        cout << "yes\n";
	    } else {
	        cout << "no\n";
	    }
    }
    return 0;
}
