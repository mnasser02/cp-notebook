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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vii> AL(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        AL[u].push_back({v, w});
    }

    vector<priority_queue<ll>> dist(n);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[0].push(0);
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        if (u == n - 1 && dist[n - 1].size() == k && d == dist[n - 1].top()) break;
        pq.pop();
        if (d > dist[u].top()) continue;
        for (auto [v, w] : AL[u]) {
            ll new_d = d + w;
            if (dist[v].size() < k) {
                dist[v].push(new_d);
                pq.push({new_d, v});
            } else if (dist[v].top() > new_d) {
                dist[v].pop();
                dist[v].push(new_d);
                pq.push({new_d, v});
            }
        }
    }

    vll ans;
    while (!dist[n - 1].empty()) {
        ans.push_back(dist[n - 1].top());
        dist[n - 1].pop();
    }
    reverse(all(ans));
    for (ll x : ans) {
        cout << x << " ";
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