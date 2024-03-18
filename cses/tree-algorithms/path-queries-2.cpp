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
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

struct SegTree {
    vi tree;
    int n;
    SegTree(int _n) : n(_n) {
        while (__builtin_popcount(n) != 1) n++;
        tree.resize(2 * n);
    }
    int query(int l, int r) {
        int ra = 0, rb = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ra = max(ra, tree[l++]);
            if (r & 1) rb = max(rb, tree[--r]);
        }
        return max(ra, rb);
    }
    void update(int p, int x) {
        tree[n + p] = x;
        for (int j = n + p >> 1; j >= 1; j >>= 1) {
            tree[j] = max(tree[j << 1], tree[j << 1 | 1]);
        }
    }
};

vi a;
struct HLD {
    vector<vi> &AL;
    vi sz, par, dep, id, tp;
    SegTree st;
    int ct;

    HLD(vector<vi> &_AL, int n) : AL(_AL), st(n) {
        sz.assign(n, 0);
        par.assign(n, -1);
        dep.assign(n, 0);
        id.assign(n, -1);
        tp.assign(n, -1);
        ct = -1;
        dfs(0, -1);
        dfs_hld(0, -1, 0);
    }

    void dfs(int u, int p) {
        sz[u] = 1;
        for (int v : AL[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            par[v] = u;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }

    void dfs_hld(int u, int p, int top) {
        id[u] = ++ct;
        st.update(id[u], a[u]);
        tp[u] = top;
        int h_ch = -1, h_sz = -1;
        for (int v : AL[u]) {
            if (v == p) continue;
            if (sz[v] > h_sz) {
                h_ch = v;
                h_sz = sz[v];
            }
        }
        if (h_ch == -1) return;
        dfs_hld(h_ch, u, top);
        for (int v : AL[u]) {
            if (v == p || v == h_ch) continue;
            dfs_hld(v, u, v);
        }
    }

    int query(int x, int y) {
        int ans = 0;
        while (tp[x] != tp[y]) {
            if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
            ans = max(ans, st.query(id[tp[x]], id[x]));
            x = par[tp[x]];
        }

        if (dep[x] > dep[y]) swap(x, y);
        ans = max(ans, st.query(id[x], id[y]));
        return ans;
    }
    void update(int p, int x) {
        st.update(id[p], x);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vi> AL(n);
    AL.assign(n, vi());
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    HLD hld(AL, n);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            i--;
            hld.update(i, x);
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << hld.query(u, v) << " ";
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
