#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<ld>> dp(n + 1, vector<ld>(6 * n + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int s = 6 * n; s >= 1; s--) {
            for (int x = 1; x <= min(6, s); x++) {
                dp[i][s] += dp[i - 1][s - x];
            }
            // dp[i][s] /= 6.0;
        }
    }
    ld ans = 0;
    for (int i = a; i <= b; i++) {
        ans += dp[n][i];
    }
    ans /= pow(6.0, n);

    cout << fixed << ans << "\n";
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
