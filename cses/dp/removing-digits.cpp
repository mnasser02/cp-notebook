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

int dp[1'000'001];
void solve() {
    int n;
    cin >> n;

    dp[0] = 0;

    for (int s = 1; s <= n; s++) {
        dp[s] = 1e9;
        int x = s;
        while (x) {
            int i = x % 10;
            dp[s] = min(dp[s], dp[s - i] + 1);
            x /= 10;
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
