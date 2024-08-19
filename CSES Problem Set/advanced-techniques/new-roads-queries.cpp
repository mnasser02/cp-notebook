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
    vi h, p;
    DSU(int n) {
        h.resize(n);
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
        if (px == py) {
            return 0;
        }
        if (h[px] < h[py]) {
            p[px] = py;
        } else {
            if (h[px] == h[py]) {
                h[px]++;
            }
            p[py] = px;
        }
        return 1;
    }
};

vector<vii> AL;
const int N = 2e5 + 10, LOG = 18;
int up[N][LOG], d[N], ans[N][LOG], vis[N];

void dfs(int u) {
    vis[u] = 1;
    for (auto [v, w] : AL[u]) {
        if (vis[v]) continue;
        d[v] = d[u] + 1;
        up[v][0] = u;
        ans[v][0] = w;
        for (int j = 1; j < LOG; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
            ans[v][j] = max(ans[v][j - 1], ans[up[v][j - 1]][j - 1]);
        }
        dfs(v);
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int k = d[u] - d[v];
    int res = 0;
    for (int j = LOG - 1; j >= 0; j--) {
        if (k & (1 << j)) {
            res = max(res, ans[u][j]);
            u = up[u][j];
        }
    }

    if (u == v) return res;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            res = max(res, ans[u][j]);
            res = max(res, ans[v][j]);
            u = up[u][j], v = up[v][j];
        }
    }
    res = max({res, ans[u][0], ans[v][0]});
    return res;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    AL.assign(n, vii());
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (dsu.join(u, v)) {
            AL[u].push_back({v, i + 1});
            AL[v].push_back({u, i + 1});
        }
    }
    for (int u = 0; u < n; u++) {
        if (!vis[u]) {
            dfs(u);
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (dsu.find(u) == dsu.find(v)) {
            cout << lca(u, v) << "\n";
        } else {
            cout << "-1\n";
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