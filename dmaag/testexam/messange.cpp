#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(const vector<vector<int> > &graph, int start) {
    vector<bool> visited(graph.size(), false);
    vector<int> depth(graph.size(), 0);
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    int maximum = 0;
    while(!queue.empty()) {
        int cur = queue.front();
        queue.pop();
        for(int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if(!visited[next]) {
                visited[next] = true;
                depth[next] = depth[cur] + 1;
                maximum = max(maximum, depth[next]);
                queue.push(next);
            }
        }
    }
    return maximum;
}

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int> > connected(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            connected[u - 1].push_back(v - 1);
            connected[v - 1].push_back(u - 1);
        }

        // calc
        int minimum = 200000;
        vector<int> depth(n);
        for(int i = 0; i < n; i++) {
            depth[i] = bfs(connected, i);
            minimum = min(minimum, depth[i]);
        }
        int i = 0;
        while(depth[i] > minimum) { i++; }
        cout << i + 1 << endl;
    }
    return 0;
}
