#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<ll, ll, ll> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

int dp[1001][1001];
const int M = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<string> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (A[i][j] == '*') continue;
            if (i == n - 1 && i == j)
                dp[i][j] = 1;
            else
                dp[i][j] = (dp[i + 1][j] + dp[i][j + 1]) % M;
        }
    }
    cout << dp[0][0] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
