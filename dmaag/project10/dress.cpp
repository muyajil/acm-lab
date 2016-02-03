#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int T; /* 1 <= T <= 5*/
    cin >> T;
    while(T--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int> > dep(n + 1);
        vector<int> indeg(n + 1);
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b; // a depends on b (b before a!)
            dep[b].push_back(a);
            indeg[a]++;
        }

        priority_queue<int> queue;
        for(int i = 1; i < n + 1; i++) {
            if(indeg[i] == 0) {
                queue.push(i);
            }
        }

        // calculations
        while(!queue.empty()) {
            int cur = queue.top();
            queue.pop();
            cout << cur << endl;
            for(unsigned int i = 0; i < dep[cur].size(); i++) {
                int next = dep[cur][i];
                indeg[next]--;
                if(indeg[next] == 0) {
                    queue.push(next);
                }
            }
        }
    }
    return 0;
}
