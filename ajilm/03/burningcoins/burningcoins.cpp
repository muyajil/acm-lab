#include <iostream>
#include <vector>

using namespace std;

int main(){
        int num_test; cin >> num_test;
        while(num_test--){
                int num_coins; cin >> num_coins;
                vector<int> values(num_coins);
                for(int i = 0; i < num_coins; i++){
                        int tmp; cin >> tmp;
                        values[i] = tmp;
                }
                //Defining DP Table
                vector<vector<int> > table(num_coins, vector<int>(num_coins));

                //Initial values
                for(int i = 0; i < num_coins; i++){
                        table[i][i] = values[i];
                        if(i < num_coins-1){
                                table[i][i+1] = max(values[i], values[i+1]);
                        }
                }

                //Running algorithm
                for(int i = num_coins-3; i >= 0; i--){
                        for(int j = i+2; j < num_coins; j++){
                                table[i][j] = max(values[i] + min(table[i+2][j], table[i+1][j-1]), values[j] + min(table[i+1][j-1], table[i][j-2]));
                        }
                }
                cout << table[0][num_coins-1] << endl;
        }
}
