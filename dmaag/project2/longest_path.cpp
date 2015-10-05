#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int find_longest_path(vector<vector<int> > &g, int start)
{
   vector<int> depths(g.size(), -1);
   queue<int> q;
   q.push(start);
   depths[start] = 1;
   int result = -1;
   while(!q.empty())
   {
      int cur = q.front();
      for(int i = 0; i < g[cur].size(); i++)
      {
         if(depths[g[cur][i]] < 0)
         {
            depths[g[cur][i]] = depths[cur] + 1;
            result = depths[cur] + 1;
            q.push(g[cur][i]);
         }
      }
      q.pop();
   }
   return result;
}

int main()
{
   int t;
   cin >> t;
   while(t--)
   {
      int n;
      cin >> n;
      vector<vector<int> > g(n);

      for(int i = 0; i < n - 1; i++)
      {
         int a, b;
         cin >> a >>b;

         g[a].push_back(b);
         g[b].push_back(a);
      }
      // longest path calc
      int result = -1;
      for(int i = 0; i < n; i++)
      {
         if(g[i].size() == 1)
         {
            int c = find_longest_path(g, i);
            if(c > result)
            {
               result = c;
            }
         }
      }
      cout << result << endl;
   }
}
