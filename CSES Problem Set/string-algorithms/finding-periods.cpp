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

const int N = 1e6 + 5, M = 1e9 + 9;
int P[N], iP[N], p = 131;

int mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}
int mod_inv(ll x) { return mod_pow(x, M - 2); }

void preprocess() {
    P[0] = 1;
    for (int i = 1; i < N; i++) {
        P[i] = (ll)p * P[i - 1] % M;
    }
    iP[N - 1] = mod_inv(P[N - 1]);
    for (int i = N - 2; i >= 0; i--) {
        iP[i] = (ll)p * iP[i + 1] % M;
    }
}

vi rolling_hash(string& s) {
    int n = s.size();
    vi h(n);
    for (int i = 0; i < n; i++) {
        h[i] = (ll)P[i] * s[i] % M;
        if (i) h[i] += h[i - 1];
        h[i] %= M;
    }
    return h;
}

int hash_fast(vi& h, int l, int r) {
    if (l == 0) return h[r];

    return (ll)(h[r] - h[l - 1] + M) % M * iP[l] % M;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    preprocess();
    vi h = rolling_hash(s);

    vi good(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        int href = hash_fast(h, 0, i - 1);
        bool ok = true;
        for (int j = 2 * i - 1; j < n; j += i) {
            if (hash_fast(h, j - i + 1, j) != href) {
                ok = false;
                break;
            }
        }
        if (n % i && hash_fast(h, n - (n % i), n - 1) != hash_fast(h, 0, n % i - 1)) ok = false;
        if (ok) cout << i << " ";
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
