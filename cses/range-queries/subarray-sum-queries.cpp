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

struct SegTree {
    struct node {
        ll sum, pre, suf, mx;
        node(ll x = 0) : sum(x) {
            x = max(x, 0ll);
            pre = x, suf = x, mx = x;
        }
    };

    vector<node> tree;
    int n;

    SegTree(const vi &x) {
        n = x.size();
        while (__builtin_popcount(n) != 1) n++;
        tree.resize(2 * n);

        for (int i = 0; i < x.size(); i++) {
            tree[n + i] = node(x[i]);
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    node merge(node a, node b) {
        node res;
        res.sum = a.sum + b.sum;
        res.pre = max(a.sum + b.pre, a.pre);
        res.suf = max(b.suf, a.suf + b.sum);
        res.mx = max({a.suf + b.pre, a.mx, b.mx});
        return res;
    }

    node query(int p, int l, int r, int i, int j) {
        if (i <= l && r <= j) {
            return tree[p];
        }
        if (r < i || l > j) return 0;
        int m = l + r >> 1;
        return merge(query(p << 1, l, m, i, j), query(p << 1 | 1, m + 1, r, i, j));
    }

    void update(int p, int x) {
        tree[n + p] = x;
        for (int j = n + p >> 1; j >= 1; j >>= 1) {
            tree[j] = merge(tree[j << 1], tree[j << 1 | 1]);
        }
    }
    node query(int i, int j) { return query(1, 0, n - 1, i, j); }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree st(a);

    while (q--) {
        int k, u;
        cin >> k >> u;
        k--;
        st.update(k, u);
        cout << st.tree[1].mx << "\n";
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
