#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct wiz {
    int boat_length;
    int position;

    friend bool operator<(wiz a, wiz b) {
        return a.position < b.position;
    }
};

int main() {
    int testcases;
    cin >> testcases;
    while(testcases--) {
        int no_of_wizards;
        cin >> no_of_wizards;
        vector<wiz> wizards(no_of_wizards);
        for(int i = 0; i < no_of_wizards; i++) {
            int len, pos;
            cin >> len >> pos;
            wizards[i] = {len, pos};
        }

        // calculations
        // rightmost and leftmost beat are set so sort the ring positions
        sort(wizards.begin(), wizards.end());

        // lower bound of available space
        wiz last = wizards.front();
        int lower_bound = last.position;
        int count = 1;

        for(int i = 1; i < no_of_wizards; i++) {
            wiz w = wizards[i];
            if(w.position >= lower_bound) { // boat can be added without a problem
                count ++;
                last = w;
                if(w.position - w.boat_length >= lower_bound) { // plenty of space
                    lower_bound = w.position;
                }
                else {
                    lower_bound = lower_bound + w.boat_length;
                }
            }
            else { // previous boat has to go..
                int old = lower_bound - last.boat_length;
                if(old <= w.position - w.boat_length) {
                    lower_bound = w.position;
                    last = w;
                }
                else if(lower_bound > old + w.boat_length) {
                    lower_bound = old + w.boat_length;
                    last = w;
                }
            }
        }
        cout << count;
        cout << endl;
    }
    return 0;
}
