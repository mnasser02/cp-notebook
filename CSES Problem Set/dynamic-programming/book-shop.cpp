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

int dp[1001][100'001];
void solve() {
    int n, x;
    cin >> n >> x;
    vi h(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> s[i];

    for (int i = 1; i <= n; i++) {
        for (int y = 0; y <= x; y++) {
            dp[i][y] = dp[i - 1][y];
            if (y - h[i] >= 0)
                dp[i][y] = max(dp[i][y], dp[i - 1][y - h[i]] + s[i]);
        }
    }
    cout << dp[n][x] << "\n";
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
