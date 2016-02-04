#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool is_valid(const vector<vector<bool> > &beasts, const int row, const int col) {
    for(int i = 0; i < col; i++) {
        if(beasts[row][i]) { return false; }
    }
    for(int i = 1; row - i >= 0 && col - i >= 0; i++) {
        if(beasts[row - i][col - i]) { return false; }
    }
    for(int i = 1; row + i < beasts.size() && col - i >= 0; i++) {
        if(beasts[row + i][col - i]) { return false; }
    }
    return true;
}

bool solve(vector<int> &solution, vector<vector<bool> > &beasts, const int row, const int col, queue<int> q) {
    beasts[row][col] = true;
    bool valid = is_valid(beasts, row, col);
    solution[col] = row + 1;
    if(!valid) { beasts[row][col] = false; return false; }
    else if(valid && col == beasts.size() - 1) { return true; }

    int first = q.front();
    do {
        int next = q.front();
        q.pop();
        bool found = solve(solution, beasts, next, col + 1, q);
        if(found) { return true; }
        q.push(next);
    } while(first != q.front() && col < beasts.size() - 1);

    beasts[row][col] = false;
    return false;
}

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        int n;
        cin >> n; /* 1 <= n <= 30 */
        vector<int> solution(n);
        vector<vector<bool> > beasts(n, vector<bool>(n, false));
        bool solution_found = false;
        queue<int> q;
        for(int i = 0; i < n; i++) { q.push(i); }
        int first = q.front();
        do {
            int next = q.front();
            q.pop();
            solution_found = solve(solution, beasts, next, 0, q);
            if(solution_found) {
                break;
            }
            q.push(next);
        } while (q.front() != first);
        if(!solution_found) {
            cout << "Impossible\n";
        }
        else {
            for(int i = 0; i < n; i++) {
                cout << solution[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
