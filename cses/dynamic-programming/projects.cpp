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
    int n;
    cin >> n;
    vector<iii> arr;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        arr.push_back({a, b, c});
    }
    arr.push_back({1e9, 1e9, 0});
    sort(all(arr));
    vll dp(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        auto [a, b, c] = arr[i];
        auto it = lower_bound(arr.begin() + i, arr.end(), tuple{b + 1, 0, 0});
        dp[i] = dp[i + 1];
        if (it != arr.end()) {
            int j = it - arr.begin();
            dp[i] = max(dp[i], dp[j] + c);
        }
    }
    cout << dp[0] << "\n";
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
