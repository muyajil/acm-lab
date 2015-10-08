#include <iostream>
#include <vector>

using namespace std;

int main(){
        int num_test; cin >> num_test;
        while(num_test--){
                int num_bev, litres; cin >> num_bev >> litres;
                vector<int> cost(num_bev);
                vector<int> volume(num_bev);
                for(int i = 0; i < num_bev; i++){
                        int tmp_cost, tmp_vol; cin >> tmp_cost >> tmp_vol;
                        cost[i] = tmp_cost;
                        volume[i] = tmp_vol;
                }
                vector<vector<int> > table(num_bev+1, vector<int>(litres+1));

                //Initlialize DP Table
                for(int i = 0; i < num_bev; i++){
                        table[i][0] = 0; //0 litres cost nothing
                }
                for(int j = 0; j < litres; j++){
                        table[0][j] = 100000; //0 beverages are not possible
                }
                //Fill DP Table
                for(int i = 1; i <= num_bev; i++){
                        for(int j = 1; j <= litres; j++){
                                if(j-volume[i] >= 0){
                                        table[i][j] = min(cost[i] + table[i][j-volume[i]], table[i-1][j]);
                                } else {

                                        table[i][j] = table[i-1][j];
                                }
                        }
                }
                /*print table
                for (int i = 0; i <= num_bev; i++){
                        for(int j = 0; j <= litres; j++){
                                cout << table[i][j] << " ";
                        }
                        cout << endl;
                }
                */
                int min_cost = 1000000;
                int num_bevs = 0;
                for(int i = 1; i < num_bev; i++){
                        if (min_cost >= table[i][litres] && table[i][litres] > 0) {
                                min_cost = table[i][litres];
                                num_bevs = i;
                        }
                }
                cout << min_cost << " " << num_bevs << endl;
        }
}
