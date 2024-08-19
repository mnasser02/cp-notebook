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

using al3 = array<ll, 3>;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vii> AL(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        AL[u].push_back({v, w});
    }
    vector<vll> dist(n, vll(2, 1e18));
    priority_queue<al3, vector<al3>, greater<al3>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;
    while (!pq.empty()) {
        auto [d, u, b] = pq.top();
        pq.pop();
        if (d > dist[u][b]) continue;
        if (u == n - 1) break;
        for (auto [v, w] : AL[u]) {
            if (dist[u][b] + w < dist[v][b]) {
                dist[v][b] = dist[u][b] + w;
                pq.push({dist[v][b], v, b});
            }
            if (b == 0) {
                if (dist[u][0] + w / 2 < dist[v][1]) {
                    dist[v][1] = dist[u][0] + w / 2;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }
    cout << min(dist[n - 1][0], dist[n - 1][1]) << "\n";
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