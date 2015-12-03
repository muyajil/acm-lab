#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> a;
vector<int> b;
vector<int> m;
int *res;
int n;

void mout() {
   for(int i = 0; i < n; i++) {
      for(int k = 0; k < n; k++) {
         cout << m[i * n + k] << " ";
      }
      cout << endl;
   }
}

void check_possible_solution(int index_a, int index_b, int sum) {
   if(index_a >= n || index_b >= n) {return;}

   int current_b = b[index_b];
   int suma = 0;
   for(int offset = index_a; offset < n; offset++) {
      suma += a[offset];
      int ca = sum + current_b * suma;
      if(ca < m[offset * n + index_b] && ca < *res) {
         m[offset * n + index_b] = ca;
         check_possible_solution(offset + 1, index_b + 1, ca);
      }
      else {
         //break;
      }
   }

   int current_a = a[index_a];
   int sumb = 0;
   for(int offset = index_b; offset < n; offset++) {
      sumb += b[offset];
      int cb = sum + current_a * sumb;
      if(cb < m[index_a * n + offset] && cb < *res) {
         m[index_a * n + offset] = cb;
         check_possible_solution(index_a + 1, offset + 1, cb);
      }
      else {
         //break;
      }
   }
   return;
}

int main() {
   cin >> n;
   a = vector<int>(n);
   b = vector<int>(n);
   for(int i = n - 1; i >= 0; i--) {
      cin >> a[i];
   }
   for(int i = n - 1; i >= 0; i--) {
      cin >> b[i];
   }

   //calc
   m = vector<int>(n * n, INT_MAX);
   res = &m[n * n - 1];

   check_possible_solution(0, 0, 0);

   mout();

   cout << *res << endl;

   return 0;
}
