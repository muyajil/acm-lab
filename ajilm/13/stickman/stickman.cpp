#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

template <typename T>
void print_board(vector<vector<T> > &board, int rows, int cols){
    for(int i = rows-1; i >= 0; i--){
        for(int j = 0; j < cols; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){

    int testcases; cin >> testcases;
    while(testcases--){
        int rows, cols;
        cin >> rows >> cols;
        vector<vector <int> > board(rows, vector<int>(cols));
        vector<vector <int> > minimum(rows, vector<int>(cols, 99999));
        vector<vector <int> > maximum(rows, vector<int>(cols, -1));
        vector<vector <bool> > jokers(rows, vector<bool>(cols, false));
        // Parse the board
        // board[i][j] should give elment (i,j)
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                int i_j; cin >> i_j;
                board[i][j] = i_j;
            }
        }
        int num_jokers; cin >> num_jokers;
        for(int i = 0; i < num_jokers; i++){
            int x_i, y_i;
            cin >> x_i >> y_i;
            jokers[x_i-1][y_i-1] = true;
        }

        // Initialize target field
        minimum[rows-1][cols-1] = board[rows-1][cols-1];
        maximum[rows-1][cols-1] = board[rows-1][cols-1];

        // Initialize rows
        for(int i = rows-2; i >= 0; i--){
            minimum[i][cols-1] = minimum[i+1][cols-1] + board[i][cols-1];
            maximum[i][cols-1] = maximum[i+1][cols-1] + board[i][cols-1];
        }

        // Initialize cols
        for(int i = cols-2; i >= 0; i--){
            minimum[rows-1][i] = minimum[rows-1][i+1] + board[rows-1][i];
            maximum[rows-1][i] = maximum[rows-1][i+1] + board[rows-1][i];   
        }

        // Now we build the tables
        for(int i = rows-2; i >= 0; i--){
            for(int j = cols-2; j >= 0; j--){
                if(jokers[i+1][j] && !jokers[i][j+1]){
                    maximum[i][j] = max(maximum[i+1][j], minimum[i][j+1]) + board[i][j];
                    minimum[i][j] = min(minimum[i+1][j], maximum[i][j+1]) + board[i][j];
                } else if(jokers[i][j+1] && !jokers[i+1][j]){
                    maximum[i][j] = max(minimum[i+1][j], maximum[i][j+1]) + board[i][j];
                    minimum[i][j] = min(maximum[i+1][j], minimum[i][j+1]) + board[i][j];
                } else if(jokers[i+1][j] && jokers[i][j+1]){
                    maximum[i][j] = max(maximum[i+1][j], maximum[j][i+1]) + board[i][j];
                    minimum[i][j] = min(minimum[i+1][j], minimum[j][i+1]) + board[i][j];
                } else {
                    maximum[i][j] = max(minimum[i+1][j], minimum[i][j+1]) + board[i][j];
                    minimum[i][j] = min(maximum[i+1][j], maximum[i][j+1]) + board[i][j];
                }
            }
        }
        cout << "Board:" << endl;
        print_board(board, rows, cols);
        cout << "Maximum:" << endl;
        print_board(maximum, rows, cols);
        cout << "Minimum:" << endl;
        print_board(minimum, rows, cols);
        cout << "Jokers:" << endl;
        print_board(jokers, rows, cols);
        cout << maximum[0][0] << endl;
    }
    return 0;
}
