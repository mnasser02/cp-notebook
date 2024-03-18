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

const int M = 1e9 + 7, MXN = 2e6 + 5;
ll fac[MXN];
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
    return mod_pow(x % M, M - 2);
}

ll C(ll n, ll k) {
    if (n < k) return 0;
    return fac[n] * mod_inv(fac[n - k]) % M * mod_inv(fac[k]) % M;
}
void solve() {
    int n;
    cin >> n;
    if (n % 2) {
        cout << "0\n";
        return;
    }
    n /= 2;
    cout << C(2 * n, n) * mod_inv(n + 1) % M << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    fac[0] = 1;
    for (ll i = 1; i < MXN; i++) {
        fac[i] = fac[i - 1] * i % M;
    }

    while (tc--) {
        solve();
    }
    return 0;
}
