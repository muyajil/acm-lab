#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long dc(const vector<pair<int, int> > &points, const int lower, const int upper) {
    if(upper - lower == 1) {
        long long x_diff = points[upper].first - points[lower].first;
        long long y_diff = points[upper].second - points[lower].second;
        return x_diff * x_diff + y_diff * y_diff;
    }
    else if(upper - lower == 2) {
        long long x_diff = points[upper].first - points[lower].first;
        long long y_diff = points[upper].second - points[lower].second;
        long long res = x_diff * x_diff + y_diff * y_diff;
        x_diff = points[upper - 1].first - points[lower].first;
        y_diff = points[upper - 1].second - points[lower].second;
        res = min(res, x_diff * x_diff + y_diff * y_diff);
        x_diff = points[upper].first - points[lower + 1].first;
        y_diff = points[upper].second - points[lower + 1].second;
        res = min(res, x_diff * x_diff + y_diff * y_diff);
        return res;
    }
    else {
        int middle = lower + (upper - lower) / 2;
        long long y = dc(points, lower, middle);
        long long z = dc(points, middle + 1, upper);
        long long minimum;
        if(z > 0 && y > 0) {
            minimum = min(y, z);
        }
        else if(z > 0) {
            minimum = z;
        }
        else if(y > 0) {
            minimum = y;
        }
        else {
            minimum = -1;
        }

        int a = lower;
        int b = upper;
        long long sqrt_minimum = (long long) sqrt(minimum);
        while(points[a].first < points[middle].first - sqrt_minimum) { a++; }
        while(points[b].first > points[middle].first + sqrt_minimum) { b--; }
        vector<pair<int, int> > candidates;
        for(int i = a; i <= b; i++) {
            candidates.push_back(points[i]);
        }
        // sort(candidates.begin(), candidates.end());

        for(int i = 0; i < candidates.size(); i++) {
            for(int k = i + 1; k < candidates.size(); k++) {
                /*
                if(candidates[i].first + sqrt_minimum < candidates[k].first) { // not reachable anymore
                    break;
                }
                */
                long long x_diff = candidates[i].first - candidates[k].first;
                long long y_diff = candidates[i].second - candidates[k].second;
                minimum = min(minimum, x_diff * x_diff + y_diff * y_diff);
            }
        }
        return minimum;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while(tests--) {
        int n;
        cin >> n;
        vector<pair<int, int> > points_x(n);
        vector<pair<int, int> > points_y(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points_x[i] = (make_pair(x, y));
            points_y[i] = (make_pair(y, x));
        }
        sort(points_x.begin(), points_x.end());
        sort(points_y.begin(), points_y.end());

        // start d&c
        long long result = dc(points_x, 0, n - 1);
        cout << result << endl;
    }
    return 0;
}
