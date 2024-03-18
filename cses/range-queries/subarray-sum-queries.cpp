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

struct node {
    ll sum, pre, suf, mx;
    node(ll x = 0) : sum(x) {
        x = max(x, 0ll);
        pre = x, suf = x, mx = x;
    }
};

int n, q;
vector<node> stree;

node merge(node a, node b) {
    node res;
    res.sum = a.sum + b.sum;
    res.pre = max(a.sum + b.pre, a.pre);
    res.suf = max(b.suf, a.suf + b.sum);
    res.mx = max({a.suf + b.pre, a.mx, b.mx});
    return res;
}

void update(int p, int x) {
    stree[n + p] = x;
    for (int j = n + p >> 1; j >= 1; j >>= 1) {
        stree[j] = merge(stree[j << 1], stree[j << 1 | 1]);
    }
}

void solve() {
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    while (__builtin_popcount(n) != 1) {
        n++;
    }
    stree.resize(2 * n);
    for (int i = 0; i < a.size(); i++) {
        stree[n + i] = node(a[i]);
    }
    for (int i = n - 1; i >= 1; i--) {
        stree[i] = merge(stree[i << 1], stree[i << 1 | 1]);
    }
    while (q--) {
        int k, u;
        cin >> k >> u;
        k--;
        update(k, u);
        cout << stree[1].mx << "\n";
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
