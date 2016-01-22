#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int u_int;

int s; /*starting point, s != t, s >= 0*/
int t; /*destination point, t =< n - 1*/

void search_paths(const vector<vector<int> > & crossings, string &end_results, int & count_res, vector<bool> &visited, vector<int> path) {
	int current = path.back();
	if(current == t) { // reached destination, append solution to result vector
		for(u_int i = 0; i < path.size(); i++) {
			end_results.append(to_string(path[i]));
			end_results.append(" ");
		}
		end_results.append("\n");
		count_res++;
		return;
	}
	// sill on the path, check if valid solution, continue if yes
	visited[current] = true;
	for(u_int i = 0; i < crossings[current].size(); i++) {
		int next = crossings[current][i];
		if(!visited[next]) {
			path.push_back(next);
			search_paths(crossings, end_results, count_res, visited, path);
			path.pop_back();
		}
	}
	visited[current] = false;
}

int main() {
    int tests; /*t =< 20*/
    cin >> tests;
	string results = "";
    while(tests--) {
        int n; /*crossings, 1 =< n =< 30*/
        int m; /*streets, 0 =< m =< 435*/
        cin >> n >> m >> s >> t;
		vector<vector<int> > crossings(n);
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
		int count_res = 0;
		vector<bool> visited(n, false);
		vector<int> path;
		path.push_back(s);
		search_paths(crossings, results, count_res, visited, path);
		results.append(to_string(count_res));
		results.append("\n");
    }
	cout << results;
    return 0;
}
