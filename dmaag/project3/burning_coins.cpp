#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
   int c;
   cin >> c;
   while(c--)
   {
      int n;
      cin >> n;
      vector<int> coins(n);
      for(int i = 0; i < n; i++)
      {
         cin >> coins[i];
      }

      //calculating
      vector<vector<int> > sums(n, vector<int>(n));
      for(int i = 0; i < n; i++)
      {
         sums[i][i] = coins[i];
         if(i < n - 1)
         {
            sums[i][i + 1] = max(coins[i], coins[i + 1]);
         }
      }

      for(int i = n - 3; i >= 0; i--)
      {
         for(int j = i + 2; j < n; j++)
         {
            sums[i][j] = max(coins[i] + min(sums[i + 2][j], sums[i + 1][j - 1]), coins[j] + min(sums[i + 1][j - 1], sums[i][j - 2]));
         }
      }

      cout << sums[0][n - 1] << endl;

   }
   return 0;
}
