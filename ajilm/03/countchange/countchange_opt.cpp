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
                vector<int> samples(num_samples);
                int max_sample = 0;
                for (int i = 0; i < num_samples; i++){
                        int tmp; cin >> tmp;
                        samples[i] = tmp;
                        max_sample = max(max_sample, samples[i]);
                }
                //Defining DP table
                vector<vector<int> > table(max_sample+1, vector<int>(num_values));

                //Initialize DP Table
                for(int i = 0; i < num_values; i++){
                        table[0][i] = 0; //Change for amount 0 is always 0
                }
                for(int i = 1; i <= max_sample; i++){
                        if(i%values[0]==0){
                                table[i][0] = i/values[0]; //If the division works do it
                        } else {
                                table[i][0] = 100000; //If not put some maximum value
                        }
                }
                //Fill DP Table
                for(int i = 1; i <= max_sample; i++){
                        for(int j = 1; j < num_values; j++){
                                if(i - values[j] >= 0){
                                        table[i][j] = min(table[i][j-1], table[i - values[j]][j]+1);
                                } else {
                                        table[i][j] = table[i][j-1];
                                }
                        }
                }
                for(int i = 0; i < num_samples; i++){
                        if(table[samples[i]][num_values-1] < 100000){
                                cout << table[samples[i]][num_values-1] << endl;
                        } else {
                                cout << "not possible" << endl;
                        }
                }
        }
}
