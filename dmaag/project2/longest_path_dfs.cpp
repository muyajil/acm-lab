#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int dfs_find_path(vector<vector<int> > &g, vector<int> &ending, vector<int> &starting, int current, int cur_path)
{
   int max_path = cur_path;
   if(ending[current] < cur_path)
   {
      ending[current] = cur_path;
   }
   for(int i = 0; i < g[current].size(); i++)
   {
      int next = g[current][i];
      if(ending[current] == ending[next] || ending[current] < 0 || ending[current] > ending[next] + 1)
      {
         int starting_path = dfs_find_path(g, ending, starting, next, cur_path + 1);

         if(max_path < starting_path)
         {
            max_path = starting_path;
            if(starting[current] < starting_path)
            {
               starting[current] = starting_path;
            }
         }
      }
   }
   return max_path;
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
      int result = 0;
      vector<int> ending(n, -1);
      vector<int> starting(n, 1);
      for(int i = 0; i < n; i++)
      {
         if(g[i].size() <= 1)
         {
            dfs_find_path(g, ending, starting, i, 1);
         }
      }
      for(int i = 0; i < n; i++)
      {
         if(result < starting[i])
         {
            result = starting[i];
         }
      }
      cout << result << endl;
   }
   return 0;
}
