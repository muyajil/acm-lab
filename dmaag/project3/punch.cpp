#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct table_entry {
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
      vector<vector<table_entry> > matrix(n + 1, vector<table_entry>(k + 1, 0));
      for(int i = 1; i < k + 1; i++) {
         for(int j = 1; j < n + 1; j++) {
            
         }
      }
   return 0;
}
