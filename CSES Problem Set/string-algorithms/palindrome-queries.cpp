#include <bits/stdc++.h>

using namespace std;

#define int ll

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

const int N = 1 << 18, M = 1e9 + 9, p = 131;
int stree[2 * N], P[N], iP[N], stree2[2 * N];

int query(int stree[], int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return 0;
    }
    int m = l + r >> 1;
    return (query(stree, p << 1, l, m, i, j) + query(stree, p << 1 | 1, m + 1, r, i, j)) % M;
}
void update(int stree[], int p, int x) {
    stree[N + p] = x;
    for (int j = N + p >> 1; j >= 1; j >>= 1) {
        stree[j] = (stree[j << 1] + stree[j << 1 | 1]) % M;
    }
}

ll mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}
ll mod_inv(ll x) { return mod_pow(x, M - 2); }

void preprocess() {
    P[0] = 1;
    for (int i = 1; i < N; i++) P[i] = (ll)p * P[i - 1] % M;
    iP[N - 1] = mod_inv(P[N - 1]);
    for (int i = N - 2; i >= 0; i--) iP[i] = (ll)p * iP[i + 1] % M;
}

int n, q;
string s;

int hash_fast(int stree[], int l, int r, int t) {
    int x = query(stree, 1, 0, N - 1, l, r);
    int ans = (ll)x * (t == 1 ? iP[l] : iP[n - 1 - r]) % M;
    return ans;
}

void solve() {
    cin >> n >> q >> s;
    preprocess();
    for (int i = 0; i < n; i++) {
        stree[N + i] = (ll)s[i] * P[i] % M;
        stree2[N + i] = (ll)s[i] * P[n - 1 - i] % M;
    }
    for (int i = N - 1; i >= 1; i--) {
        stree[i] = (stree[i << 1] + stree[i << 1 | 1]) % M;
        stree2[i] = (stree2[i << 1] + stree2[i << 1 | 1]) % M;
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            char x;
            cin >> k >> x;
            k--;
            update(stree, k, (ll)x * P[k] % M);
            update(stree2, k, (ll)x * P[n - 1 - k] % M);
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            int m = (a + b + 1) / 2;
            int h1 = hash_fast(stree, a, m - 1, 1);
            int h2 = hash_fast(stree2, m + ((a - b + 1) % 2 != 0), b, 2);
            if (h1 == h2) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
