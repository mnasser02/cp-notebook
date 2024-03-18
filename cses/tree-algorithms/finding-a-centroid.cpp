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
int sz[N], n;

void dfs1(int u, int p) {
    sz[u] = 1;
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
    }
}
int dfs2(int u, int p) {
    bool found = true;
    for (int v : AL[u]) {
        if (v == p) continue;
        if (sz[v] > n / 2) {
            return dfs2(v, u);
        }
    }
    return u;
}

void solve() {
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    dfs1(0, -1);
    cout << dfs2(0, -1) + 1 << "\n";
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
