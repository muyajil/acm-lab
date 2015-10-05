#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int main()
{
   int c;
   cin >> c;

   while(c--)
   {
      int n, m, v;
      cin >> n >> m >> v;

      vector<int> depths(n, -1);
      vector<vector<int> > g(n);

      for(int i = 0; i < m; i++)
      {
         int a, b;
         cin >> a >> b;

         g[a].push_back(b);
         g[b].push_back(a);
      }

      depths[v] = 0;
      queue<int> q;
      q.push(v);
      while(!q.empty())
      {
         int cur = q.front();
         for(int i = 0; i < g[cur].size(); i++)
         {
            if(depths[g[cur][i]] < 0)
            {
               depths[g[cur][i]] = depths[cur] + 1;
               q.push(g[cur][i]);
            }
         }
         q.pop();
      }

      for(int i = 0; i < n; i++)
      {
         cout << depths[i] << " ";
      }
      cout << endl;
   }
   return 0;
}
