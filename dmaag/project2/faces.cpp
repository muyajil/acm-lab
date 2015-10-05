#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int find_group(vector<vector<int> > &g, vector<int> &groups)
{
   queue<int> q;
   int team = 0;

   for(int i = 0; i < g.size(); i++)
   {
      if(groups[i] < 0)
      {
         groups[i] = team;
         q.push(i);
         while(!q.empty())
         {
            int cur = q.front();
            for(int i = 0; i < g[cur].size(); i++)
            {
               if(groups[g[cur][i]] < 0)
               {
                  groups[g[cur][i]] = team;
                  q.push(g[cur][i]);
               }
            }
            q.pop();
         }
         team++;
      }
   }
   return team;
}

int main()
{
   int n;
   cin >> n;

   while(n--)
   {
      int v, e;
      cin >> v >> e;
      vector<vector<int> > g(v);

      for(int i = 0; i < e; i++)
      {
         int a, b;
         cin >> a >> b;

         g[a].push_back(b);
         g[b].push_back(a);
      }
      vector<int> groups(v, -1);
      int no_groups = find_group(g, groups);

      vector<int> vertexes(no_groups, 0);
      vector<int> edges(no_groups, 0);

      // 1 - no_groups
      int result = 1 - no_groups;

      for(int i = 0; i < v; i++)
      {
         vertexes[groups[i]]++;
         edges[groups[i]] += g[i].size();
      }

      for(int i = 0; i < no_groups; i++)
      {
         edges[i] = edges[i] / 2;
         result += 2 + edges[i] - vertexes[i];
      }
      cout << result << endl;
   }
}
