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

const int N = 2e5 + 5;
vi AL[N];
ll sz[N], ans[N], dist[N];
int n;

void dfs1(int u, int p) {
    sz[u] = 1;
    for (int v : AL[u]) {
        if (v == p) continue;
        dist[v] = 1 + dist[u];
        dfs1(v, u);
        sz[u] += sz[v];
    }
}

void dfs2(int u, int p) {
    for (int v : AL[u]) {
        if (v == p) continue;
        ans[v] = ans[u] + n - 2 * sz[v];
        dfs2(v, u);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    dfs1(0, -1);
    for (int u = 0; u < n; u++) {
        ans[0] += dist[u];
    }
    dfs2(0, -1);
    for (int u = 0; u < n; u++) cout << ans[u] << " ";
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
