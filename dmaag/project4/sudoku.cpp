#include <vector>
#include <iostream>
#include <queue>

using namespace std;

void printm(vector<int> &m) {
   for(int i = 0; i < 9; i++) {
      for(int k = 0; k < 9; k++) {
         cout << m[i * 9 + k] << " ";
      }
      cout << endl;
   }
}

bool check_whole(vector<int> &m) {
   vector<bool> has;
   for(int t = 0; t < 9; t++) { // tests
      has = vector<bool>(10, false);
      for(int l = 0; l < 9; l++) { // line test
         if(has[m[t * 9 + l]]) {
            return false;
         }
         has[m[t * 9 + l]] = true;
      }
      has = vector<bool>(10, false);
      for(int k = 0; k < 9; k++) { // column test
         if(has[m[k * 9 + t]]) {
            return false;
         }
         has[m[k * 9 + t]] = true;
      }
      has = vector<bool>(10, false);
      int sqare = (t % 9) / 3;
      for(int k = 0; k < 3; k++) { // sqare test
         for(int l = 0; l < 3; l++) {
            //cout << "index: " << (t / 3) * 3 + k << " " << sqare * 3 + l << ": " << m[(k + (t / 3) * 3) * 9 + sqare * 3 + l] << endl;
            if(has[m[(k + (t / 3) * 3) * 9 + sqare * 3 + l]]) {
               return false;
            }
            has[m[(k + (t / 3) * 3) * 9 + sqare * 3 + l]] = true;
         }
      }
      //cout << endl;
   }
   return true;
}

bool check(vector<int> &m, int index) {
   int c = m[index];
   m[index] = 0;
   int row = index / 9;
   //cout << endl;
   for(int i = 0; i < 9; i++) {
      //cout << c << ": (" << row << ", " << i << "), (" << i << ", " << index % 9 << ")" << endl;
      //cout << c << " == " << m[row * 9 + i] << " == " << m[i * 9 + index % 9] << endl;
      if(m[row * 9 + i] == c || m[i * 9 + index % 9] == c) {
         return false;
      }
   }
   int third = (index % 9) / 3;
   for(int i = 0; i < 3; i++) {
      for(int k = 0; k < 3; k++) {
         if(m[row * 9 + third * 3 + k] == c) {
            return false;
         }
      }
   }
   //cout << "true" << endl;
   m[index] = c;
   return true;
}

bool solve(queue<int> q, vector<int> &m) {
    if(q.empty()) {
        return true;
    }
   int idx_next = q.front();
   q.pop();
   bool has_solution = false;
   for(int i = 1; i < 10 && !has_solution; i ++) {
      m[idx_next] = i;
      if(check(m, idx_next)) {
         has_solution = solve(q, m);
         if(has_solution) {
            if(q.empty()) {
                return true;
            }
            else {
                break;
            }
         }

      }
      m[idx_next] = 0;
   }
   return has_solution;
}

bool check2(const vector<int> &m, const int current) {
    int row = current / 9;
    int col = current % 9;
    for(int i = 0; i < 9; i ++) {
        int index = row * 9 + i;
        if(m[index] == m[current] && index != current) { return false; }
        index = i * 9 + col;
        if(m[index] == m[current] && index != current) { return false; }
    }
    // TODO: check if in same square is a equal number
    

}

bool solve2(queue<int> q, vector<int> &m) {
    int current = q.front();
    q.pop();
    for(int i = 1; i <= 9; i++) {
        m[current] = i;
        if(!check2(m, current)) {
            m[current] = 0;
            continue;
        }
        if(solve2(q, m)) {
            return true;
        }
    }
    return false;
}

int main() {
   int t;
   cin >> t;
   while(t--) {
      vector<int> m(9 * 9);
      queue<int> q;
      for(int i = 0; i < 9 * 9; i++) {
         char c;
         cin >> c;
         int next = c - '0';
         if(next > 0 && next < 10) {
            m[i] = next;
         }
         else {
            q.push(i);
            m[i] = 0;
         }
      }

      // solve sudoku
      bool has_solution = false;
      printm(m);
      has_solution = solve2(q, m);
      //cout << endl;
      printm(m);

      has_solution = check_whole(m);

      if(has_solution){
         cout << 1 << endl;
      }
      else {
         cout << 0 << endl;
      }
   }
   return 0;
}

/*
1 5 6 8 3 7 1 4 9 2 9 1 2 4 8 5 3 6 7 4 3 7 6 9 2 5 1 8 1 2 4 ? ? ? 7 3 9 7 5 6 ? ? ? 2 8 1 8 9 3 ? ? ? 6 4 5 6 7 9 1 2 4 8 5 3 3 8 5 7 6 9 1 2 4 2 4 1 5 3 8 9 7 6
*/
