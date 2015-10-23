#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct entry {
   int number_of_drinks;
   int volume;
   int price;
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
      entry init = {0, 0, 0};
      vector<vector<entry> > matrix(k + 1, vector<entry>(n + 1, init));
      for(int l = 1; l < k + 1; l++) {
         for(int i = 1; i < n + 1; i++) {
            if(l - vol[i] >= 0) { // new volume inbound
               if(matrix[l][i - 1].price > matrix[l - vol[i]][i].price) { // current drink is cheaper
                  int nprice = matrix[l - vol[i]][i].price
                  matrix[l][i] = {matrix[l - vol[i]][i].price};
               }
            }
         }
      }
   }
   return 0;
}
