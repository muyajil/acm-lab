#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
   int n;
   cin >> n;
   vector<int> a(n);
   vector<int> b(n);
   for(int i = n - 1; i >= 0; i--) {
      cin >> a[i];
   }
   for(int i = n - 1; i >= 0; i--) {
      cin >> b[i];
   }

   //calc
   vector<int> m(n * n, INT_MAX);

   //new solution
   int suma = 0, sumb = 0;
   for(int i = 0; i < n; i++) {
      suma += a[i];
      m[i] = sumb * a[0];
      sumb += b[i];
      m[i * n] = suma * b[0];
   }

   for(int i = 1; i < n; i++) {
      for(int k = 1; k < n; k++) {
         //fill new cell
         for(int l = 1)
      }
   }

   //mout();

   cout << *res << endl;

   return 0;
}
