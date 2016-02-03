#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//We make a Range minimum query
//Build a table for range minimum queries:
//  - size: (num_links) x (log(num_links).roundUp())
//  - t[i][0]) = min(L[i], L[i+1]) --> k = 1
//  - t[i][r+1] = min(t[i][r], t[i+2^r][r]) --> k=2^r

//function to compute log2(n) rounded up
int log2(int n){
    int i = 1;
    // compute times 2 until bigger than n
    while (i <= n) n*=2;
    return i;
}

int main(){
    int testcases; cin >> testcases;
    while (testcases--){
        int num_links, num_ks;
        cin >> num_links >> num_ks;
        vector<int> links(num_links);
        vector<int> ks(num_ks);
        for(int i = 0; i < num_links; i++){
            int curr_link;
            cin >> curr_link;
            links.push_back(curr_link);
        }
        for(int i = 0; i < num_ks; i++){
            int curr_k;
            cin >> curr_k;
            ks.push_back(curr_k);
        }
        // Compute maximal r to compute
        int log_links = log2(num_links);
        // Allocate the table
        int T[num_links][log_links];
        
        // Now we build the table

        // First we fill in the base case
        for(int i = 0; i < num_links; i++){
            // We take the minimum of the current link and the next
            // In the case where we go out of bounds
            // when i = num_links-1 we look at the first link again
            T[i][0] = min(links[i], links[(i+1)%(num_links-1)]);
        }

        // Now we make the recursion
        for(int j = 1; j < log_links; j++){
            for(int i = 0; i < num_links; i++){
                // We divide the array in two halves
                // Take the minimum of the two halves
                int i_next = i+pow(2,j-1);
                i_next %= num_links-1;
                T[i][j] = min(T[i][j-1],
                        T[i_next][j-1]);
            }
        }

        // Now we have the tables and we should be able to to the queries
        
        // We iterate through all the ks we received and try to answer the queries
        for(int i = 0; i < num_ks; i++){
            int curr_k = ks[i];
            // First we need the log2 rounded up of k
            int log_k = log2(curr_k);
            int dist = pow(2, log_k); //approximation of k

            // Now we need to get the maximum of the possible paths
            
            // For that we need to go through our table
            // We look at each possible starting link and then output the best we found
            int best_index = 0;
            for(int j = 0; j < num_links; j++){
                int curr_bandwidth;
                int best_bandwidth = 0;
                
                curr_bandwidth = max(T[j][log_k], T[(j-dist)%(num_links-1)][log_k]);
                
                if(curr_bandwidth > best_bandwidth){
                    best_bandwidth = curr_bandwidth;
                    best_index = j;
                }
            }
            if (best_index + dist > num_links){
                cout << (best_index+dist)%(num_links-1) << best_index << endl;
            } else {
                cout << best_index << best_index + dist << endl;
            }
        }
    }
    return 0;
}
