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

int dp[1'000'005];
const int M = 1e9 + 7;
void solve() {
    int n, x;
    cin >> n >> x;
    vi c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= x; s++) {
            if (s - c[i] >= 0) {
                dp[s] += dp[s - c[i]];
                dp[s] %= M;
            }
        }
    }

    cout << dp[x] << "\n";
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
