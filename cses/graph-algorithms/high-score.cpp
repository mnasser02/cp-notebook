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

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vii> AL(n);
    vector<vi> ALr(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        AL[u].push_back({v, -w});
        ALr[v].push_back(u);
    }

    queue<int> q;
    vll dist(n, 1e18);
    vi freq(n, 0);
    vector<bool> in_queue(n), cycle(n);

    q.push(0);
    dist[0] = 0;
    in_queue[0] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = 0;
        for (auto& [v, w] : AL[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            if (in_queue[v]) continue;
            freq[v]++;
            if (freq[v] > n) {
                cycle[v] = 1;

            } else {
                q.push(v);
                in_queue[v] = 1;
            }
        }
    }
    vi vis(n);
    bool inf = 0;
    auto dfs = [&](auto self, int u) {
        vis[u] = 1;
        if (cycle[u]) {
            inf = 1;
            return;
        }
        for (int v : ALr[u]) {
            if (!vis[v]) self(self, v);
        }
    };
    dfs(dfs, n - 1);

    if (inf)
        cout << "-1";
    else
        cout << -dist[n - 1];
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