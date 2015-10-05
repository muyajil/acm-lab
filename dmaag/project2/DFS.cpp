#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t;

void dfs_search(vector<vector<int> > &g, vector<int> &ds, vector<int> &fs, int current)
{
   ds[current] = t++;
   for(int i = 0; i < g[current].size(); i++)
   {
      int next = g[current][i];
      if(ds[next] < 0)
      {
         dfs_search(g, ds, fs, next);
      }
   }
   fs[current] = t++;
}

void dfs(vector<vector<int> > &g, vector<int> &ds, vector<int> &fs)
{
   for(int i = 0; i < g.size(); i++)
   {
      if(ds[i] < 0)
      {
         dfs_search(g, ds, fs, i);
      }
   }
}

int main()
{
   int c;
   cin >> c;

   while(c--)
   {
      int n;
      int m;
      cin >> n >> m;

      vector<vector<int> > g(n);

      for(int i = 0; i < m; i++)
      {
         int a;
         int b;
         cin >> a >> b;

         g[a].push_back(b);
         g[b].push_back(a);
      }

      for(int i = 0; i < n; i++)
      {
         sort(g[i].begin(), g[i].end());
      }

      t = 0;
      vector<int> ds(n, -1);
      vector<int> fs(n, -1);

      dfs(g, ds, fs);

      for(int i = 0; i < n; i++)
      {
         cout << ds[i] << " ";
      }
      cout << endl;
      for(int i = 0; i < n; i++)
      {
         cout << fs[i] << " ";
      }
      cout << endl;

   }
   return 0;
}
