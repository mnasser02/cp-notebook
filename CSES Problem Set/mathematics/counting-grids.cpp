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

const int M = 1e9 + 7;

ll mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}
ll mod_inv(ll x) {
    return mod_pow(x, M - 2);
}

void solve() {
    ll n;
    cin >> n;

    ll cnt = (n - 1) / 2;
    ll x = cnt * (2 * 2 + 2 * (cnt - 1)) / 2;

    ll p1 = (cnt + 1) * (n - 1) - x + (n % 2), p2 = 2 * p1 - (n % 2);

    ll ans = (2 * mod_pow(2, p1)) % M + mod_pow(2, p2);
    ans %= M;
    ans = (ans + mod_pow(2, n * n)) % M;

    ans = ans * mod_inv(4) % M;

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
