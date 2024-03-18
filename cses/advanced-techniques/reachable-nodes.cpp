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
#define AMl(x) (x).begin(), (x).end()
#define rAMl(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

vector<bitset<50000>> AM;
vector<vi> AL;
vi vis;
void dfs(int u) {
    vis[u] = 1;
    for (int v : AL[u]) {
        if (!vis[v]) {
            dfs(v);
        }
        AM[u] |= AM[v];
    }
}
void solve() {
    int n, m;
    cin >> n >> m;

    AM.assign(n, bitset<50000>());
    AL.assign(n, vi());
    vis.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
    }
    for (int u = 0; u < n; u++) {
        AM[u][u] = 1;
    }
    for (int u = 0; u < n; u++) {
        if (!vis[u]) dfs(u);
        cout << AM[u].count() << " ";
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
