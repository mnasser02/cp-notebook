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
#define LSOne(S) ((S) & (-S))

const int M = 1e9 + 7;
int mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}
int mod_inv(ll x) {
    return mod_pow(x % M, M - 2);
}

void solve() {
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll i = 1; i * i <= n; i++) {
        ans = (ans + n / i * i) % M;
    }
    ll l = (ll)sqrt(n) + 1;
    for (ll i = sqrt(n); i >= 1; i--) {
        ll r = n / i;
        ll add = (r - l + 1 + M) % M * ((l + r) % M) % M * mod_inv(2) % M;
        add = add * i % M;
        ans = (ans + add) % M;
        l = r + 1;
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
