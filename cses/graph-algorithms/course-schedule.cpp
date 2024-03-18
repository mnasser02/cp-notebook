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

template <class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

vector<vi> AL;
vi topo, vis, p;
bool cycle;
void dfs(int u) {
    vis[u] = 1;
    for (auto v : AL[u]) {
        if (!vis[v]) {
            p[v] = u;
            dfs(v);
        } else if (vis[v] == 1) {
            // if (p[u] != v) {  // non-trivial cycle
            cycle = true;
            // }
        }
    }
    vis[u] = 2;
    topo.push_back(u);
}

void solve() {
    int n, m;
    cin >> n >> m;
    AL.assign(n, vi());
    vis.assign(n, 0);
    p.assign(n, -1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
    }
    for (int u = 0; u < n; u++) {
        if (!vis[u]) dfs(u);
    }

    if (cycle) {
        cout << "IMPOSSIBLE\n";
    } else {
        reverse(all(topo));
        for (int u : topo) cout << u + 1 << " ";
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
