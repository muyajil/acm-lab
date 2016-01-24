#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int city1, city2, cost;
    Edge(int a, int b, int c) : city1(a), city2(b), cost(c) { }
};

int find(int x, vector<int> &array){
    if(array[x] == x) return x;
    return array[x] = find(array[x], array);
}

bool unify(int a, int b, vector<int> &array){
    int parent1 = find(a, array);
    int parent2 = find(b, array);
    if(parent1 != parent2){
        array[parent1] = parent2;
        return true;
    }
    return false;
}

bool compare_cost(Edge &x, Edge &y){
    return x.cost < y.cost;
}

vector<int> kruskal(int num_cities, vector<Edge> &links, vector<int> &city_repr){
    
    vector<int> costs(num_cities,0);
    
    for(vector<Edge>::const_iterator iter = links.begin(); iter != links.end(); ++iter){
        Edge current = *iter;
        if(unify(current.city1, current.city2, city_repr)){
            //this means we use this edge, but where to add the cost? -> to the parent!
            //The problem is that the cost is now distributed transitively
            costs[find(current.city1, city_repr)]+=current.cost;
        }
    }
    
    return costs;
}

int main(){
    std::ios_base::sync_with_stdio(false);

    int num_datasets; cin >> num_datasets;
    while(num_datasets--){
        int num_villages, num_links;
        cin >> num_villages >> num_links;
        vector<Edge> links;
        links.reserve(num_links);
        for(int i = 0; i < num_links; i++){
            int city1, city2, cost;
            cin >> city1 >> city2 >> cost;
            links.push_back(Edge(city1, city2, cost));
        }
        sort(links.begin(), links.end(), compare_cost);
        vector<int> city_repr(num_villages);
    
        for(int i = 0; i < num_villages; i++){
            city_repr[i] = i;
        }
        vector<int> costs = kruskal(num_villages, links, city_repr);
        
        for(int i = 0; i < num_villages; i++){
            if(costs[i] > 0){
                int parent = find(i, city_repr);
                if(parent != i){
                    costs[parent]+=costs[i];
                    costs[i] = 0;
                }
            }
        }
        
        
        int num_islands = 0;
        int cheapest_network = 999999999;
        for(int i = 0; i < num_villages; i++){
            if(costs[i] > 0){
                if(costs[i] < 1000000){
                    num_islands++;
                }
                if(costs[i] < cheapest_network){
                    cheapest_network = costs[i];
                }
            }
            
        }
        cout << num_islands << " " << cheapest_network << endl;
    }
    return 0;
}
