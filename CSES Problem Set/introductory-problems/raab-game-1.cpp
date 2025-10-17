#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;

    if (a + b > n || a * b == 0 && a + b != 0) {
        cout << "NO\n";
        return;
    }

    vector<int> A(n), B(n);
    iota(A.begin(), A.end(), 1);
    iota(B.begin(), B.end(), 1);

    for (int i = 1; i <= a - (b > 1); i++) {
        swap(A[i], A[i - 1]);
    }
    for (int i = n - 2; i >= n - b - (a == 1 && b != 1); i--) {
        swap(A[i], A[i + 1]);
    }

    cout << "YES\n";
    for (int x : A) cout << x << ' ';
    cout << '\n';
    for (int x : B) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int tc = 1;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}