#include <vector>
#include <iostream>

typedef unsigned int u_int;
using namespace std;

bool solve(vector<vector<int> > &tiles, vector<bool> &visited, int current) {
    if(visited[current]) { // either no solution possible or finished
        if(current != 0) { // no solution
            return false;
        }
        for(u_int i = 0; i < visited.size(); i++) {
            if(!visited[i]) {
                return false;
            }
        }
        // every point is visited and so we have a solution!
        return true;
    }
    else{ // not finished yet
        visited[current] = true;
        bool res = false;
        for(u_int i = 0; i < tiles[current].size(); i++ ) {
            int next = tiles[current][i];
            res = solve(tiles, visited, next);
            if(res) { return true; }
        }
        visited[current] = false;
	return false;
    }
}

int main(void) {
    int t;
    cin >> t;
    while(t--) {
        int n, s; // n=#dominoes, s=max spots on dominoe
        cin >> n >> s;
	    vector<vector<int> > tiles(s + 1);
        for(int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            tiles[u].push_back(v);
            tiles[v].push_back(u);
        }

        //impossible cases
        if(n <= s || s <= 1) { cout << "no\n"; continue; }
        
        //computation
        vector<bool> visited(s + 1, false);
        visited[0] = true;
        bool res = false;
        for(u_int i = 0; i < tiles[0].size(); i++) {
            res = solve(tiles, visited, tiles[0][i]);
            if(res) { break; }
        }

        // result output
        if(res) {
            cout << "yes\n";
        }
        else{
            cout << "no\n";
        }
    }
    return 0;
}
