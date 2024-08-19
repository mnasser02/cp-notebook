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

vector<vi> AL;
vi dfs_low, dfs_num, p;
int dfs_ctr;
vii ans;

void bridges(int u) {
    dfs_low[u] = dfs_num[u] = dfs_ctr++;
    for (int v : AL[u]) {
        if (dfs_num[v] == -1) {
            p[v] = u;
            bridges(v);
            if (dfs_low[v] > dfs_num[u]) {
                ans.push_back({u, v});
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (p[u] != v) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    AL.assign(n, vi());
    dfs_low.assign(n, -1);
    dfs_num.assign(n, -1);
    p.assign(n, -1);
    dfs_ctr = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        AL[--u].push_back(--v);
        AL[v].push_back(u);
    }

    bridges(0);

    cout << ans.size() << "\n";
    for (auto [u, v] : ans) {
        cout << ++u << " " << ++v << "\n";
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