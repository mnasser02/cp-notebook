#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

void solve() {
    int n;
    cin >> n;
    vll x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        x[i] += x[i - 1];
    }

    vector<vll> dp(n, vll(n)), opt(n, vll(n));

    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            ll mn = 1e18;
            ll cost = x[j + 1] - x[i];
            for (int k = opt[i][j - 1]; k <= min(opt[i + 1][j], (ll)j - 1); k++) {
                ll cur = dp[i][k] + dp[k + 1][j];
                if (cur <= mn) {
                    opt[i][j] = k;
                    mn = cur;
                }
            }
            dp[i][j] = mn + cost;
        }
    }
    cout << dp[0][n - 1] << "\n";
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