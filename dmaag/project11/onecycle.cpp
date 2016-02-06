#include <vector>
#include <iostream>

using namespace std;

int dfs(const vector<vector<int> > &graph, vector<int> &depth, vector<bool> &visited, const int cur, const int last) {
    if(graph[cur].size() == 0) {
        return -1;
    }
    for(int i = 0; i < graph[cur].size(); i++) {
        int next = graph[cur][i];
        if(last == next) { continue; }
        if(visited[next]) {
            return depth[cur] - depth[next] + 1;
        }
        else{
            depth[next] = depth[cur] + 1;
            visited[next] = true;
            int result;
            result = dfs(graph, depth, visited, next, cur);
            if(result >= 0) {
                return result;
            }
        }
    }
    return -1;
}

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        int n;
        cin >> n;
        vector<vector<int> > graph(n);
        for(int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> depths(n, 0);
        vector<bool> visited(n, false);
        visited[0] = true;
        int res;
        res = dfs(graph, depths, visited, 0, 0);
        cout << res << endl;
    }
    return 0;
}
