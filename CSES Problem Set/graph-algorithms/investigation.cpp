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

const int M = 1e9 + 7;
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

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<array<ll, 4>> dist(n, {(ll)1e18l});
    dist[0] = {0, 1, 0, 0};
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (u == n - 1) break;
        if (d > dist[u][0]) continue;
        for (auto [v, w] : AL[u]) {
            ll new_d = dist[u][0] + w;
            if (new_d == dist[v][0]) {
                dist[v][1] = (dist[v][1] + dist[u][1]) % M;
                ckmin(dist[v][2], dist[u][2] + 1);
                ckmax(dist[v][3], dist[u][3] + 1);
            } else if (new_d < dist[v][0]) {
                dist[v][0] = new_d;
                dist[v][1] = dist[u][1];
                dist[v][2] = dist[u][2] + 1;
                dist[v][3] = dist[u][3] + 1;
                pq.push({new_d, v});
            }
        }
    }
    for (ll x : dist[n - 1]) cout << x << " ";
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