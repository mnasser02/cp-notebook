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
    int n;
    cin >> n;
    vi succ(n);
    for (int u = 0; u < n; u++) {
        int v;
        cin >> v;
        v--;
        succ[u] = v;
    }

    vi vis(n), dist(n, -1), tin(n), path;
    int timer, x;
    auto dfs = [&](auto self, int u) -> void {
        path.push_back(u);
        vis[u] = 1;
        tin[u] = timer++;

        int v = succ[u];
        if (!vis[v]) {
            self(self, v);
        } else {
            if (dist[v] == -1)
                dist[v] = tin[u] - tin[v] + 1;
            else {
                tin[v] = timer;
            }
            x = v;
        }
    };

    for (int s = 0; s < n; s++) {
        if (!vis[s]) {
            timer = 0;
            path.clear();
            dfs(dfs, s);
            bool cyc = 0;
            for (int u : path) {
                cyc = cyc || u == x;
                dist[u] = dist[x];
                if (!cyc) dist[u] += tin[x] - tin[u];
            }
        }
        cout << dist[s] << " ";
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