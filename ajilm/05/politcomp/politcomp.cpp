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
    edge(int a, int b, int c, int d): city1(a), city2(b), time(c), cost(d) { }
    int city1, city2, time, cost;
};

//function for finding representative
int find(int x, vector<int> &cities){
    if(cities[x] == x){
        return x;
    }
    return cities.at(x) = find(cities.at(x), cities);
}

//function for unifying to sets
bool unify(int u, int v, vector<int> &cities){
    int parent1 = find(u, cities);
    int parent2 = find(v, cities);
    if(parent1 != parent2){
        cities.at(parent1) = parent2;
        return true;
    } else {
        return false;
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

//The Kruskal algorithm
int kruskal(int num_cities, vector<edge> &streets){
    //Keep track of total cost
    int total_cost = 0;
    
    //union find array
    vector<int> cities(num_cities);
    for(int i = 0; i < num_cities; i++){
        cities.at(i)=i;
    }
    int unions = num_cities;
    
    //Take cheapest edge  
    edge cheapest = streets[0];
    
    //Mark current edge position in array
    int edge_pos = 0;
    
    //Now comes the actual algorithm
    //The graph is always connected, so we can assume there is always a MST
    while(unions > 1){
        edge current = streets.at(edge_pos);
        edge_pos++;
        if(unify(current.city1, current.city2, cities)){
            total_cost += current.cost;
            unions--;
        }
    }
    
    //Now we can return the total cost
    return total_cost;
}

int main(){
    
    int num_islands; cin >> num_islands;
    while(num_islands--){
        // read the number of cities and roads
        int num_cities, num_roads;
        cin >> num_cities >> num_roads;
        vector<edge> streets;
        streets.reserve(num_roads);
        for(int i = 0; i < num_roads; i++){
            // read parameters of edges
            int city1, city2, time, cost;
            cin >> city1 >> city2 >> time >> cost;
            streets.push_back(edge(city1, city2, time, cost));
        }
        
        //Sort edges by time and find MST
        sort(streets.begin(), streets.end(), sort_time);
        int mst_time = kruskal(num_cities, streets);
        
        //Sort edges by cost and find MST
        sort(streets.begin(), streets.end(), sort_cost);
        int mst_cost = kruskal(num_cities, streets);
        
        if(mst_time == mst_cost){
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    
    return 0;
}
