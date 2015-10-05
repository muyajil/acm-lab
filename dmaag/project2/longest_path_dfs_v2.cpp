#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

void dfs_find_path(vector<vector<int> > &g, vector<int> &inpath, vector<int> &nextpath, int current)
{
   inpath[current] = 0;
   for(int i = 0; i < g[current].size(); i++)
   {
      int next = g[current][i];
      if(inpath[next] < 0)
      {
         dfs_find_path(g, inpath, nextpath, next);
      }
   }
   int maxa = 0;
   int maxb = 0;
   for(int i = 0; i < g[current].size(); i++)
   {
      int neighbor = g[current][i];
      if(maxa <= nextpath[neighbor] || maxb < nextpath[neighbor])
      {
         maxb = maxa;
         maxa = nextpath[neighbor];
      }
      if(maxa < maxb)
      {
         int c = maxa;
         maxa = maxb;
         maxb = c;
      }
   }
   nextpath[current] = maxa + 1;
   inpath[current] = maxa + maxb + 1;
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
         cin >> a >> b;

         g[a].push_back(b);
         g[b].push_back(a);
      }
      // longest path calc
      vector<int> inpath(n, -1);
      vector<int> nextpath(n, -1);
      dfs_find_path(g, inpath, nextpath, 0);

      int result = -1;
      for(int i = 0; i < n; i++)
      {
         if(result < inpath[i])
         {
            result = inpath[i];
         }
      }
      cout << result << endl;
   }
   return 0;
}
