#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
   int n;
   cin >> n;
   while(n--)
   {
      int c, m;
      cin >> c >> m;
      vector<int> coins(c);
      for(int i = 0; i < c; i++)
      {
         cin >> coins[i];
      }

      int tmax = 0;
      vector<int> tests(m);
      for(int i = 0; i < m; i++)
      {
         cin >> tests[i];
         tmax = max(tmax, tests[i]);
      }

      vector<int> number(tmax + 1, 10000);
      number[0] = 0;
      for(int i = 1; i < tmax + 1; i++)
      {
         for(int j = 0; j < c; j++)
         {
            int new_index = i - coins[j];
            if(new_index >= 0 && number[i] > number[new_index] + 1)
            {
               number[i] = number[new_index] + 1;
            }
         }
      }

      for(int i = 0; i < m; i++)
      {
         if(number[tests[i]] == 10000)
         {
            cout << "not possible" << endl;
         }
         else
         {
            cout << number[tests[i]] << endl;
         }
      }
   }
   return 0;
}
