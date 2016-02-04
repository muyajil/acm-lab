#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long dc(const vector<int> &costs, const int k, const int first, const int last) {
    if(last - first )
}

int main() {
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while(tests--) {
        int n, k;
        cin >> n >> k;
        vector<int> costs(n);
        for(int i = 0; i < n; i++) {
            int c;
            cin >> c;
            costs[i] = c;
        }

        long long res = dc(costs, k, 0, n - 1);
        cout << res << endl;
    }
    return 0;
}
