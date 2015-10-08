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

bool target_on_board(vertex cur, int width, int height){
        return cur.x + cur.velo_x < width && cur.x + cur.velo_x >= 0 && cur.y + cur.velo_y < height && cur.y + cur.velo_y >= 0;
}

bool velocity_in_range(vertex cur, int i, int j){
        return abs(cur.velo_x + i) < 4 && abs(cur.velo_y + i) < 4;
}

bool target_occupied(vertex cur, vector<vector<bool> > &obstacles){
        return obstacles[cur.x + cur.velo_x][cur.y + cur.velo_y];
}

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
                queue<vertex> queue;
                vertex starting_vertex = {x_start_h, y_start_h, 0, 0, 0}; //first node of the graph
                queue.push(starting_vertex); //push first node onto stack
                int result = -1;
                while(!queue.empty()) {
                        vertex cur = queue.front();
                        cout << "Current Vertex:\n x: " << cur.x << " y: " << cur.y << " velo_x: " << cur.velo_x << " velo_y: " << cur.velo_y << endl;
                        //push all vertices onto stack that only change velocity
                        for(int i = 1; i >= -1; i--) {
                                for(int j = 1; j >= -1; j--) {
                                        //check if the velocity is in the range
                                        if(velocity_in_range(cur, i, j)) {
                                                //cout << "velocity was in range for i: " << i << " and j: " << j << endl;
                                                //if the target square is on the board and not visited
                                                if(target_on_board(cur, width, height) && !visited[cur.x][cur.y][3 + cur.velo_x + i][3 + cur.velo_y + j]) {
                                                        cout << "target was on board and not visited for i: " << i << " and j: " << j << endl;
                                                        vertex change_velo = {cur.x, cur.y, cur.velo_x + i, cur.velo_x + j, cur.hops + 1}; //construct vertex
                                                        visited[cur.x][cur.y][3 + cur.velo_x + i][3 + cur.velo_y + j] = true; //set visited flag
                                                        queue.push(change_velo);
                                                }
                                        }
                                }
                        }
                        //if the target square is on the board
                        if(target_on_board(cur, width, height)) {
                                //if there is no obstacle on the target square and if it was not yet visited with the same velocity
                                if(!target_occupied(cur, obstacles) && !visited[cur.x + cur.velo_x][cur.y + cur.velo_y][3 + cur.velo_x][3 + cur.velo_y]) {
                                        cout << "target was on board and not visited for current vertex" << endl;
                                        vertex change_pos = {cur.x + cur.velo_x, cur.y + cur.velo_y, cur.velo_x, cur.velo_y, cur.hops+1}; // construct vertex
                                        visited[cur.x + cur.velo_x][cur.y + cur.velo_y][3+cur.velo_x][3+cur.velo_y] = true; //set visited true
                                        if(cur.x + cur.velo_x == x_end_h && cur.y + cur.velo_y == y_end_h) { //if its the end
                                                result = cur.hops;
                                                break;
                                        } else {
                                                queue.push(change_pos);
                                        }
                                }
                        }
                        cout << "Queue size before popping: " << queue.size() << endl;
                        queue.pop();
                }
                if(result < -1) {
                        cout << "Optimal solution takes " << result << " hops." << endl;
                } else {
                        cout << "No solution." << endl;
                }
        }
}

/*

Need to handle cornercases correctly! (start=end)

*/
