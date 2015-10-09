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
                vector<bool> used_bev(num_bev+1,false);

                //Initlialize DP Table
                for(int i = 0; i < num_bev; i++){
                        table[i][0] = 0; //0 litres cost nothing
                }
                for(int j = 0; j < litres; j++){
                        table[0][j] = 1000000; //0 beverages are not possible
                }


                //Fill DP Table
                for(int i = 1; i <= num_bev; i++){
                        for(int j = 1; j <= litres; j++){
                                if(j-volume[i] >= 0){
                                        table[i][j] = min(cost[i] + table[i][j-volume[i]], table[i-1][j]);
                                        if(table[i][j] == cost[i] + table[i][j-volume[i]]) used_bev[i] = true;
                                } else {
                                        table[i][j] = table[i-1][j];
                                }
                        }
                }

                //Count different beverages
                int diff_bevs = 0;
                for(int i = 0; i <= num_bev; i++){
                        if(used_bev[i]) diff_bevs++;
                }

                //Find minimal cost
                int min_cost = 1000000;
                for(int i = 1; i < num_bev; i++){
                        if (min_cost >= table[i][litres]) {
                                min_cost = table[i][litres];
                        }
                }
                cout << min_cost << " " << diff_bevs << endl;
        }
}

/*

NOTES FROM LECTURE:

Was an exam question last year! --> Variant of the Knapsack problem

k Litres of punch
Each type of dring has volume v[i] and cost c[i]
Goal: produce at least k litres of drinks as cheap as possible

f(t) = min cost to create at least t litres
f(t,i) = min cost to create t litres using only the first i types of drinks
Base cases:
        f(t,i) = 0 for t <= 0
        f(t,i) = infty if i <= 0
Recursion:
        f(t,i) = min(f(t, i-1), c[i] + f(t-v[i], i))

Need to to backtracking! to find how many different
*/
