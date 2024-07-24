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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

struct DSU {
    struct save {
        int x, y, hx, hy;
    };

    vi h, p;
    int cc;
    stack<save> history;

    DSU(int n) : h(n), p(n), cc(n) {
        iota(all(p), 0);
    }

    int find(int x) { return x == p[x] ? x : find(p[x]); }

    bool join(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return false;
        } else {
            if (h[px] < h[py]) swap(px, py);

            history.push({px, py, h[px], h[py]});

            if (h[px] == h[py]) h[px]++;
            cc--;
            p[py] = px;

            return true;
        }
    }

    void rollback() {
        auto [x, y, hx, hy] = history.top();
        history.pop();
        p[x] = x, p[y] = y, h[x] = hx, h[y] = hy;
        cc++;
    }
};

struct query {
    int u, v;
    bool joined = 0;
    query(int u_, int v_) : u(u_), v(v_) {}
};

struct QueryTree {
    DSU dsu;
    vector<vector<query>> tree;
    vi ans;

    QueryTree(int n, int q) : dsu(n), tree(4 * q + 5), ans(q) {}

    void insert(int p, int l, int r, int i, int j, query qr) {
        if (i <= l && r <= j) {
            tree[p].push_back(qr);
            return;
        }
        if (l > j || r < i) return;
        int m = l + r >> 1;
        insert(p << 1, l, m, i, j, qr);
        insert(p << 1 | 1, m + 1, r, i, j, qr);
    }

    void dfs(int p, int l, int r) {
        for (query& qr : tree[p]) {
            qr.joined = dsu.join(qr.u, qr.v);
        }

        if (l == r) {
            ans[l] = dsu.cc;
        } else {
            int m = l + r >> 1;
            dfs(p << 1, l, m);
            dfs(p << 1 | 1, m + 1, r);
        }
        for (query qr : tree[p]) {
            if (qr.joined) dsu.rollback();
        }
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    map<ii, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);
        mp[{u, v}] = 0;
    }

    QueryTree qt(n, q + 1);
    for (int i = 1; i <= q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);

        if (t == 1) {
            mp[{u, v}] = i;
        } else {
            qt.insert(1, 0, q, mp[{u, v}], i - 1, query(u, v));
            mp.erase({u, v});
        }
    }

    for (auto [qr, i] : mp) {
        qt.insert(1, 0, q, i, q, query(qr.first, qr.second));
    }

    qt.dfs(1, 0, q);
    for (int x : qt.ans) cout << x << " ";
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