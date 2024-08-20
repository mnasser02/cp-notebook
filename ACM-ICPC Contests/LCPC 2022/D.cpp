#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

const int M = 1e9 + 7, N = 1e5 + 5;
int fac[N];

ll mpow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}
ll minv(ll x) { return mpow(x, M - 2); }

ll C(ll n, ll k) {
    if (k > n) return 0;
    return fac[n] * minv(fac[n - k]) % M * minv(fac[k]) % M;
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll ans = (n == m) * n;
    for (int mex = 0; mex <= min(m, n - 1); mex++) {
        ans += C(n - mex - 1, m - mex) * mex % M;
        ans %= M;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = (ll)fac[i - 1] * i % M;

    while (tc--) {
        solve();
    }
    return 0;
}