#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

const int M = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    int tot = n * (n + 1) / 2;
    if (tot % 2) {
        cout << "0\n";
        return;
    }

    int tar = tot / 2;
    ll dp[n + 1][tar + 1];
    memset(dp, 0, sizeof dp);

    dp[0][0] = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int s = 0; s <= tar; s++) {
            dp[i][s] = dp[i - 1][s];
            if (s - i >= 0) {
                dp[i][s] += dp[i - 1][s - i];
            }
            dp[i][s] %= M;
        }
    }
    cout << dp[n - 1][tar] << "\n";
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
