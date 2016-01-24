#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

int shortest_path(int start, int dest, vector<vector<pair<int, int> > > &graph){
    int num_cities = graph.size();
    priority_queue<pair<int, int> > queue;
    vector<bool> visited(num_cities, false);
    vector<int> distances(num_cities, numeric_limits<int>::max());
    distances[start] = 0;
    
    queue.push(make_pair(distances[start], start));
    
    while(!queue.empty()){
        pair<int, int> current_city = queue.top(); queue.pop();
        int current_city_id = current_city.second;
        //If we havent already visited this node
        if(!visited[current_city_id]){
            visited[current_city_id] = true;
            //Go through all the neighbours
            for(int i = 0; i < graph[current_city_id].size(); i++){
                int next_city_id = graph[current_city_id][i].first;
                //If we have not visited this neighbour yet
                if(!visited[next_city_id]){
                    //If the distance + weight of connection is smaller than current distance
                    if(distances[current_city_id] + graph[current_city_id][i].second < distances[next_city_id]){
                        distances[next_city_id] = distances[current_city_id] + graph[current_city_id][i].second;
                        queue.push(make_pair(-distances[next_city_id], next_city_id));
                    }
                }
            }
        }
    }
    
    return distances[dest];
    
}

int main(){
    int num_cases; cin >> num_cases;
    while(num_cases--){
        int num_cities, num_tracks, start, dest;
        cin >> num_cities >> num_tracks >> start >> dest;
        
        vector<vector<pair<int, int> > > graph(num_cities);
        
        for(int i = 0; i < num_tracks; i++){
            int city1, city2, cost;
            cin >> city1 >> city2 >> cost;
            graph[city1].push_back(make_pair(city2, cost));
            graph[city2].push_back(make_pair(city1, cost));
        }
        
        int cost = shortest_path(start, dest, graph);
    
        if(cost < numeric_limits<int>::max()){
            cout << cost << endl;   
        } else {
            cout << "Need a horse" << endl;
        }
    }
    return 0;
}
