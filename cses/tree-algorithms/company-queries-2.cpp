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
int n, up[N][LOG], d[N];

void dfs(int u) {
    for (int v : AL[u]) {
        up[v][0] = u;
        for (int j = 1; j < LOG; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
        d[v] = d[u] + 1;
        dfs(v);
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
void solve() {
    int q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        AL[u].push_back(i);
    }
    dfs(1);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
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
