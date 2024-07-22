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
    vi h, p, sz;
    int mx, cc;
    DSU(int n) {
        h.resize(n), p.resize(n), sz.assign(n, 1);
        mx = 1, cc = n;
        iota(all(p), 0);
    }

    int find(int x) {
        if (x != p[x]) p[x] = find(p[x]);
        return p[x];
    }

    bool join(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return 0;
        if (h[py] > h[px]) {
            p[px] = py;
            sz[py] += sz[px];
            ckmax(mx, sz[py]);
        } else {
            p[py] = px;
            sz[px] += sz[py];
            ckmax(mx, sz[px]);
            if (h[px] == h[py]) h[px]++;
        }
        cc--;
        return 1;
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
        cout << dsu.cc << " " << dsu.mx << "\n";
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