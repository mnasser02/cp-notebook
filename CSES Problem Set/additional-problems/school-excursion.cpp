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

struct DSU {
    vi p, h, sz;
    DSU(int n) {
        h.assign(n, 0);
        sz.assign(n, 1);
        p.resize(n);
        iota(all(p), 0);
    }
    int find(int x) {
        if (p[x] != x)
            p[x] = find(p[x]);
        return p[x];
    }
    bool join(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py)
            return false;
        if (h[px] < h[py]) {
            sz[py] += sz[px];
            p[px] = py;
        } else {
            sz[px] += sz[py];
            p[py] = px;
            if (h[px] == h[py])
                h[px]++;
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        dsu.join(u, v);
    }
    vi w;
    for (int u = 0; u < n; u++) {
        if (u == dsu.find(u)) {
            w.push_back(dsu.sz[u]);
        }
    }

    bitset<(int)1e5 + 1> bs;

    bs[0] = 1;
    for (int i = 0; i < w.size(); i++) {
        bs |= bs << w[i];
    }
    for (int u = 1; u <= n; u++) {
        cout << bs[u];
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