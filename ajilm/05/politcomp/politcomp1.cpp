#include <iostream>
#include <vector>
#include <algorithm>

/*

Idea: 
We will run Kruskal once for the cost and once for the time.
We will use union find to find out if new edges create cycles

*/

using namespace std;

struct edge {
    int city1;
    int city2;
    int time;
    int cost;
    int id;
};

//vector for union find
vector<int> cities;

//Keep track of number of unions
int unions;

//function for finding representative
int find(int x){
    while(cities[x] != x){
        x = cities[x];
    }
    return x;
}

//function for unifying to sets
void unify(int u, int v){
    int parent1, parent2;
    parent1 = find(u);
    parent2 = find(v);
    if(parent1 < parent2){
        cities[parent1] = parent2;
    } else {
        cities[parent2] = parent1;
    }
}

//function for comparing time
bool sort_time(edge &x, edge &y){
    return x.time < y.time;
}

//function for comparing cost
bool sort_cost(edge &x, edge &y){
    return x.cost < y.cost;
}

//function for comparing id
bool sort_id(edge &x, edge &y){
    return x.id < y.id;
}

//Initialize cities array
void init_cities(int num_cities){
    cities.clear();
    for(int i = 0; i < num_cities; i++){
        //Initially all nodes are their own unions/representatives
        cities.push_back(i);
    }
    //Set union count
    unions = cities.size();
}

//The Kruskal algorithm
vector<edge> kruskal(bool time, int num_cities, vector<edge> &streets){
    //Sort edges by time
    if(time){
        sort(streets.begin(), streets.end(), sort_time);
    //Sort edges by cost
    } else {
        sort(streets.begin(), streets.end(), sort_cost);
    }
    //initiliaze union find array
    init_cities(num_cities);
    
    //Vector that will hold all edges making up the MST
    vector<edge> result;
    
    //Take cheapest edge and push it to the result
    edge cheapest = streets[0];
    result.push_back(cheapest);
    
    //First unify the two cities
    unify(cheapest.city1, cheapest.city2);
    unions--;
    
    //Mark current edge position in array
    int edge_pos = 1;
    
    //Now comes the actual algorithm
    //The graph is always connected, so we can assume there is always a MST
    while(unions > 1){
        edge current = streets[edge_pos];
        if(find(current.city1) != find(current.city2)){
            unify(current.city1, current.city2);
            unions--;
            result.push_back(current);
        }
    }
    
    //Now we have the result vector, we need to sort it by id for comparison
    sort(result.begin(), result.end(), sort_id);
    
    //Now we can return it
    return result;
}

bool compare_mst(vector<edge> &time, vector<edge> &cost){
    if(time.size() != cost.size()){
        return false;
    }
    
    for(int i = 0; i < time.size(); i++){
        if(time[i].id != cost[i].id) return false;
    }
    return true;
}

int main(){
    
    int num_islands; cin >> num_islands;
    while(num_islands--){
        // read the number of cities and roads
        int num_cities, num_roads;
        cin >> num_cities >> num_roads;
        vector<edge> streets(num_roads);
        for(int i = 0; i < num_roads; i++){
            // read parameters of edges
            int city1, city2, time, cost;
            cin >> city1 >> city2 >> time >> cost;
            edge current_edge = {city1, city2, time, cost, i};
            streets[i] = current_edge;
        }
        vector<edge> mst_time = kruskal(true, num_cities, streets);
        vector<edge> mst_cost = kruskal(false, num_cities, streets);
        if(compare_mst(mst_time, mst_cost)){
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    
    return 0;
}
