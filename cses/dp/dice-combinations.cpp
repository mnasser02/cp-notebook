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

const int M = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    int dp[n + 10] = {0, 1, 1, 1, 1, 1, 1};
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= 6; x++) {
            if (i - x >= 0) {
                dp[i] += dp[i - x];
                dp[i] %= M;
            }
        }
    }
    cout << dp[n] << "\n";
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
