#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef unsigned int u_int;

vector<vector<int> > crossings;
string end_results;
int s; /*starting point, s != t, s >= 0*/
int t; /*destination point, t =< n - 1*/

void bfs(vector<bool> &reachable, const vector<bool> &visited) {
	queue<int> q;
	q.push(t);
	while(!q.empty()) {
		int current = q.front();
		q.pop();
		reachable[current] = true;
		for(int i = 0; i < crossings[current].size(); i++) {
			int next = crossings[current][i];
			if(!visited[next] && !reachable[next]) {
				q.push(next);
			}
		}
	}
}

int search_paths(vector<bool> &visited, string path, int current) {
	if(current == t) { // reached destination, append solution to result vector
		end_results.append(path);
		end_results.append("\n");
		return 1;
	}
	// sill on the path, check if valid solution, continue if yes
	visited[current] = true;
	vector<bool> reachable(crossings.size(), false);
	bfs(reachable, visited);
	int res_count = 0;
	for(u_int i = 0; i < crossings[current].size(); i++) {
		int next = crossings[current][i];
		if(!visited[next] && reachable[next]) {
			path.append(" " + to_string(next));
			res_count += search_paths(visited, path, next);
			path.resize(path.length() - 2);
		}
	}
	visited[current] = false;
	return res_count;
}

int main() {
    int tests; /*t =< 20*/
    cin >> tests;
	end_results = "";
    while(tests--) {
        int n; /*crossings, 1 =< n =< 30*/
        int m; /*streets, 0 =< m =< 435*/
        cin >> n >> m >> s >> t;
		crossings = vector<vector<int> >(n);
        for(int i = 0; i < m; i++) {
        	int a, b;
			cin >> a >> b;
			crossings[a].push_back(b);
			crossings[b].push_back(a);
        }

		// sort vectors
		for(int i = 0; i < n; i++) {
			sort(crossings[i].begin(), crossings[i].end());
		}

		// computation
		vector<bool> visited(n, false);
		string path;
		path.append(to_string(s));
		int res_count = search_paths(visited, path, s);
		end_results.append(to_string(res_count));
		end_results.append("\n");
    }
	cout << end_results;
    return 0;
}
