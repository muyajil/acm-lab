#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
        int num_test; cin >> num_test;
        while(num_test--){
                int num_values, num_samples; cin >> num_values >> num_samples;
                vector<int> values(num_values);
                for (int i = 0; i < num_values; i++){
                        int tmp; cin >> tmp; values[i] = tmp;
                }
                for (int i = 0; i < num_samples; i++){
                        int amount; cin >> amount;
                        //DP Table: Row: Amounts 0 to amount, Col: values
                        vector<vector<int> > table(amount+1, vector<int>(num_values));

                        //Initialize DP Table
                        for(int i = 0; i < num_values; i++){
                                table[0][i] = 0; //Change for amount 0 is always 0
                        }
                        for(int i = 1; i <= amount; i++){
                                if(i%values[0]==0){
                                        table[i][0] = i/values[0]; //If the division works do it
                                } else {
                                        table[i][0] = 100000; //If not put some maximum value
                                }
                        }
                        //Fill DP Table
                        for(int i = 1; i <= amount; i++){
                                for(int j = 1; j < num_values; j++){
                                        if(i - values[j] >= 0){
                                                table[i][j] = min(table[i][j-1], table[i - values[j]][j]+1);
                                        } else {
                                                table[i][j] = table[i][j-1];
                                        }
                                }
                        }
                        if(table[amount][num_values-1] < 100000){
                                cout << table[amount][num_values-1] << endl;
                        } else {
                                cout << "not possible" << endl;
                        }
                }
        }
}
