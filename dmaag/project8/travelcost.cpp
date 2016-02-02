#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int testcases;
    cin >> testcases;
    while(testcases--) {
        int distance; // distance to travel
        int gasstations; // number of gasstations
        cin >> distance >> gasstations;
        vector<int> positions(gasstations + 1);
        vector<int> costs(gasstations + 1);
        for(int i = 0; i <  gasstations; i++) {
            int kmtogas; // postion of gasstation
            int cost; // cost per liter
            cin >> kmtogas >> cost;
            positions[i] = kmtogas;
            costs[i] = cost;
        }
        positions[gasstations] = distance;
        costs[gasstations] = 0;

        // calculations
        int max_reach = 1000; // max km to drive until empty tank
        int remaining_km = 1000;
        if(positions[0] > max_reach) { // first gasstation out of reach
            cout << "impossible" << endl;
            continue;
        }

        int rescost = 0; // total costs * 10
        for(int i = 0; i <= gasstations; i++) { // start with first gasstation
            // subtract needed gas to corrent station
            if(i == 0) {
                remaining_km -= positions[0];
            }
            else {
                remaining_km -= (positions[i] - positions[i - 1]); // drive to first gas station
            }
            if(remaining_km < 0) {
                rescost = -1;
                break;
            }
            if(i == gasstations) {
                break;
            }

            // check if cheaper station ahead, else fill up tank
            int next = i + 1;
            while(next < gasstations && positions[next] - positions[i] < max_reach) {
                if(costs[next] < costs[i]) { // gasstation in reach that has cheaper gas
                    break;
                }
                next++;
            }
            int journey = positions[next] - positions[i]; // journey to next cheaper station
            if(journey < max_reach && next <= gasstations) {
                if(journey > remaining_km) { // need to buy some, cheaper station ahead
                    int remaining_journey = journey - remaining_km;
                    rescost += remaining_journey * costs[i];
                    remaining_km += remaining_journey;
                } // else enought gas in tank, do nothing
            }
            else { // no cheaper fuel station in sight, top off tank
                rescost += (max_reach - remaining_km) * costs[i];
                remaining_km = max_reach;
            }
        }
        if(rescost >= 0) {
            cout << rescost / 10 << "." << rescost % 10 << endl;
        }
        else {
            cout << "impossible" << endl;
        }
    }
}
