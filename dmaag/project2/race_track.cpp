#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct vertex { // stores coordinates, speeds and hops to start for a point in the graph
   int x_co; // x coordinate
   int y_co; // y coordinate
   int x_vel; // velocity in x direction
   int y_vel; // velocity in y direction
   int hops; // hops traveled from start
};

int main()
{
   int t;
   cin >> t;
   while(t--)
   {
      int grid_x, grid_y, start_x, start_y, end_x, end_y, obs;
      cin >> grid_x >> grid_y >> start_x >> start_y >> end_x >> end_y >> obs;
      vector<vector<bool> > obstacles(grid_x, vector<bool>(grid_y, false)); // [i][j] == true if one cannot go to position [i][j]
      vector<vector<vector<vector<bool> > > > visited(grid_x, vector<vector<vector<bool> > >(grid_y, vector<vector<bool> >(7, vector<bool>(7, false)))); // [x][y][vx][vy] true if point [x][y] was visited with with velocity (vx, vy)

      for(int i = 0; i < obs; i++)
      {
         int a, b, x, y;
         cin >> a >> b >> x >> y;
         for(int k = a; k <= x; k++)
         {
            for(int l = b; l <= y; l++)
            {
               obstacles[k][l] = true;
            }
         }
      }

      /*BFS search for one fastest way*/
      queue<vertex> queue; // queue for BFS
      int result = -1; //result stays -1 until solution is found
      if(start_x == end_x && start_y == end_y) {
         result = 0;
      }
      visited[start_x][start_y][3][3] = true;
      vertex cur = {start_x, start_y, 0, 0, 0};
      queue.push(cur);

      // BFS like search until a solution is found or there are no more possibilities
      while(result < 0 && !queue.empty())
      {
         cur = queue.front();
         // enumerate all possible velocity changes in x and y direction
         for(int dif_x = -1; dif_x <= 1; dif_x++)
         {
            for(int dif_y = -1; dif_y <= 1; dif_y++)
            {
               int vx = cur.x_vel + dif_x; // new velocity in x direction
               int vy = cur.y_vel + dif_y; // new velocity in y direction
               // only proceed if velocities are possible
               if(vx >= -3 && vx <= 3 && vy >= -3 && vy <= 3)
               {
                  int a = cur.x_co + vx; // new x-position
                  int b = cur.y_co + vy; // new y-position
                  bool inbound = a >= 0 && a < grid_x && b >= 0 && b < grid_y; // checks whether coordinates are inside the grid or not

                  // only take action if position is not blocked, inside the grid and not allready visited with exact same speed
                  if(inbound && !visited[a][b][vx + 3][vy + 3] && !obstacles[a][b])
                  {
                     visited[a][b][vx + 3][vy + 3] = true;
                     int h = cur.hops + 1; // hops traveled to reach new point
                     // if new potin is the end point, set result and therefore terminate while loop
                     if(a == end_x && b == end_y)
                     {
                        result = h;
                     }
                     // not end point -> enqueue point and start with next point
                     else
                     {
                        vertex next = {a, b, vx, vy, h};
                        queue.push(next);
                     }
                  }
               }
            }
         }
         queue.pop(); // delete the just analyzed point
      }

      /*output*/
      if(result >= 0) // solution was found
      {
         cout << "Optimal solution takes " << result << " hops." << endl;
      }
      else // result == -1 and therefore no solution could be found
      {
         cout << "No solution." << endl;
      }
   }
}
