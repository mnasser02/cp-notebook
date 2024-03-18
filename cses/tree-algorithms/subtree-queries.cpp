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

const int N = 1 << 18;
vi AL[N];
int in[N], out[N], a[N];
ll stree[2 * N];

int timer;

void dfs(int u, int p) {
    in[u] = ++timer;
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    out[u] = timer;
}

ll query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) {
        return stree[p];
    }
    if (r < i || l > j) {
        return 0;
    }
    int m = l + r >> 1;
    return query(p << 1, l, m, i, j) + query(p << 1 | 1, m + 1, r, i, j);
}

void update(int p, int x) {
    stree[N + p] = x;
    for (int j = N + p >> 1; j >= 1; j >>= 1) {
        stree[j] = stree[j << 1] + stree[j << 1 | 1];
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        update(in[i], a[i]);
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            i--;
            update(in[i], x);
        } else {
            int i;
            cin >> i;
            i--;
            cout << query(1, 0, N - 1, in[i], out[i]) << "\n";
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
