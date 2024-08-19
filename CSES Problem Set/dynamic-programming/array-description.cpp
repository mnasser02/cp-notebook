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

ll dp[100'005][105];
const int M = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if (a[1])
        dp[1][a[1]] = 1;
    else {
        for (int j = 1; j <= m; j++) dp[1][j] = 1;
    }

    for (int i = 2; i <= n; i++) {
        if (a[i]) {
            dp[i][a[i]] = (dp[i - 1][a[i] - 1] + dp[i - 1][a[i]] + dp[i - 1][a[i] + 1]) % M;
        } else {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % M;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) ans = (ans + dp[n][i]) % M;
    cout << ans << "\n";
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
