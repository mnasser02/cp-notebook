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
    vi tree;
    int n;

    SegTree(int _n) : n(_n) {
        while (__builtin_popcount(n) != 1) n++;
        tree.resize(2 * n);
    }

    SegTree(const vi &x) {
        n = x.size();
        while (__builtin_popcount(n) != 1) n++;
        tree.resize(2 * n);

        for (int i = 0; i < x.size(); i++) {
            tree[n + i] = x[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    int query(int p, int l, int r, int i, int j) {
        if (i <= l && r <= j) {
            return tree[p];
        }
        if (r < i || l > j) return 2e9;
        int m = l + r >> 1;
        return min(query(p << 1, l, m, i, j), query(p << 1 | 1, m + 1, r, i, j));
    }

    void update(int p, int x) {
        tree[n + p] = x;
        for (int j = n + p >> 1; j >= 1; j >>= 1) {
            tree[j] = min(tree[j << 1], tree[j << 1 | 1]);
        }
    }

    int query(int i, int j) { return query(1, 0, n - 1, i, j); }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vi x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    SegTree stree(x);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, u;
            cin >> k >> u;
            k--;
            stree.update(k, u);
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << stree.query(a, b) << "\n";
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
