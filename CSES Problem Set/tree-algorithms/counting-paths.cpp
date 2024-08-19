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

const int N = 2e5 + 5, LOG = 18;
vi AL[N];
int up[N][LOG], d[N], a[N], ans[N];

void dfs1(int u, int p) {
    for (int v : AL[u]) {
        if (v == p) continue;
        up[v][0] = u;
        d[v] = d[u] + 1;
        for (int j = 1; j < LOG; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
        dfs1(v, u);
    }
}
int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    int k = d[u] - d[v];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((1 << j) & k) {
            u = up[u][j];
        }
    }

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j], v = up[v][j];
        }
    }
    return up[u][0];
}
void dfs2(int u, int p) {
    ans[u] = a[u];
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs2(v, u);
        ans[u] += ans[v];
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    dfs1(0, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int anc = lca(u, v);
        a[u]++, a[v]++;
        if (anc)
            a[up[anc][0]]--;
        a[anc]--;
    }
    dfs2(0, -1);
    for (int u = 0; u < n; u++) {
        cout << ans[u] << " \n"[u == n - 1];
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
