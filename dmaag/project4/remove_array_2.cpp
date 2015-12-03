#include <iostream>
#include <vector>
#include <climits>
//#include <cmath>

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
         suma = 0; sumb = 0;
         int current_a = a[i];
         int current_b = b[k];

         for(int l = i; l >= 0; l--) {
            suma += a[l];
            int newSum = current_b * suma + m[(l - 1) * n + k - 1];
            if(m[i * n + k] > newSum) {
               m[i * n + k] = newSum;
            }
         }

         sumb += current_b; // first case already looked at
         for(int l = k - 1; l >= 0; l--) {
            sumb += b[l];
            int newSum = current_a * sumb + m[(i - 1) * n + l - 1];
            if(m[i * n + k] > newSum) {
               m[i * n + k] = newSum;
            }
         }

      }
   }

   cout << m[n * n - 1] << endl;

   return 0;
}
