#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int min_best(const vector<vector<int> > &plane,
        const vector<vector<bool> > &joker, const vector<vector<int> > &minima,
        const vector<vector<int> > &maxima, const int row, const int col) {
    int up;
    if(joker[row + 1][col]) { //up is joker, so take min insted of max
        up = minima[row + 1][col];
    }
    else { // not a joker so take max
        up = maxima[row + 1][col];
    }
    int right;
    if(joker[row][col + 1]) { // right is joker, take min
        right = minima[row][col + 1];
    }
    else { // no joker so take max
        right = maxima[row][col + 1];
    }
    return plane[row][col] + min(up, right);
}

int max_best(const vector<vector<int> > &plane,
        const vector<vector<bool> > &joker, const vector<vector<int> > &minima,
        const vector<vector<int> > &maxima, const int row, const int col) {
    int up;
    if(joker[row + 1][col]) { //up is joker, so take max insted of min
        up = maxima[row + 1][col];
    }
    else { // not a joker so take min
        up = minima[row + 1][col];
    }
    int right;
    if(joker[row][col + 1]) { // right is joker, take max
        right = maxima[row][col + 1];
    }
    else { // no joker so take min
        right = minima[row][col + 1];
    }
    return plane[row][col] + max(up, right);
}

void print(const vector<vector<int> > &a) {
    for(int i = a.size() - 1; i >= 0; i --) {
        for(int k = 0; k < a[i].size(); k++) {
            cout << setw(4) << a[i][k];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int tests;
    cin >> tests;
    while(tests--) {
        // read in game
        int rows, cols;
        cin >> rows >> cols;
        vector<vector<int> > plane(rows, vector<int>(cols));
        for(int i = 0; i < rows; i++) {
            for(int k = 0; k < cols; k++) {
                int c;
                cin >> c;
                plane[i][k] = c;
            }
        }
        int j;
        cin >> j;
        vector<vector<bool> > joker(rows, vector<bool>(cols, false));
        for(int i = 0; i < j; i++) {
            int x, y;
            cin >> x >> y;
            joker[x - 1][y - 1] = true;
        }

        // calculate dp table
        vector<vector<int> > minima(rows, vector<int>(cols));
        vector<vector<int> > maxima(rows, vector<int>(cols));

        // fill uppermost rows
        int sum = 0;
        for(int i = cols - 1; i >= 0; i--) {
            sum += plane[rows - 1][i];
            minima[rows - 1][i] = sum;
            maxima[rows - 1][i] = sum;
        }

        // fill last rows
        sum = 0;
        for(int i = rows - 1; i >= 0; i--) {
            sum += plane[i][cols - 1];
            minima[i][cols - 1] = sum;
            maxima[i][cols - 1] = sum;
        }

        //fill in the missing parts
        for(int r = rows - 2; r >= 0; r--) {
            for(int c = cols - 2; c >= 0; c--) {
                minima[r][c] = min_best(plane, joker, minima, maxima, r, c);
                maxima[r][c] = max_best(plane, joker, minima, maxima, r, c);
            }
        }

        cout << maxima[0][0] << endl;
    }
    return 0;
}
