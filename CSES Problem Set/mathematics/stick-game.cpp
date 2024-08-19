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

int dp[1000001];
vi a;
void solve() {
    int n, k;
    cin >> n >> k;
    a.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        dp[a[i]] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < a.size(); j++) {
            if (a[j] <= i) {
                dp[i] |= ~dp[i - a[j]];
            }
        }
        cout << (dp[i] ? "W" : "L");
    }
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
