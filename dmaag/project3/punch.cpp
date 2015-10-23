#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct entry {
   int number_of_drinks;
   int volume;
   int price;
   bool came_from_left;
};

int main() {
   int t;
   cin >> t;
   while(t--) {
      int n, k;
      cin >> n >> k;
      vector<int> cost(n);
      vector<int> vol(n);
      for(int i = 0; i < n; i++) {
         cin >> cost[i] >> vol[i];
      }

      // calcu
      entry init = {0, 0, 0, true};
      vector<entry> matrix((k + 1) * n, init);
      for(int l = 1; l < k + 1; l++) {
         entry nentry = matrix[(l - 1) * n];
         nentry.came_from_left = false;

         if(nentry.volume < l) {
            nentry.number_of_drinks = 1;
            nentry.volume += vol[0];
            nentry.price += cost[0];
         }
         matrix[l * n] = nentry;
      }

      for(int l = 1; l < k + 1; l++) {
         for(int i = 1; i < n; i++) {

            entry left = matrix[l * n + i - 1];
            left.came_from_left = true;

            entry up = matrix[i];
            if(l - vol[i] >= 0) {
               up = matrix[(l - vol[i]) * n + i];
            }

            if(l > up.volume) {
               up.volume += vol[i];
               up.price += cost[i];
               if(up.came_from_left) {
                  up.number_of_drinks++;
               }
               up.came_from_left = false;
            }

            entry current;
            if(left.price < up.price) {
               current = left;
            }
            else if(left.price == up.price) {
               if(left.number_of_drinks > up.number_of_drinks) {
                  current = left;
               }
               else if(left.number_of_drinks == up.number_of_drinks) {
                  //TODO handle case
                  if(left.volume >= up.volume) {
                     current = left;
                  }
                  else {
                     current = up;
                  }
               }
               else {
                  current = up;
               }
            }
            else {
               current = up;
            }

            matrix[l * n + i] = current;
         }
      }
      cout << matrix[k * n + n - 1].price << " " << matrix[k * n + n - 1].number_of_drinks << endl;
   }
   return 0;
}
