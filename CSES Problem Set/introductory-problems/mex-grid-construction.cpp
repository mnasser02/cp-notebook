#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<int> present(i + j + 1);
            for (int p = 0; p < i; p++) {
                if (grid[p][j] < i + j) present[grid[p][j]] = 1;
            }
            for (int q = 0; q < j; q++) {
                if (grid[i][q] < i + j) present[grid[i][q]] = 1;
            }
            int mex = 0;
            while (present[mex]) mex++;
            grid[i][j] = mex;
            cout << mex << ' ';
        }
        cout << '\n';
    }
    return 0;
}