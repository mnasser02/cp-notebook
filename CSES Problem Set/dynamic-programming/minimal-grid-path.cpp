#include <bits/stdc++.h>

using namespace std;

const int N = 3001;
string A[N];
bitset<N> active[2 * N];
int n;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    active[0][0] = 1;
    for (int i = 1; i < 2 * n - 1; i++) {
        char mnc = 'Z';
        for (int r = min(n - 1, i); r >= 0; r--) {
            int c = i - r;
            if (c >= n) break;
            if (A[r][c] <= mnc && (active[i - 1][r] || (r - 1 >= 0 && active[i - 1][r - 1]))) {
                if (A[r][c] < mnc) active[i].reset();
                active[i][r] = 1;
                mnc = A[r][c];
            }
        }
    }

    string ans;
    int i = 2 * n - 1;
    int r = n - 1;
    while (i--) {
        if (!active[i][r]) {
            r--;
        }
        int c = i - r;
        ans.push_back(A[r][c]);
    }

    reverse(ans.begin(), ans.end());
    cout << ans;

    return 0;
}
