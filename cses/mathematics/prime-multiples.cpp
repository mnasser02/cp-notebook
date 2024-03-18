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
    ll n;
    cin >> n;
    int k;
    cin >> k;
    vll a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int bm = 1; bm < (1 << k); bm++) {
        ll val = 1;
        int c = 0;
        for (int msk = bm; msk; msk ^= LSOne(msk)) {
            int v = __builtin_ctz(msk);
            if (val > n / a[v]) {
                c = 0;
                break;
            }
            val *= a[v];
            c++;
        }
        if (!c) continue;
        if (c % 2 == 0)
            ans -= n / val;
        else
            ans += n / val;
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