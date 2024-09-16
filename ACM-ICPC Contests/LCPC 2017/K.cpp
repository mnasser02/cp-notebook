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
    int n, q;
    cin >> n >> q;
    vector<vi> AL(n);
    for (int u = 1; u < n; u++) {
        int v;
        cin >> v;
        v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    vi sz(n), in(n), out(n);
    vector<vii> ch(n);
    int timer = -1;
    auto dfs = [&](auto self, int u, int p) -> void {
        sz[u] = 1;
        in[u] = ++timer;
        for (int v : AL[u]) {
            if (v == p) continue;
            self(self, v, u);
            ch[u].push_back({in[v], v});
            sz[u] += sz[v];
        }
        out[u] = timer;
    };
    dfs(dfs, 0, -1);

    auto is_anc = [&](int a, int u) {
        return in[a] <= in[u] && out[u] <= out[a];
    };

    auto get = [&](int a, int u) {
        return (--upper_bound(all(ch[a]), ii{in[u], 1e9}))->second;
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        ll ans = 0;
        if (is_anc(u, v)) {
            ans = (ll)sz[v] * (n - sz[get(u, v)]);
        } else if (is_anc(v, u)) {
            ans = (ll)sz[u] * (n - sz[get(v, u)]);
        } else {
            ans = (ll)sz[u] * sz[v];
        }
        cout << ans << '\n';
    }
}

int main() {
    freopen("campnou.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}