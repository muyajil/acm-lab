#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int num_elems; // Number of elements of arrays

int solve(int a_p, int b_p, // consider subproblem for the prefixes a_p and b_p
    vector<int> &a, vector<int> &b, // arrays
    vector<int> &sum_a, vector<int> &sum_b, // sum arrays
    vector<vector<int> > &table){ // dp_table
    // Here we check the result for p a_p and b_p
    // First we need to check trivial results
    if(a_p == 0){
        return a[0] * sum_b[b_p]; // We need to take everything from b according to rules
    } else if(b_p == 0){
        return b[0] * sum_a[a_p]; // Same here
    } else if(table[a_p][b_p] != -1){
        return table[a_p][b_p]; // Here we have already computed the result
    } else { // Now we need to really compute the minimal cost
        table[a_p][b_p] = sum_a[a_p] * sum_b[b_p]; // The biggest possible value
        // Try with taking 1 element from a
        for(int i = 0; i < b_p; i++){
            table[a_p][b_p] = min(
                table[a_p][b_p],  // current value
                a[a_p] * (sum_b[b_p] - sum_b[i]) + solve(a_p-1, i, a, b, sum_a, sum_b, table)); // Try all possible number of elements to take from b
        }
        // Try with taking 1 element from b
        for(int i = 0; i < a_p; i++){
            table[a_p][b_p] = min(
                table[a_p][b_p], // curent value
                b[b_p] * (sum_a[a_p] - sum_a[i]) + solve(i, b_p-1, a, b, sum_a, sum_b, table)); // Try all possible number of elements to take from a
        }
        return table[a_p][b_p];
    }
}

int main(){
    int num_elems; cin >> num_elems; // Get number of elements per array
    vector<int> a(num_elems); // Array a
    vector<int> sum_a(num_elems); // Sum array a, sum_a[i] = sum of first i elements
    vector<int> b(num_elems); // Array b
    vector<int> sum_b(num_elems); // Sum array b
    vector<vector<int> > table(num_elems, vector<int>(num_elems, -1)); // define dp table, default value -1

    // Read array a
    for (int i = 0; i < num_elems; i++){
        int a_i; cin >> a_i; a[i] = a_i; // Get next value
        if(i == 0){
            sum_a[i] = a_i;
        } else {
            sum_a[i] = a_i + sum_a[i-1]; // compute next sum
        }

    }

    // Read array b
    for (int i = 0; i < num_elems; i++){
        int b_i; cin >> b_i; b[i] = b_i; // Get next value
        if(i == 0){
            sum_b[i] = b_i;
        } else {
            sum_b[i] = b_i + sum_b[i-1]; // compute next sum
        }
    }

    cout << solve(num_elems-1, num_elems-1, a, b ,sum_a, sum_b, table) << endl;
    return 0;
}
