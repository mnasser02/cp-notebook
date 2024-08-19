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

const int M = 1e9 + 7;
ll mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * b % M;
        b = b * b % M;
        p >>= 1;
    }
    return ans;
}

vector<vi> AL;
int cc;
vi vis;
void dfs(int u) {
    vis[u] = 1;
    for (int v : AL[u]) {
        if (!vis[v]) dfs(v);
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    AL.assign(n, vi());
    vis.assign(n, 0);
    cc = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        AL[--u].push_back(--v);
        AL[v].push_back(u);
    }

    for (int u = 0; u < n; u++) {
        if (!vis[u]) {
            dfs(u);
            cc++;
        }
    }
    cout << mod_pow(2, m - n + cc) << "\n";
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