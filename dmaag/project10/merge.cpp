#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        int m;
        cin >> m;
        priority_queue<int> q;
        for(int i = 0; i < m; i++) {
            int next;
            cin >> next;
            q.push(-next); // enqueue with minus to sort increasingly
        }

        int sum = 0;
        bool calculating = true;
        while(calculating) {
            int first = - q.top(); q.pop();
            int second = - q.top(); q.pop();
            first = first + second;
            sum += first - 1;
            if(q.empty()) {
                calculating = false;
            }
            q.push(-first);
        }
        cout << sum << endl;
    }
    return 0;
}
