#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
   int t;
   cin >> t;
   while(t--)
   {
      int n, k;
      cin >> n >> k;
      vector<int> cost(n);
      vector<int> vol(n);
      for(int i = 0; i < n; i++)
      {
         cin >> cost[i] >> vol[i];
      }

      // calcu
      vector<vecotr<int> > matrix(k + 1, vector<int>(k + 1));
   }
   return 0;
}
