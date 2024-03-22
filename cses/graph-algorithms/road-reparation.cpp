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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

struct DSU {
    vi p, h;
    DSU(int n) {
        h.assign(n, 0);
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
            p[px] = py;
        } else {
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
    vector<iii> EL;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        EL.push_back({w, u, v});
    }

    sort(EL.begin(), EL.end());
    DSU dsu(n);
    ll ans = 0;
    int x = 0;
    for (auto& [w, u, v] : EL) {
        if (dsu.join(u, v)) {
            ans += w;
            x++;
        }
    }

    if (x != n - 1)
        cout << "IMPOSSIBLE\n";
    else
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
