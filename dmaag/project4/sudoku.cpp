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
            break;
         }

      }
      m[idx_next] = 0;
   }
   return has_solution;
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
      has_solution = solve(q, m);
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
