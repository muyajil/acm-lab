#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct vertex {
  int x;
  int y;
  int velo_x;
  int velo_y;
  int hops;
};

int main(){
  int num_test; cin >> num_test;
  while(num_test--) {
    int width, height; cin >> width >> height;
    int x_start_h, y_start_h, x_end_h, y_end_h; //hopper start and end pos
    cin >> x_start_h >> y_start_h >> x_end_h >> y_end_h;
    int num_obstacles; cin >> num_obstacles;
    vector<vector<bool> > obstacles(width, vector<bool>(height, false)); //if (obstacles [i][j]) it is occupied
    //Read obstacles
    for(int i = 0; i < num_obstacles; i++) {
      int x_start, y_start, x_end, y_end;
      cin >> x_start >> y_start >> x_end >> y_end;
      for (int i = x_start; i <= x_end; i++) {
        for(int j = y_start; j <= y_end; j++) {
          obstacles[i][j] = true;
        }
      }
    }
    //State of the hopper
    vector<vector<vector<vector<bool> > > > visited(width, vector<vector<vector<bool> > >(height, vector<vector<bool> >(7, vector<bool>(7, false))));
    // if (visited[i][j][k][l]) hopper visited (i,j) with velocity (k,l)

    visited[x_start_h][y_start_h][3][3] = true; // initial position with velocity 0,0
    queue<vertex> queue; //preparing queue for BFS
    vertex starting_vertex = {x_start_h, y_start_h, 0, 0, 0}; //first node of the graph
    queue.push(starting_vertex); //push first node onto stack
    int result = -1;
    if(x_start_h == x_end_h && y_start_h == y_end_h){
      result = 0;
    }
    //int queue_counter = 0;
    while(!queue.empty() && result < 0) {
      vertex cur = queue.front();
      //enumerate all possible velocity changes
      for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
          //check if the velocity is in the range only proceed if so
          if(abs(cur.velo_x + i) < 4 && abs(cur.velo_y + j) < 4) {
            //construct a new vertex that has the new velocities & positions
            vertex next = {cur.x + cur.velo_x + i, cur.y + cur.velo_y + j, cur.velo_x + i, cur.velo_y + j, cur.hops+1};
            //check if the new position would be on the board
            if(next.x < width && next.x >= 0 && next.y < height && next.y >= 0) {
              //check if we have not already visited this square with the same speed
              if(!visited[next.x][next.y][3 + next.velo_x][3 + next.velo_y]){
                //check if the target would be occupied
                if(!obstacles[next.x][next.y]){
                  //set visited flag
                  visited[next.x][next.y][3 + next.velo_x][3 + next.velo_y] = true;
                  //check if we reached the end
                  if(next.x == x_end_h && next.y == y_end_h){
                    result = next.hops;
                  } else {
                    queue.push(next);
                  }
                }
              }
            }
          }
        }
      }
      //queue_counter++;
      queue.pop();
    }
    //cout << "Queue counter: " << queue_counter <<  endl;
    if(result > -1) {
      cout << "Optimal solution takes " << result << " hops." << endl;
    } else {
      cout << "No solution." << endl;
    }
  }
}

/*

Need to handle cornercases correctly! (start=end)

*/
