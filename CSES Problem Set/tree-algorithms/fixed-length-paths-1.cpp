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
int sz[N], cnt[N];
bool done[N];

int n, k, mx_depth;
ll ans;

int get_sizes(int u, int p) {
    sz[u] = 1;
    for (int v : AL[u]) {
        if (v == p || done[v]) continue;
        sz[u] += get_sizes(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int p, int tree_size) {
    for (int v : AL[u]) {
        if (v == p || done[v]) continue;
        if (sz[v] > tree_size / 2) {
            return get_centroid(v, u, tree_size);
        }
    }
    return u;
}

void dfs(int u, int p, int d, bool filling) {
    if (d > k) return;
    if (filling) {
        mx_depth = max(mx_depth, d);
        cnt[d]++;
    } else
        ans += cnt[k - d];
    for (int v : AL[u]) {
        if (v == p || done[v]) continue;
        dfs(v, u, d + 1, filling);
    }
}

void decompose(int u) {
    int centroid = get_centroid(u, -1, get_sizes(u, -1));

    mx_depth = 0;
    cnt[0] = 1;
    for (int v : AL[centroid]) {
        if (done[v]) continue;
        dfs(v, centroid, 1, false);
        dfs(v, centroid, 1, true);
    }
    fill(cnt, cnt + mx_depth + 1, 0);

    done[centroid] = 1;
    for (int v : AL[centroid]) {
        if (done[v]) continue;
        decompose(v);
    }
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    decompose(0);

    cout << ans << "\n";
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
