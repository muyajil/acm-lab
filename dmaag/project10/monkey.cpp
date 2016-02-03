#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

void bfs(const vector<vector<int> > &graph, vector<bool> &built, vector<bool> &covered, int cur) {
    queue<int> q;
    q.push(cur);
    vector<bool> visited(graph.size(), false);
    visited[cur] = true;
    while(!q.empty()) {
        int c = q.front();
        q.pop();
        visited[c] = true;
        built[c] = false;
        covered[c] = true;
        for(int i = 0; i < graph[c].size(); i++) {
            int next = graph[c][i];
            if(!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    built[cur] = true;
}

/* all indices from 1 to n so the first element of each vector is 0!! */
int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        int locations, roads;
        cin >> locations >> roads;
        vector<vector<int> > streets(locations + 1);
        for(int i = 1; i < roads + 1; i++) { // graph
            int a, b;
            cin >> a >> b;
            streets[a].push_back(b);
        }

        vector<pair<int, int> > costs(locations); // first: cost, second: ID
        for(int i = 0; i < locations; i++) { // costs
            int c;
            cin >> c;
            costs[i] = make_pair(c, i + 1);
        }
        sort(costs.begin(), costs.end());

        vector<bool> visited(locations + 1, false);
        vector<bool> built(locations + 1, false);

        for(int i = 0; i < locations; i++) {
            pair<int, int> current = costs[i];
            if(!visited[current.second]) {
                bfs(streets, built, visited, current.second);
            }
        }

        int totalcosts = 0;
        for(int i = 0; i < locations; i++) {
            pair<int, int> p = costs[i];
            if(built[p.second]) {
                totalcosts += p.first;
            }
        }

        cout << totalcosts << endl;
    }
    return 0;
}
