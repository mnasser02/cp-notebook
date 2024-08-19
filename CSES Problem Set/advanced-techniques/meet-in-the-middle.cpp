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
#define LSOne(S) ((S) & -(S))

void solve() {
    int n, x;
    cin >> n >> x;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vll v;

    for (int msk = 0; msk < (1 << (n / 2)); msk++) {
        ll sum = 0;
        for (int m = msk; m; m ^= LSOne(m)) {
            int v = __builtin_ctz(m);
            sum += a[v];
        }
        v.push_back(sum);
    }
    sort(all(v));

    ll ans = 0;
    for (int msk = 0; msk < (1 << ((n + 1) / 2)); msk++) {
        ll sum = 0;
        for (int m = msk; m; m ^= LSOne(m)) {
            int v = __builtin_ctz(m);
            sum += a[n / 2 + v];
        }
        ans += upper_bound(all(v), x - sum) - lower_bound(all(v), x - sum);
    }

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
