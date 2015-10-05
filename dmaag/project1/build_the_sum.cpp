#include <iostream>
#include <algorithm>

int main()
{
   int n;
   std::cin >> n;
   double results[n];

   for(int j = 0; j < n; j++){
      int m;
      std::cin >> m;
      double num[m];

      for (int i = 0; i < m; i++)
      {
         double next;
         std::cin >> next;
         num[i] = next;
      }
      std::sort(num, num + m);
      results[j] = 0;
      for(int i = 0; i < m; i++)
      {
         results[j] += num[i];
      }
   }
   for(int j = 0; j < n; j++)
   {
      std::cout << results[j] << "\n";
   }
}
