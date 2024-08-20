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

struct DSU {
    vi p, h;
    DSU(int n) {
        h.assign(n, 0);
        p.resize(n);
        iota(all(p), 0);
    }
    int find(int x) {
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }
    bool join(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py)
            return false;
        if (h[px] < h[py]) {
            p[px] = py;
        } else {
            p[py] = px;
            if (h[px] == h[py])
                h[px]++;
        }
        return true;
    }
};

struct node {
    ll sum, pre, suf, mx;
    node(ll x = -1e18) : sum(x), pre(x), suf(x), mx(x) {}
};

struct LCA {
    vector<vii>& AL;
    vector<vi> up;
    vector<vector<node>> dp;
    vi d, vis;
    int n, log;

    LCA(vector<vii>& AL_) : AL(AL_) {
        n = AL.size();
        vis.resize(n);
        d.resize(n);
        log = log2(n) + 2;
        up.assign(n, vi(log));
        dp.assign(n, vector<node>(log));

        for (int u = 0; u < n; u++) {
            if (!vis[u]) dfs(u);
        }
    }

    node merge(node a, node b) {
        node res;
        res.sum = a.sum + b.sum;
        res.pre = max(a.pre, a.sum + b.pre);
        res.suf = max(b.suf, a.suf + b.sum);
        res.mx = max({a.mx, b.mx, a.suf + b.pre});
        return res;
    }

    void dfs(int u) {
        vis[u] = 1;
        for (auto [v, w] : AL[u]) {
            if (vis[v]) continue;
            d[v] = d[u] + 1;
            up[v][0] = u;
            dp[v][0] = node(w);
            for (int j = 1; j < log; j++) {
                dp[v][j] = merge(dp[v][j - 1], dp[up[v][j - 1]][j - 1]);
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            dfs(v);
        }
    }

    ll get(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int k = d[u] - d[v];
        node res, left, right;
        for (int j = 0; j < log; j++) {
            if (k & (1 << j)) {
                left = merge(left, dp[u][j]);
                u = up[u][j];
            }
        }

        if (u == v) {
            return left.mx;
        }

        for (int j = log - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                left = merge(left, dp[u][j]);
                right = merge(right, dp[v][j]);
                u = up[u][j];
                v = up[v][j];
            }
        }
        left = merge(left, dp[u][0]);
        right = merge(right, dp[v][0]);
        swap(right.pre, right.suf);
        res = merge(left, right);
        return res.mx;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    DSU dsu(n);
    vector<vii> AL(n);
    vii queries;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            u--, v--;
            if (dsu.join(u, v)) {
                AL[u].push_back({v, x});
                AL[v].push_back({u, x});
            }
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (dsu.find(u) != dsu.find(v) || u == v) {
                queries.push_back({-1, -1});
            } else {
                queries.push_back({u, v});
            }
        }
    }
    LCA lca(AL);
    for (auto [u, v] : queries) {
        if (u == -1) {
            cout << "Nope\n";
        } else {
            cout << lca.get(u, v) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}