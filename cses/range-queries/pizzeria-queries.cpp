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

int n, q;
vi stree1, stree2;

int query(vi &stree, int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return 2e9;
    }
    int m = l + r >> 1;
    return min(query(stree, p << 1, l, m, i, j), query(stree, p << 1 | 1, m + 1, r, i, j));
}
void update(vi &stree, int p, int x) {
    stree[n + p] = x;
    for (int j = n + p >> 1; j >= 1; j >>= 1) {
        stree[j] = min(stree[j << 1], stree[j << 1 | 1]);
    }
}
void solve() {
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ni = n;
    while (__builtin_popcount(n) != 1) {
        n++;
    }
    stree1.assign(2 * n, 2e9), stree2.assign(2 * n, 2e9);
    for (int i = 0; i < ni; i++) {
        stree1[n + i] = a[i] + i;
        stree2[n + i] = a[i] - i;
    }
    for (int i = n - 1; i >= 1; i--) {
        stree1[i] = min(stree1[i << 1], stree1[i << 1 | 1]);
        stree2[i] = min(stree2[i << 1], stree2[i << 1 | 1]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            update(stree1, k, k + x);
            update(stree2, k, x - k);
        } else {
            int k;
            cin >> k;
            k--;
            int ans = min(k + query(stree2, 1, 0, n - 1, 0, k - 1), query(stree1, 1, 0, n - 1, k, ni - 1) - k);
            cout << ans << "\n";
        }
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
