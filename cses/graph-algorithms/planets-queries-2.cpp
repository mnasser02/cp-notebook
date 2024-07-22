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

const int LOG = 30;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<vi> up(n, vi(LOG)), ALt(n);
    vi succ(n);
    for (int u = 0; u < n; u++) {
        int v;
        cin >> v;
        v--;
        up[u][0] = v;
        succ[u] = v;
        ALt[v].push_back(u);
    }

    vector<map<int, int>> cycles;
    vi cycle_id(n, -2);
    for (int u = 0; u < n; u++) {
        if (cycle_id[u] != -2) continue;
        vi path;
        int v = u;
        while (cycle_id[v] == -2) {
            path.push_back(v);
            cycle_id[v] = -3;
            v = succ[v];
        }
        map<int, int> cycle;
        bool in_cyc = 0;
        for (int x : path) {
            in_cyc = in_cyc || x == v;
            if (in_cyc) cycle[x] = cycle.size();
            cycle_id[x] = in_cyc ? cycles.size() : -1;
        }
        cycles.push_back(cycle);
    }

    vi dist(n);
    for (int s = 0; s < n; s++) {
        if (cycle_id[s] != -1 || cycle_id[succ[s]] == -1) continue;
        queue<int> q({s});
        dist[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : ALt[u]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int j = 1; j < LOG; j++) {
        for (int u = 0; u < n; u++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
    }

    auto advance = [&](int u, int k) {
        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {
                u = up[u][j];
            }
        }
        return u;
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (cycle_id[up[u][LOG - 1]] != cycle_id[up[v][LOG - 1]]) {
            cout << "-1\n";
        } else if (cycle_id[u] != -1 || cycle_id[v] != -1) {
            if (cycle_id[u] != -1 && cycle_id[v] == -1) {
                cout << "-1\n";
            } else {
                int d = dist[u];
                u = advance(u, d);

                int cid = cycle_id[v];
                int cu = cycles[cid][u], cv = cycles[cid][v];
                int csz = cycles[cid].size();
                d += (cv - cu + csz) % csz;
                cout << d << "\n";
            }
        } else {
            int d = dist[u] - dist[v];
            if (d >= 0 && advance(u, d) == v) {
                cout << d << "\n";
            } else {
                cout << "-1\n";
            }
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