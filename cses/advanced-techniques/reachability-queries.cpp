#include <bits/stdc++.h>

using namespace std;

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

#pragma GCC target("popcnt")

vector<bitset<50000>> AM;
vector<vi> AL, AL2;
vi vis, dfs_num, dfs_low, id;
int dfsNumberCounter, numSCC;
stack<int> St;

void dfs(int u) {
    vis[u] = 1;
    for (int v : AL2[u]) {
        if (!vis[v]) {
            dfs(v);
        }
        AM[u] |= AM[v];
    }
}

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;
    dfsNumberCounter++;
    St.push(u);
    vis[u] = 1;
    for (auto& v : AL[u]) {
        if (dfs_num[v] == -1)
            tarjanSCC(v);
        if (vis[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_low[u] == dfs_num[u]) {
        ++numSCC;
        while (1) {
            int v = St.top();
            id[v] = u;
            St.pop();
            vis[v] = 0;
            if (u == v) break;
        }
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    AM.assign(n, bitset<50000>());
    AL.assign(n, vi());
    AL2.assign(n, vi());
    id.assign(n, -1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
    }
    for (int u = 0; u < n; u++) {
        AM[u][u] = 1;
    }

    dfs_num.assign(n, -1);
    dfs_low.assign(n, 0);
    vis.assign(n, 0);
    while (!St.empty()) St.pop();
    dfsNumberCounter = numSCC = 0;
    for (int u = 0; u < n; ++u)
        if (dfs_num[u] == -1)
            tarjanSCC(u);

    for (int u = 0; u < n; u++) {
        for (int v : AL[u]) {
            if (id[u] != id[v]) {
                AL2[id[u]].push_back(id[v]);
            }
        }
    }
    vis.assign(n, 0);
    for (int u = 0; u < n; u++) {
        if (!vis[u] && u == id[u]) {
            dfs(u);
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << (AM[id[u]][id[v]] ? "YES" : "NO") << "\n";
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
