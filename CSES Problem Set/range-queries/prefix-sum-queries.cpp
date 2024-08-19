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
    ll sum, pre;
    node(ll x = 0) : sum(x), pre(max(x, 0ll)) {}
};

int n, q;
vector<node> stree;

node merge(node a, node b) {
    node res;
    res.sum = a.sum + b.sum;
    res.pre = max(a.sum + b.pre, a.pre);
    return res;
}
node query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return node();
    }
    int m = l + r >> 1;
    return merge(query(p << 1, l, m, i, j), query(p << 1 | 1, m + 1, r, i, j));
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
        int t;
        cin >> t;
        if (t == 1) {
            int k, u;
            cin >> k >> u;
            k--;
            update(k, u);
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << query(1, 0, n - 1, a, b).pre << "\n";
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
