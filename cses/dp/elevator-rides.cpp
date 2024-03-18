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

void solve() {
    int n, x;
    cin >> n >> x;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pll> dp(1 << n);
    dp[0] = {1, 0};
    for (int bm = 1; bm < (1 << n); bm++) {
        dp[bm] = {n + 1, 0};
        for (int i = 0; i < n; i++) {
            if ((1 << i) & bm) {
                pll cur = dp[bm ^ (1 << i)];
                if (a[i] + cur.second <= x) {
                    cur.second += a[i];
                } else {
                    cur.first++;
                    cur.second = a[i];
                }
                dp[bm] = min(dp[bm], cur);
            }
        }
    }
    cout << dp[(1 << n) - 1].first << "\n";
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
