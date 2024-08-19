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

const int M = 1e9 + 7;
const int M2 = M - 1;

ll mod_pow(ll b, ll p, ll m) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % m;
        b = b * b % m;
        p >>= 1;
    }
    return ans;
}

ll mod_inv(ll x) {
    return mod_pow(x % M, M - 2, M);
}

void solve() {
    ll n;
    cin >> n;
    ll num = 1, sum = 1, prod = 1;
    vii a;

    ll num2 = 1;

    bool ev = true;
    for (int i = 0; i < n; i++) {
        ll x, k;
        cin >> x >> k;
        if (k % 2 && ev) {
            ev = false;
            num2 = num2 * (1 + k) / 2 % M2;
        } else
            num2 = num2 * (1 + k) % M2;

        a.push_back({x, k});

        num = num * (1 + k) % M;

        ll geom = (mod_pow(x, k + 1, M) - 1 + M) % M * mod_inv(x - 1 + M) % M;
        sum = sum * geom % M;
    }

    for (auto [x, k] : a) {
        if (ev)
            prod = (prod * mod_pow(x, (k / 2 * num2) % M2, M)) % M;
        else
            prod = (prod * mod_pow(x, (k * num2) % M2, M)) % M;
    }
    cout << num << " " << sum << " " << prod << "\n";
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
